### Introduction

...


### What Makes a Productive Code Review?
###### This article is available as a [PDF](https://github.com/ryandebraalsnhu/ryandebraalsnhu.github.io/blob/main/2-1.Journal.What.Makes.a.Productive.Code.Review-Ryan.DeBraal.pdf).

![image](https://user-images.githubusercontent.com/83176990/129496538-24f8168d-57e9-4912-bb0b-e97ca50cb780.png)

A code review is as important to a software developer as a second draft is to an author. Good software is not written in bursts of inspiration but rather honed and perfected over the course of many iterations. 

Code reviews come in a variety of forms including pair programming, over-the-shoulder presentations, and even tool assisted code checks. A typical code review usually consists of one developer reviewing another developer’s code and trying to identify mistakes.

This process has been shown to improve overall code quality in the same way that a proofreader can more easily identify another writer’s mistakes in spelling or grammar because they do not have a personal association with the code.

When someone reviews code they should be looking for common issues such as missed data validation checks or null exceptions, but they should also be conscience of the overall solution that the code is attempting to attain and be thinking about ways on which the process could be improved.

Code reviews should occur frequently throughout the development process. The Agile process is specifically designed to place code reviews at pivotal junctures throughout the SDLC. After a user story is completed and submitted as a pull request, a developer should be made responsible for reviewing the code. This way there is a system of checks in place to make sure that more than one person has signed off on a piece of code and that responsibility for the correct functioning of a piece of code is shared between multiple developers.

Personally, I have found live demonstrations to be the most effective method of code review. It has been my experience that software developers can become very myopic when looking at the code rather than how the code functions from the perspective of the user. No code is bug free, and all code can always be improved in one way or another, but it is important that the developer understands that what they are building is ultimately to satisfy a customer’s needs. So, the first step in developing code is to make it do what the customer wants, the second step should be to retain the quality of the code but still make sure that it does what the customer wants. I have seen numerous occasions when code refactoring has resulted in much cleaner code that no longer performs the basic operations that the “spaghetti code” mysteriously was able to achieve.

![image](https://user-images.githubusercontent.com/83176990/129497305-be8187b0-1f5d-49de-9e96-ef03fff7e9d7.png)

### Artifact One: Search Methodologies (Data Structures and Algorithms)
###### This article is available as a [PDF](https://github.com/ryandebraalsnhu/ryandebraalsnhu.github.io/blob/main/7-1.Final.Project.Reflection.Paper.pdf).
###### This project is available for [Download](https://ryandebraal.com/downloads/4-2.Milestone.Three.Enhancement.Two-Ryan.DeBraal.zip). 
###### This project is available as a [Repo](https://github.com/ryandebraalsnhu/Artifact.One.Data.Structures.and.Algorithms).

For this artifact I chose to consolidate the assignments of Module Three, Five and Six of the CS-260-Q3396 Data Structures and Algorithms course into a single project and allow the user to select which mode they would like to utilize in order to load, read, search and delete bids from a data structure. This was a valuable experience for me because as I revisited each methodology and directly compared them against each other I became much more familiar with the pros and cons of each data structure type.

## Data Structures
Main.cpp in the FinalProject solution best exemplifies my knowledge and understanding of the data structure types we learned about in this course.

The Linked List mode pulls the data from the CSV and stores it in a data structure with a dynamic size. However, this methodology has several drawbacks:
•	They can only be iterated across in one direction, from the beginning or “head” to the end or “tail”, this means there is no “random access” allowed.
•	A pointer to the head node must be constantly maintained. 

Fig 1. Linked Lists
![image](https://user-images.githubusercontent.com/83176990/129496849-fb9c8cbd-d7d8-4264-918d-a178f2c83c43.png)

The Hash Table mode pulls the data into a data structure which utilizes a vector to map a value to a “hash” and then later retrieve that value via its hash. This allows data to be retrieved very quickly. A hash value is often derived using this simple formula: hash = key % noOfBuckets

By being able to simply “lookup” a specific data point in a collection, the ability to retrieve information becomes straightforward. This is a significant improvement over having to iterate across a collection until a match is found.
To avoid collisions,  each “cell” of a hash table is actually a linked list of records so that data can be retrieved from a certain hash index in the same manner as the aforementioned linked list.

Fig 2. Hash Table with Chaining
![image](https://user-images.githubusercontent.com/83176990/129496859-f40bf7e9-4b57-447e-8a68-fc99259b4847.png)

The Binary Search Tree mode stores data in a more complex way and is therefore a little more unwieldy but search capabilities are significantly improved because of the way the data is stored and retrieved.

In a Binary Search Tree, each node contains a value from a well-ordered set. Every node in the left subtree contains a value which is smaller than the value in the current node, and every node in the right subtree contains a value which is larger than the value in the current node. This allows for simple boolean logic to quickly search for and retrieve data because the data is being navigated through rather than iterated across.

Fig 3. Binary Search Tree
![image](https://user-images.githubusercontent.com/83176990/129496862-cf4162b4-b299-4f71-94c6-4d5dfe1579e5.png)

## Algorithms

### Search
All three data structures (linked lists, hash tables and binary search trees) can be adapted to search for and retrieve values contained within them. The Linked List mode is straight forward but limited in its scope, this kind of data storage and retrieval is only really viable for a collection of perhaps a few hundred entries. The Hash Table mode has significant advantages over the linked list method; however, it also inherits the linked lists disadvantages because the chained hash tables still utilize linked lists, and therefore the space overhead of the “next” pointer can be significant. The Binary Search Tree mode does away with the limitations of the linked-list but it also far more complex to work with, it also requires a “well-ordered set”, meaning the performance of the search algorithm is directly related to how well the data being stored is organized.

### Sort
Sorting of a linked list requires a rather convoluted methodology, because a singly linked list can only be iterated across in one direction, this would require a separate object to be instantiated and maintained in order to capture values that are “above” or “below” the current pointer. (GeeksforGeeks, 2020)
Fig 4. Pseudo Code for sorting a linked list
 
Sorting of a hash table isn’t necessary because as mentioned previously the data structure depends on “hash lookups” rather than iterating across the data.

Sorting of a Binary Search Tree would be antithetical to its very nature. A binary search trees is dependent upon the data being organized by branching logic. 
Hash/Chaining

Hash Chaining is a clever workaround to the limitations of linked lists and the complications of binary search trees. While “under the hood” it seems somewhat clunky in its implementation, ultimately the ability to lookup data values by hash is a worthwhile endeavor that can make an application run faster and easier to develop.
“Search time for hash table lookups are reduced significantly, searching (or inserting / removing) an item may require only O(1), in contrast to O(N) for searching a list or to O(log N) for binary search.” (zyBooks)

### Effectiveness
Main.cpp in the FinalProject solution was my favorite program to write, because it allowed me to “take off the training wheels” and code something that wasn’t prescribed. I liked creating the “modes” for each data structure type and organizing the different functionalities into discrete methods. I wish I had had more time to make the code mode modular. I ended up sticking all the classes I created into a single .cpp file which made it quite long and harder and harder to maintain as time went on. I didn’t take the time to learn about the relationship between .cpp files and .h files, so “importing” classes was out of the question. I ended up using regions to better organize code, but if I were to continue development on this project I would move the LinkedList, HashTable, and BinarySearchTree classes into individual files.

I think the code is highly reusable, all the data structure implementations can be adapted to another project simply be swapping our the Bid struct for another object that needs to be maintained in a collection.

I am pleased with the annotations I placed in the code base, I try to code based on a motto I heard several years ago: “verbosity over brevity”, To me this means it does not serve anyone better to write code that isn’t cleanly organized and well documented. I think software developers are often tempted to try to condense their code into the smallest amount of space as possible, especially with the advent of LINQ. Coding something that works is the most important, but coding something that can be easily interpreted by another developer is a close second.

### Conclusion
When building something, either in code or in the real world, it is important to use the right tool for the job. Knowing which kind of data structure to use will save development time and result in cleaner, faster code. In this case, I think the eBid Search application that we created was best organized using the Binary Search Tree data structure because each entry has a gaurenteed BidID, I would modify the BidID to be an integer value rather than a string value because that would allow the BST to more quickly determine which branch (left or right) to go down, I imagine the string manipulation of the unique identifier would eventually have a significant impact on search speed.
I was routinely surprised by the amount of effort put into creating things that I routinely take for granted in my day-to-day work developing applications in C#. Dictionarys, LINQ, NO Pointers. These are just a handful of examples of the kinds of tools that I routinely us and never give a second thought.

### Citations
Insertion Sort for Singly Linked List. GeeksforGeeks, 3 Feb. 2020, [www.geeksforgeeks.org/insertion-sort-for-singly-linked-list/](www.geeksforgeeks.org/insertion-sort-for-singly-linked-list/)
InterviewBit. “Linked Lists.” InterviewBit, [www.interviewbit.com/courses/programming/topics/linked-lists/](www.interviewbit.com/courses/programming/topics/linked-lists/)
Nilsson, Stefan. “Binary Search Trees Explained.” · YourBasic, Yourbasic.org, [www.yourbasic.org/algorithms/binary-search-tree/](www.yourbasic.org/algorithms/binary-search-tree/)
ZyBooks, [https://learn.zybooks.com/zybook/SNHUCS260AY16-17/chapter/5/section/1](https://learn.zybooks.com/zybook/SNHUCS260AY16-17/chapter/5/section/1)

![image](https://user-images.githubusercontent.com/83176990/129497826-14effb73-987a-482b-b5e7-5061ae2799e2.png)

### Artifact Two: Grazioso Salvare Austin Animal Shelter CRUD (Client\Server Development)
###### This project is available for [Download](https://ryandebraal.com/downloads/Artifact.Two.Client.Server.Development.zip). 
###### This project is available as a [Repo](https://github.com/ryandebraalsnhu/ClientServer_PortfolioItem).

For this artifact I chose to submit the final project for CS-499-X6397 Computer Science Capstone 21EW6, an application which is used to create, read, update, and delete (CRUD) records from a MongoDB database.

## Motivation
Animal Shelter was created to facilitate record keeping for the Austin Animal Control Center (AAC) database.

## Functionality
The application in its current state can be used to navigate the AAC database, filter by various conditions, visualize the GPS location where the animal was found, and generate a breakdown of outcomes per filtered section. In the future this application can be expanded to create a fully realized CRUD application capable of maintaining the data retained and administrated by the Austin Animal Control Center.

## Tools and rationale
This application was developed to leverage the pre-existing instance of MongoDB, which is a document-based, “No-SQL” database. The data access layer (DAL), or Controller in MVC parlance, utilizes [PyMongo](https://pymongo.readthedocs.io/en/stable/) to create, read, update, and delete (CRUD) data. The user interface, or View in MVC parlance, is powered by [Dash](https://dash.plotly.com/introduction), a framework for building web analytic applications.

These technologies were chosen for their relative ease of use and rapid stand-up time. Each component of this n-tier application was developed modularly so that it could be enhanced or swapped out easily in the future as need dictates. For example, if the client decided that they wanted the application to run on the Django web framework, they could simply reutilize the existing CRUD.py component and write a new user interface.

![image](https://user-images.githubusercontent.com/83176990/129498322-bd4ebb7a-2826-4ee0-9c11-9f8eac98120d.png)

### Artifact Three: MinimalYST - A minimalist Open GL tribute to Myst
###### This project is available for [Download](https://ryandebraal.com/downloads/2-2.Milestone.One.Code.Review.mp4). 
###### This project is available as a [Repo](https://github.com/ryandebraalsnhu/computer-graphics-portfolio).
###### This project can be seen on [YouTube](https://www.youtube.com/watch?v=EV29wz9A6gs&t=4s).

# Computer Graphics Portfolio
https://github.com/ryandebraalsnhu/computer-graphics-portfolio

## How do I approach designing software?

Personally, I always employee a "fail fast" philosophy, which is sometimes known as 
"defensive programming". (Contieri, 2020) Whenever I write code, I immedietly try 
to determine if the data is valid. If it isn't, I stop working with it immediately 
and return a well formatted exception. It is pointless to try to "shove bad data" 
through the business logic.

Very often I see code which looks like this:

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

This is needlessly convoluted "spagetti code". This same logic could be refactored to read 
more cleanly and be more robust by simply testing the data and stopping progress (fail fast) 
as soon as the data isn't viable:

```
if (collection == null || collection.Data == null || !collection.Data.Any())
    return Error("An invalid collection has been specified.");

for (var d in collection.Data) {
    if (d == null || d.ID == null || d.ID < 1)
        continue; 

    //Business logic goes here...  	
}
```

## What new design skills has your work on the project helped you to craft?

Working with OpenGL has given me a better understanding of how C++ organizes it's 
dependancies. I usually work with C#, which allows you to very easily grab a dependancy 
either from the managed code bases (i.e. System.Web.dll) or by linking to a class library 
project within your solution.

I found it challenging and interesting to have the "raw" code for dependancies to be so 
readily at your finger tips. If need be, a developer could fork an existing dependancy
and customize it to their particular needs. I now have a much better understanding of 
"Dependancy Hell". (Allen, 2016)


## What design process did you follow for your project work?

While working on my project, I tried to be as iterative as possible. I would not have been 
able to produce the final project had I not spent the prior six weeks using my existing 
codebase as the start to each week's assignment.

## How could tactics from your design approach be applied in future work?

The ability to organize work efforts and execute them in a timely manner, in a logical order 
is a skill that will serve a developer well not only in their professional career but also 
in life.

## How do I approach developing programs?

When writing code it is important to validate the data you are working with on every level.
When you receive the data from an external source, validate that it is not null and that it 
is in the expected format. When iterating across a collection validate that the collection 
itself is not null and that it has conents. When working with objects, be sure to validate 
each field's data type.

## What new development strategies did you use while working on your 3D scene?

During the course of this project, I used alot more guess and check than I am normally 
comfortable with using. Without the aid of CAD I needed to constantly build and run my 
application to determine if the picture in my head matched what was rendered on screen.

## How did iteration factor into your development?

It was essential. The shear complexity of the final project was the culmination of over 
40 hours of work, which would have been impossible to do without delegating those efforts 
over the duration of the entire course.

## How has your approach to developing code evolved throughout the milestones, which led you to the project’s completion?

I think the existing development strategies that I use in my professional life worked well. 
However, if I were able to give advice to my past self (or to future students in this class)
it would be to better familiarize yourself with the way C++ structures an application.

I lost hours of productively simply trying to get header files to read from eachother in the 
correct order. When it finally did work, I had sort of a "Frakenstein" system cobbled together.

## How can computer science help me in reaching my goals?

I've been using "computer science" since I was 5 years old. It is an essential part of my life
and not only has it provided me with a comfortable lifestyle but it has helped me to develop 
useful skillsets in other areas of my life. The ability to break down situations into logical
steps and then execute them in focused "sprints" has helped me do everything from: getting 
a paycheck to assembling furniture from Ikea.

## How do computational graphics and visualizations give you new knowledge and skills that can be applied in your future educational pathway?

This class will serve as an example of how it is important to completely absorb the content 
before jumping into an assignment. I think I needlessly made things much more difficult for 
myself when I started a new assignment, coded for 4 hours, and they once I ran into a roadblock 
went back to Brightspace only to discover that I've been coding down a blind alley due to a 
fundamental misunderstanding of a concept that would have already been presented to me.

## How do computational graphics and visualizations give you new knowledge and skills that can be applied in your future professional pathway?

I have a new found respect for C++ developers. I wouldn't pursue it as a career, but I definetly 
have a better understanding of the need to be iterative when creating things. Even C# is essentially
just a highly wrappered version of underlying C++ functionalities.

## Citations

Allen, A. (2016, August 15). What is dependency hell? Retrieved April 25, 2021, from https://searchitoperations.techtarget.com/definition/dependency-hell
Contieri, M. (2020, May 26). Fail fast PHILOSOPHY, Explained. Retrieved April 25, 2021, from https://hackernoon.com/fail-fast-philosophy-explained-si963vk9




