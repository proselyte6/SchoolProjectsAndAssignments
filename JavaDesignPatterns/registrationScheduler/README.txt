CS442 Design Patterns
Fall 2016
PROJECT 2 README FILE

Due Date: Friday, September 30th, 2016
Submission Date: Sunday, October 3rd, 2016
Grace Period Used This Project: 3 Days
Grace Period Remaining: 1 Days
Author(s): Shafkat Haque and Adam Buschle
e-mail(s): shaque4@binghamton.edu and abuschl1@binghamton.edu


PURPOSE:

This program assigned 80 students to 7 courses with 60 spots taking in to account
their preference score for each course. This program is different from assignment 1 though
because this one implements multi-threaded programming as well as using the ANT build system.
We also separated code into multiple java files (ex. FileProcessor for file processing and Results to write to stdout or to an output file) and methods instead of having a bunch of code in
the driver. It also helps us learn how to program to an interface, as most classes to implement an interface. We also learn how to create a logger class and use it for debugging purposes, how to implement out own Object Pool (for the courses), and to understand how threads working by creating them, joining them and catching exceptions. We used arrays and vectors for everything so the algorithm runs in O(n) where n is the number of students. Anything from object pool runs in O(m) where m is the number of courses. 

PERCENT COMPLETE:

We believe we have completed 100% of this project.

PARTS THAT ARE NOT COMPLETE:

-

BUGS:

-

FILES:

build.xml, needed for using ANT

/driver/Driver.java, the main class that parses the command line args, sets the logger, creates the instances for the file processor, results, createWorkers (threads) and calls the results class to write to a file.

/store/Course.java, the file that hold the class for a course which contains a vector of students, a string to identify the course, and a boolean value to tell if the course is at full capacity.

/store/Student.java, the file that holds the class for a student which contains their preferences as variables, a vector that holds the string of the enrolled course, and a vector that holds the corresponding preference value to the enrolled course. 

/store/FileDisplayInterface.java, the file for the interface for results to implement that has a method for writing to a file.

/store/StdoutDisplayInterface.java, the file for the interface for results to implement that has a method for writing to stdout.

/store/Results.java, the file that stores the students and the information about their courses. Also has methods to writing to a file and stdout, implemented from the respective interfaces. 

/store/ObjectPool.java, the file that handles the information about courses and the students enrolled in them. Implements the Singleton Pattern, and allows threads to borrow a course, return a course, find how many are available to use, and how many are idle.

/threadMgmt/CreateWorkers.java, the file for CreateWorkers that starts the worker threads, runs them and joins them.

/threadMgmt/WorkerThread.java, the file for the worker threads. Contains the run method which has the algorithm for adding students to courses and vice versa. Now takes into account it is a multi-threaded program and uses the object pool.

/util/FileProcessor.java, the file for processing files. has methods for reading line by line from a file, and writing line by line to file.

/util/Logger.java, the file that uses the debug_value and prints what it needs to respectively. It is all static so it can just be called directly without creating an object for it and is used for debugging.


SAMPLE OUTPUT:

Student_1 A B C D E 15
Student_2 B C D E F 15
Student_3 C D E F G 15
Student_4 A D E F G 15
Student_5 A B E F G 15
Student_6 A B C F G 15
Student_7 A B C D G 15
Student_8 A B C D E 15
Student_9 B C D E F 15
Student_10 C D E F G 15
Student_11 A D E F G 15
Student_12 A B E F G 15
Student_13 A B C F G 15
Student_14 A B C D G 15
Student_15 A B C D E 15
Student_16 B C D E F 15
Student_17 C D E F G 15
Student_18 A D E F G 15
Student_19 A B E F G 15
Student_20 A B C F G 15
Student_21 A B C D G 15
Student_22 A B C D E 15
Student_23 B C D E F 15
Student_24 C D E F G 15
Student_25 A D E F G 15
Student_26 A B E F G 15
Student_27 A B C F G 15
Student_28 A B C D G 15
Student_29 A B C D E 15
Student_30 B C D E F 15
Student_31 C D E F G 15
Student_32 A D E F G 15
Student_33 A B E F G 15
Student_34 A B C F G 15
Student_35 A B C D G 15
Student_36 A B C D E 15
Student_37 B C D E F 15
Student_38 C D E F G 15
Student_39 A D E F G 15
Student_40 A B E F G 15
Student_41 A B C F G 15
Student_42 A B C D G 15
Student_43 A B C D E 15
Student_44 B C D E F 15
Student_45 C D E F G 15
Student_46 A D E F G 15
Student_47 A B E F G 15
Student_48 A B C F G 15
Student_49 A B C D G 15
Student_50 A B C D E 15
Student_51 B C D E F 15
Student_52 C D E F G 15
Student_53 A D E F G 15
Student_54 A B E F G 15
Student_55 A B C F G 15
Student_56 A B C D G 15
Student_57 A B C D E 15
Student_58 B C D E F 15
Student_59 C D E F G 15
Student_60 A D E F G 15
Student_61 A B E F G 15
Student_62 A B C F G 15
Student_63 A B C D G 15
Student_64 A B C D E 15
Student_65 B C D E F 15
Student_66 C D E F G 15
Student_67 A D E F G 15
Student_68 A B E F G 15
Student_69 A B C F G 15
Student_70 A B C D G 15
Student_71 A B C D E 15
Student_72 B C D E F 15
Student_73 C D E F G 15
Student_74 A D E F G 15
Student_75 A B E F G 15
Student_76 A B C F G 15
Student_77 A B C D G 15
Student_78 A B C D E 15
Student_79 B C D E F 15
Student_80 C D E F G 15
Average preference score is: 15.0

TO COMPILE:

ant
ant jar

TO RUN:

ant run

EXTRA CREDIT:

-

BIBLIOGRAPHY:

This serves as evidence that we are in no way intending Academic Dishonesty.
Shafkat Haque and Adam Buschle

  * https://docs.oracle.com/javase/8/docs/api/java/io/BufferedReader.html (Used for buffered reader)

  * https://docs.oracle.com/javase/8/docs/api/java/io/BufferedWriter.html (Used for buffered writer)


ACKNOWLEDGEMENT:

-