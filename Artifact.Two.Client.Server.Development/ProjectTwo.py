from jupyter_plotly_dash import JupyterDash

import dash
import dash_leaflet as dl
import dash_core_components as dcc
import dash_html_components as html
import dash_table
import plotly.express as px
import dash_table as dt
from dash.dependencies import Input, Output, State

import os
import numpy as np
import pandas as pd
from pymongo import MongoClient
from bson.json_util import dumps

# Import base64 for encoding of image
import base64

# Import CRUD object 
from CRUD import AnimalShelter

# Define CSS style variables   
HEADER_IMAGE = {'width':'196px'}
TEXT_CENTER = {'text-align':'center'}
TABLE_CELL = {'text-align': 'left', 'min-width': '150px'}
MAP_CONTAINER = {'float':'left',
                 'width': '500px', 
                 'height': '470px', 
                 'margin-top':'10px', 
                 'margin-right':'10px', 
                 'padding':'5px', 
                 'border':'1px solid #e3e3e3',
                 'border-radius': '5px',
                 'box-shadow': '5px 5px 5px #ccc'}
GRAPH_CONTAINER = {'float':'left',
                   'width':'500px', 
                   'margin-top':'10px', 
                   'margin-right':'10px',
                   'padding':'5px',
                   'border':'1px solid #e3e3e3',
                   'border-radius': '5px',
                   'box-shadow': '5px 5px 5px #ccc'}
CLEAR_FIX = {'clear':'both'}
BOLD_TEXT = {'font-weight':'700'}

# Define pagination variables
PAGE_SIZE = 5

# Define filter variables
FILTER_NONE = {}

FILTER_WATER = {'$or':
                [{"breed":"Labrador Retriever Mix"},
                 {"breed":"Chesapeake Bay Retriever"},
                 {"breed":"Newfoundland"}
                ],
                "age_upon_outcome_in_weeks":{"$gte":26,"$lte":156},
                "sex_upon_outcome":"Intact Female"}

FILTER_MOUNTAIN = {'$or':                 
                   [{"breed":"German Shepherd"},
                    {"breed":"Alaskan Malamute"},
                    {"breed":"Old English Sheepdog"},
                    {"breed":"Siberian Husky"},
                    {"breed":"Rottweiler"}
                   ],
                   "age_upon_outcome_in_weeks":{"$gte":26,"$lte":156},
                   "sex_upon_outcome":"Intact Male"}

FILTER_DISASTER = {'$or':
                   [{"breed":"Doberman Pinscher"},
                    {"breed":"German Shepherd"},
                    {"breed":"Golden Retriever"},
                    {"breed":"Bloodhound"},
                    {"breed":"Rottweiler"}
                   ],
                   "age_upon_outcome_in_weeks":{"$gte":26,"$lte":156},
                   "sex_upon_outcome":"Intact Male"}

FILTER_ELDERLY = {"age_upon_outcome_in_weeks":{'$gte':782}} 

# Instantiate CRUD object
animalShelter = AnimalShelter('aacuser', 'snhu', '33893')

# Populate data frame
cursor = animalShelter.read(FILTER_NONE)
df = pd.DataFrame.from_records(list(cursor))
df[' index'] = range(1, len(df) + 1)

#Generate base64 encoded image in memory
encoded_image = base64.b64encode(open('logo.png', 'rb').read())

app = JupyterDash('SimpleExample')
app.layout = html.Div([
    html.Div(id='hidden-div', style={'display':'none'}),
    
# Header
    html.Div([
        html.Img(src='data:image/png;base64,{}'.format(encoded_image.decode()), style = HEADER_IMAGE),
        html.H3('Ryan DeBraal - CS-340-Q5031 Client/Server Development 21EW5')       
    ], style=TEXT_CENTER), 
    
# Radio Button List
    html.Div([
        dcc.RadioItems(
        id = 'rdoList',
        options = [           
            {'label': 'Water Rescue', 'value': 'WATER'},
            {'label': 'Mountain Rescue', 'value': 'MOUNTAIN'},
            {'label': 'Disaster Rescue ', 'value': 'DISASTER'},
            {'label': 'Elderly (15+) ', 'value': 'ELDERLY'},  
            {'label': 'Reset', 'value': 'ALL'},
        ],
        value = 'WATER',
        labelStyle = {'display': 'inline-block'}
    ),
    ]),
    html.Br(),
      
# Table & Pagination
    html.Div(id='table-output', children = [
            dash_table.DataTable(
                id='datatable-id',
                columns=[
                    {"name": i, "id": i} for i in df.columns
                ])]),
    html.Br(),
    html.Br(),
    html.Br(),
    html.Div(children = [
        html.Div(['Map:'], style=BOLD_TEXT),
        html.Div(id='map-id')
    ], style=MAP_CONTAINER),
    html.Div(children = [
        html.Div(['Outcomes:'], style=BOLD_TEXT),
        dcc.Graph(id="pie-chart")
    ], style=GRAPH_CONTAINER),
    html.Div(style=CLEAR_FIX),
    html.Br(),
    html.Br(),
    html.Br(),
    
]) # End of app
    
