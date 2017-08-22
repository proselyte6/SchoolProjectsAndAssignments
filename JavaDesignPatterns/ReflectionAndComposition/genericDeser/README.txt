CS442 Design Patterns
Fall 2016
PROJECT 5 README FILE

Due Date: Thursday, December 15th, 2016 at 12 PM
Submission Date: Monday, December 12th, 2016 at 2:30 AM
Slack Days Used This Project: 0
Slack Days Remaining: 0
Author(s): Shafkat Haque
e-mail(s): shaque4@binghamton.edu


PURPOSE:

This assignment was to test our knowledge and understanding of Java Reflection and Object Composition. Java Reflection is used when we are processing the input file, to choose the right class, fields, and methods. We also overload the equals method and hashCode method to calculate if there are unique objects. The data structures used in this class are hash sets. The methods for traversing, adding and calculating runs in worst time O(n), so when every object is unique, and the best time is 0(1), when there is only multiple copies of the same object. I thought this structure would have been the best because hash sets prevent the same object being added to a set, so I can just increment counts of unique objects.

PERCENT COMPLETE:

I believe I have completed 100% of this project.

PARTS THAT ARE NOT COMPLETE:

-

BUGS:

-

FILES:

build.xml - needed for using ANT

/driver/Driver.java - the main file that processes the command line arguments, sets the logger, creates the file processor and populate objects and calls the method genericDeser()

/util/Logger.java - logger class for debugging. Set at 0, the results will print

/fileOperations/FileProcessorI.java - interface for file processor class

/fileOperations/FileProcessor.java - used for processing input files

/util/SecondI.java - the interface for the Second class

/util/Second.java - the class for the Second object with an overloaded equals() and hashCode() method

/util/FirstI.java - the interface for the First class

/util/First.java - the class for the First Objects with an overloaded equals() and hashCode() method

/util/PopulateObjectsI.java - the interface for the PopulateObjects

//util/PopulateObjects.java - the class PopulateObjects that uses hash sets to store the instances of First and Second objects. It also contains the hash map that maps the string types to the actually type/class. It also calculates all the unique first objects, unique second objects, total first objects and total second objects. It processes an input file and uses reflection to create the objects.

SAMPLE OUTPUT:

Number of unique First objects: 4952
Total Number of First objects: 4952
Number of unique Second objects: 5018
Total Number of Second objects: 5048


TO COMPILE:

//within the directory of haque_shafkat_assign5/genericDeser
ant
ant jar

TO RUN:

//within the directory of haque_shafkat_assign5/genericDeser
ant run -Darg0=input.txt -Darg1=0

EXTRA CREDIT:

-

BIBLIOGRAPHY:

-

ACKNOWLEDGEMENT:

-