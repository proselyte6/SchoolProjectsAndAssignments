CS442 Design Patterns
Fall 2016
PROJECT 4 README FILE

Due Date: Wednesday, October 23th, 2016 at 12 PM
Submission Date: Thursday, October 24th, 2016 at 12:30 AM
Grace Period Used This Project: 1 Slack day used
Grace Period Remaining: 0 slack days remaining
Author(s): Shafkat Haque
e-mail(s): shaque4@binghamton.edu


PURPOSE:

This assignment was to test our knowledge of the Visitor, Prototype and Observer pattern, and seeing how patterns can interact with each other and work together. For the data structure I chose was a binary search tree. I inserted in order according to the length of the words so it can be as balanced as possible. The insertion and traversing would work at O(lg n) at best and average case and would work at O(n) at worst case. If I used a linked list, it would have taken O(n) no matter what, so a tree was much more efficient.

PERCENT COMPLETE:

I believe I have completed 100% of this project.

PARTS THAT ARE NOT COMPLETE:

-

BUGS:

-

FILES:

build.xml - needed for using ANT

/driver/Driver.java - the main file that validates the command line input. Then creates the trees, file processors and visitors. Then uses a performance measurement loop. Then it tests the observer pattern works by using another visitor and writing those results to an output file.

/util/Logger.java - logger class for debugging

/util/LoggerI.java - interface for logger class

/util/FileProcessorI.java - interface for file processor class

/util/FileProcessor.java - used for processing input files and writing to output files

/dsForStrings/Node.java - the node for the tree, that holds  word, the count for the word, two child nodes and a parent nods. Implements the prototype and observer pattern. Every node in the original tree is a subject and every corresponding node in the back up tree is an observer.

/dsForString/Tree.java - the tree class. has an insert method

/Observer/Observer.java - the interface for Observers

/Observer/Subject.java - the interface for Subjects

/visitors/DSProcessingVisitorI.java - the interface for data structure processing visitors.

/visitors/PopulateVisitor.java - This visitor is responsible for populating the data structure with the words from an input file.

/visitors/WordCountVisitor.java - this Visitor determines the total number of words, total number of unique words, and characters stored in the data structure

/visitors/CloneAndObserveVisitor.java - This visitor is used for cloning and setting up the subject - observer relationship

/visitors/TestVisitor.java - This visitor class is just for showing that the observer pattern works



SAMPLE OUTPUT:

Total number of words: 1312
Total distinct number of words: 640
Total number of characters: 6147

TO COMPILE:

//within the directory of haque_shafkat_assign4/wordCount/src
ant
ant jar

TO RUN:

//within the directory of haque_shafkat_assign4/wordCount/src
ant run

EXTRA CREDIT:

-

BIBLIOGRAPHY:

-

ACKNOWLEDGEMENT:

-