# Radio Button List Callbacks
@app.callback(
    dash.dependencies.Output('table-output', 'children'),
    [dash.dependencies.Input('rdoList', 'value')]
    )
def update_output(value):

    # Generate data frame based on radio button list selection
    if value == 'ALL':        
        df = pd.DataFrame.from_records(animalShelter.read(FILTER_NONE))   
    elif value == 'WATER':        
        df = pd.DataFrame.from_records(animalShelter.read(FILTER_WATER))      
    elif value == 'MOUNTAIN':      
        df = pd.DataFrame.from_records(animalShelter.read(FILTER_MOUNTAIN))      
    elif value == 'DISASTER':
        df = pd.DataFrame.from_records(animalShelter.read(FILTER_DISASTER))
    elif value == 'ELDERLY':
        df = pd.DataFrame.from_records(animalShelter.read(FILTER_ELDERLY))
        
    return [
        dash_table.DataTable(
            id = 'datatable-id',
            columns = [{"name": i, "id": i} for i in df.columns],
            data = df.to_dict('records'),
            style_cell = TABLE_CELL,
            style_data_conditional=[{'if': {'row_index': 'odd'},'background-color': '#f3f3f3'}],
            style_header={'background-color': '#e3e3e3','font-weight': 'bold'},
            page_action = 'native',
            page_current = 0,
            page_size = PAGE_SIZE)        
       ]

# Graph Callbacks - - - - - - - - - - - - - - - - - - - - -   
@app.callback(
    Output("pie-chart", "figure"),
    [Input("datatable-id", "data")]
)
def generate_chart(data):
    dff = pd.DataFrame.from_dict(data)
    fig = px.pie(dff,names='outcome_type')
    return fig

# Map Callbacks - - - - - - - - - - - - - - - - - - - - -   
@app.callback(
    Output('map-id', "children"),
    [Input('datatable-id', "derived_viewport_data")])
def update_map(viewData):
    dff = pd.DataFrame.from_dict(viewData)
    
    # Parse values out of data frame
    posX = [str(i) for i in dff.iloc[0:5,9].values]
    posY = [str(i) for i in dff.iloc[0:5,10].values]   
    animal_ids = dff.iloc[0:5,0].values
    animal_names = dff.iloc[0:5,5].values
    
    # Austin TX is at [30.75,-97.48]
    return [
        dl.Map(style={'width': '500px', 'height': '450px'}, center=[posX[0],posY[0]], zoom=8, children=[
            dl.TileLayer(id="base-layer-id"),

            # Animal 0
            dl.Marker(position=[posX[0],posY[0]], children=[
                dl.Tooltip([
                    html.Span(['ID: '], style=BOLD_TEXT),
                    html.Span(animal_ids[0]),
                    html.Br(),
                    html.Span(['Name: '], style=BOLD_TEXT),
                    html.Span(animal_names[0])
                ])
            ]),
            
            # Animal 1
            dl.Marker(position=[posX[1],posY[1]], children=[
                dl.Tooltip([
                    html.Span(['ID: '], style=BOLD_TEXT),
                    html.Span(animal_ids[1]),
                    html.Br(),
                    html.Span(['Name: '], style=BOLD_TEXT),
                    html.Span(animal_names[1])
                ])
            ]),
            
            # Animal 2
            dl.Marker(position=[posX[2],posY[2]], children=[
                dl.Tooltip([
                    html.Span(['ID: '], style=BOLD_TEXT),
                    html.Span(animal_ids[2]),
                    html.Br(),
                    html.Span(['Name: '], style=BOLD_TEXT),
                    html.Span(animal_names[2])
                ])
            ]),
            
            # Animal 3
            dl.Marker(position=[posX[3],posY[3]], children=[
                dl.Tooltip([
                    html.Span(['ID: '], style=BOLD_TEXT),
                    html.Span(animal_ids[3]),
                    html.Br(),
                    html.Span(['Name: '], style=BOLD_TEXT),
                    html.Span(animal_names[3])
                ])
            ]),
            
            # Animal 4
            dl.Marker(position=[posX[4],posY[4]], children=[
                dl.Tooltip([
                    html.Span(['ID: '], style=BOLD_TEXT),
                    html.Span(animal_ids[4]),
                    html.Br(),
                    html.Span(['Name: '], style=BOLD_TEXT),
                    html.Span(animal_names[4])
                ])
            ]),
            
        ])
    ]


# Execution starts here
app