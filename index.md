## Introduction
![image](https://user-images.githubusercontent.com/83176990/129499810-55183e75-5e0c-4348-9d6d-92849437c911.png)

My name is Ryan DeBraal, I am originally from rural Wisconsin but now live with my wife in Chicago. I work as a Software Developer in the Information Security sector. I have been attending SNHU for approximately three years. I returned to academia after a ten-year hiatus because I wanted to complete my degree. 

When I was twenty-four years old I was hired for a six-month contract at a local corporation best known for manufacturing toilet paper, to help develop a Regulatory Affairs document management system. This six-month contract became a three-year contract and during that time school fell by the wayside.

Fast forward to 2018, I've moved to Chicago and have been hired as a full-time employee at a Fortune 500 company with nothing on my resume but a High School education. My wife, having witnessed my self-consciousness about by level of formal education (or lack thereof), suggested I return to school and finish my degree. To my astonishment and delight a great deal of my credits from a decade ago transferred over.

SNHU has taught me several valuable lessons. I think the most important of which is that they have refreshed my memory on how to “learn” in an academic environment. I never took school very seriously; I was always smart enough to be able to just glance at material and make assumptions about its content and pull off a passing grade. 

However, when I started classes at SNHU, my slapdash attempts at writing papers at the last minute were met with underwhelming grades. I then discovered that words without academic rigor behind them have little value. Both in school and in the professional world. Being “learned” in a subject is far more prized than simply having a “good gut feeling”.

I initially enrolled in the Game Development program because that was the passion which had initially drawn me into software development in my early teens. However, as I was attending classes a reoccurring headline seemed to keep cropping up in my new feed: “Hundreds of Develops laid off following record-breaking release of AAA title”. 

I realized that the game industry had an awful turnover rate rife with “crunch time” development sprints. I decided to switch to a more classical “Computer Science” degree course instead. It has been a boon when it comes helping to reenforce the coding practices I use in my day-to-day life and has given me confidence to express myself with academic knowledge backing my statements.

### Objective

My objective while creating this ePortfolio was to curate the work that I have done in previous courses. In their original incarnations, I demonstrated aptitude now with  additional time and research I've improved upon these codebases. I am confident that I've illustrated my ability to iterate upon an existing project and demonstrate that I can not only create useful software but to enhance preexisting software with an eye towards a meaningful future state.

This ePortfolio represents only a small vertical slice of my development experiences at SNHU.

---

## Code Review
![image](https://user-images.githubusercontent.com/83176990/129500048-e2f1c314-3a3b-42d4-8211-9d02787ac507.png)

### Links
###### This article is available as a [PDF](https://github.com/ryandebraalsnhu/ryandebraalsnhu.github.io/blob/main/2-1.Journal.What.Makes.a.Productive.Code.Review-Ryan.DeBraal.pdf).
###### This review can be seen on [YouTube](https://www.youtube.com/watch?v=jG0b8Cf76q) (~52 min).

A code review is as important to a software developer as a second draft is to an author. Good software is not written in bursts of inspiration but rather honed and perfected over the course of many iterations. 

Code reviews come in a variety of forms including pair programming, over-the-shoulder presentations, and even tool assisted code checks. A typical code review usually consists of one developer reviewing another developer’s code and trying to identify mistakes.

This process has been shown to improve overall code quality in the same way that a proofreader can more easily identify another writer’s mistakes in spelling or grammar because they do not have a personal association with the code.

When someone reviews code they should be looking for common issues such as missed data validation checks or null exceptions, but they should also be conscience of the overall solution that the code is attempting to attain and be thinking about ways on which the process could be improved.

Code reviews should occur frequently throughout the development process. The Agile process is specifically designed to place code reviews at pivotal junctures throughout the SDLC. After a user story is completed and submitted as a pull request, a developer should be made responsible for reviewing the code. This way there is a system of checks in place to make sure that more than one person has signed off on a piece of code and that responsibility for the correct functioning of a piece of code is shared between multiple developers.

Personally, I have found live demonstrations to be the most effective method of code review. It has been my experience that software developers can become very myopic when looking at the code rather than how the code functions from the perspective of the user. No code is bug free, and all code can always be improved in one way or another, but it is important that the developer understands that what they are building is ultimately to satisfy a customer’s needs.

---

## Artifact One: Search Methodologies (Data Structures and Algorithms)
![image](https://user-images.githubusercontent.com/83176990/129497305-be8187b0-1f5d-49de-9e96-ef03fff7e9d7.png)

### Links
###### This article is available as a [PDF](https://github.com/ryandebraalsnhu/ryandebraalsnhu.github.io/blob/main/7-1.Final.Project.Reflection.Paper.pdf).
###### This project is available for [Download](https://ryandebraal.com/downloads/4-2.Milestone.Three.Enhancement.Two-Ryan.DeBraal.zip). 
###### This project is available as a [Repo](https://github.com/ryandebraalsnhu/Artifact.One.Data.Structures.and.Algorithms).

### Narrative
For this artifact I chose to consolidate the assignments of Module Three, Five and Six of the CS-260 Data Structures and Algorithms course into a single project and allow the user to select which mode they would like to utilize in order to load, read, search, and delete bids from a data structure. This was a valuable experience for me because as I revisited each methodology and directly compared them against each other I became much more familiar with the pros and cons of each data structure type. This project is a good example of my ability organize data into collections and use search algorithms (such as Binary Search Tree) to navigate the data in an efficient manner.

I think the code is highly reusable, all the data structure implementations can be adapted to another project simply be swapping our the Bid struct for another object that needs to be maintained in a collection. I am pleased with the annotations I placed in the code base, I try to code based on a motto I heard several years ago: “verbosity over brevity”. To me this means it does not serve anyone better to write code that isn’t cleanly organized and well documented. I think software developers are often tempted to try to condense their code into the smallest amount of space as possible, especially with the advent of LINQ. 

Enhancing this project was a pretty straight forward endeavor. Since I had developed this application quite some time ago I had naturally become a more proficient developer, so revisiting my "old code" caused me to immediately recognize some deficents that could be quickly repaired.

### Functionality
The Linked List mode pulls the data from the CSV and stores it in a data structure with a dynamic size. However, this methodology has several drawbacks:
- They can only be iterated across in one direction, from the beginning or “head” to the end or “tail”, this means there is no “random access” allowed.
- A pointer to the head node must be constantly maintained. 

![image](https://user-images.githubusercontent.com/83176990/129496849-fb9c8cbd-d7d8-4264-918d-a178f2c83c43.png)

The Hash Table mode pulls the data into a data structure which utilizes a vector to map a value to a “hash” and then later retrieve that value via its hash. This allows data to be retrieved very quickly. A hash value is often derived using this simple formula: hash = key % noOfBuckets

By being able to simply “lookup” a specific data point in a collection, the ability to retrieve information becomes straightforward. This is a significant improvement over having to iterate across a collection until a match is found. To avoid collisions, each “cell” of a hash table is actually a linked list of records so that data can be retrieved from a certain hash index in the same manner as the aforementioned linked list.

![image](https://user-images.githubusercontent.com/83176990/129496859-f40bf7e9-4b57-447e-8a68-fc99259b4847.png)

The Binary Search Tree mode stores data in a more complex way and is therefore a little more unwieldy but search capabilities are significantly improved because of the way the data is stored and retrieved.

In a Binary Search Tree, each node contains a value from a well-ordered set. Every node in the left subtree contains a value which is smaller than the value in the current node, and every node in the right subtree contains a value which is larger than the value in the current node. This allows for simple boolean logic to quickly search for and retrieve data because the data is being navigated through rather than iterated across.

![image](https://user-images.githubusercontent.com/83176990/129496862-cf4162b4-b299-4f71-94c6-4d5dfe1579e5.png)

### Citations
Insertion Sort for Singly Linked List. GeeksforGeeks, 3 Feb. 2020, [www.geeksforgeeks.org/insertion-sort-for-singly-linked-list/](www.geeksforgeeks.org/insertion-sort-for-singly-linked-list/)

InterviewBit. “Linked Lists.” InterviewBit, [www.interviewbit.com/courses/programming/topics/linked-lists/](www.interviewbit.com/courses/programming/topics/linked-lists/)

Nilsson, Stefan. “Binary Search Trees Explained.” · YourBasic, Yourbasic.org, [www.yourbasic.org/algorithms/binary-search-tree/](www.yourbasic.org/algorithms/binary-search-tree/)
ZyBooks, [https://learn.zybooks.com/zybook/SNHUCS260AY16-17/chapter/5/section/1](https://learn.zybooks.com/zybook/SNHUCS260AY16-17/chapter/5/section/1)

---

## Artifact Two: Grazioso Salvare Austin Animal Shelter CRUD (Client\Server Development)
![image](https://user-images.githubusercontent.com/83176990/129497826-14effb73-987a-482b-b5e7-5061ae2799e2.png)

### Links
###### This project is available for [Download](https://ryandebraal.com/downloads/Artifact.Two.Client.Server.Development.zip). 
###### This project is available as a [Repo](https://github.com/ryandebraalsnhu/ClientServer_PortfolioItem).

### Narrative
For this artifact I chose to enhance the final project for CS-260 Data Structures and Algorithms, an application which is used to create, read, update, and delete (CRUD) records from a MongoDB database. This project is a good example of my ability to manipulate data in a database through a GUI.

Enhancing this project was quite a bit more difficult than Artifact One. For starters, the Virtual Machine (VM) that I had used to develop this application had already been wiped of my credentials! In order to enhance this application I had to first setup a local MongoDB instance on my home machine, then hunt down the original [JSON file](https://catalog.data.gov/de/dataset/austin-animal-center-intakes/resource/3762cdf8-ccdb-4de5-83a1-bb7d98a00f12) needed to import the data into the instance. Finnally, I had to setup Jupyter Notebook in Windows, which first required installation of Anaconda, a package manager similar to Node Package Manager (npm), which I use quite often in my work life.

### Functionality
The application in its current state can be used to navigate the AAC database, filter by various conditions, visualize the GPS location where the animal was found, and generate a breakdown of outcomes per filtered section. In the future this application can be expanded to create a fully realized CRUD application capable of maintaining the data retained and administrated by the Austin Animal Control Center. 

This application was developed to leverage the pre-existing instance of MongoDB, which is a document-based, “No-SQL” database. The data access layer (DAL), or Controller in MVC parlance, utilizes [PyMongo](https://pymongo.readthedocs.io/en/stable/) to create, read, update, and delete (CRUD) data. The user interface, or View in MVC parlance, is powered by [Dash](https://dash.plotly.com/introduction), a framework for building web analytic applications.

These technologies were chosen for their relative ease of use and rapid stand-up time. Each component of this n-tier application was developed modularly so that it could be enhanced or swapped out easily in the future as need dictates. 

For example, if the client decided that they wanted the application to run on the Django web framework, they could simply reutilize the existing CRUD.py component and write a new user interface.

### Citations

Austin animal Center Intakes - json file - ckan. Austin Animal Center Intakes - JSON File - CKAN. (n.d.). [https://catalog.data.gov/de/dataset/austin-animal-center-intakes/resource/3762cdf8-ccdb-4de5-83a1-bb7d98a00f12](https://catalog.data.gov/de/dataset/austin-animal-center-intakes/resource/3762cdf8-ccdb-4de5-83a1-bb7d98a00f12).

Introduction to dash. Plotly. (n.d.). [https://dash.plotly.com/introduction](https://dash.plotly.com/introduction). 

PyMongo 3.12.0 documentation. PyMongo 3.12.0 Documentation - PyMongo 3.12.0 documentation. (n.d.). [https://pymongo.readthedocs.io/en/stable/](https://pymongo.readthedocs.io/en/stable/). 

---

## Artifact Three: MinimalYST - A minimalist Open GL tribute to Myst (Software Design and Engineering)
![image](https://user-images.githubusercontent.com/83176990/129498322-bd4ebb7a-2826-4ee0-9c11-9f8eac98120d.png)

### Links
###### This project is available for [Download](https://ryandebraal.com/downloads/2-2.Milestone.One.Code.Review.mp4). 
###### This project is available as a [Repo](https://github.com/ryandebraalsnhu/computer-graphics-portfolio).
###### This project can be seen on [YouTube](https://www.youtube.com/watch?v=EV29wz9A6gs&t=4s) (~3 min).

### Narrative
For this artifact I chose to enhance the final project for CS-330 Computer Graphic and Visualization, this project utilizes several third party OpenGL libraries. It was meant to be a minimalist tribute to the classic point-and-click adventure game, Myst. This project is a good example of my ability to utilize third party libraries and combine them effectively into a cohesive experience.

This was a particularly challenging project to complete initially as it was a culmination of almost every lesson I've learned at SNHU including design and analysis, planning, time management, object oriented programming (OOP), geometry, physics, data structures, and perhaps most importantly: the ability to learn and adapt quickly.

### Functionality
The application in its current state is a simple 3D scene with the ability to walk around using the keyboard and look around using the mouse. There are several "algorithmic systems" implemented including a day/night cycle, and the flickering glow of a candle.

Overall, this was my favorite project to work on because it required a very high degree of understanding but also allowed me to express myself creatively. 

### Citations

Allen, A. (2016, August 15). What is dependency hell? Retrieved April 25, 2021, from [https://searchitoperations.techtarget.com/definition/dependency-hell](https://searchitoperations.techtarget.com/definition/dependency-hell)

Contieri, M. (2020, May 26). Fail fast PHILOSOPHY, Explained. Retrieved April 25, 2021, from [https://hackernoon.com/fail-fast-philosophy-explained-si963vk9](https://hackernoon.com/fail-fast-philosophy-explained-si963vk9)

---

## Self Assessment

Whenever possible I try to employ a "fail fast" philosophy, which is sometimes known as "defensive programming". (Contieri, 2020) 

Whenever I write code, I immedietly try to determine if the data is valid. If it isn't, I stop working with it immediately and return a well formatted exception. It is pointless to try to "shove bad data" through the business logic.

I've often seen code online that looks like this:

```
if (collection != null) {
    if (collection.Data != null || collection.Data.length < 1) {
        for (var d in collection.Data) {
	        if (d != null) {	        
 	            if (d.ID != null && d.ID > 0) {
		            //Business logic goes here...
                } else {
					//Invalid ID...
				}
	        } else {
				//Data in loop is null...
			}
        }		
	} else {
		//Data in collection is null...
	}	
} else {
    //Collection is null...
}
```

The above (imho) looks like needlessly convoluted. This same logic could be refactored to read more cleanly and be more robust by simply testing the data and stopping progress (fail fast) as soon as the data isn't viable:

```
if (collection == null || collection.Data == null || !collection.Data.Any())
    return Error("An invalid collection has been specified.");

for (var d in collection.Data) {
    if (d == null || d.ID == null || d.ID < 1)
        continue; 

    //Business logic goes here...  	
}
```

In my opinion, the first step in developing code is to make it do what the customer wants, the second step should be to retain the quality of the code but still make sure that it does what the customer wants. I have seen numerous occasions when code refactoring has resulted in much cleaner code that no longer performs the basic operations that the “spaghetti code” mysteriously was able to achieve. 

Coding something that works is the most important, but coding something that can be easily interpreted by another developer is a close second.

In the words of Albert Einstein:

> If you can't explain it simply, you don't understand it well enough.

