CS442 Design Patterns
Fall 2016
PROJECT 3 README FILE

Due Date: Thursday, October 27th, 2016
Submission Date: Monday, October 24th, 2016
Grace Period Used This Project: -
Grace Period Remaining: 1 Days
Author(s): Shafkat Haque
e-mail(s): shaque4@binghamton.edu


PURPOSE:

This assignment was to test our knowledge of patterns and be able to apply it to a problem. I chose the builder pattern for this assignment because it already meets all the requirements. The orientation checklist is composed of four different activities but the checklist can be compose in any varied order (flexibility) thus requiring the builder pattern. Every file has been implemented to an interface except for the driver. We are to take 4 activities, with different options that vary amongst activities, construct the checklist in the user’s order and calculate the cost, effort, duration and carbon footprint of the orientation.


PERCENT COMPLETE:

I believe we have completed 100% of this project.

PARTS THAT ARE NOT COMPLETE:

-

BUGS:

-

FILES:

build.xml - needed for using ANT

/util/OrientationSchedulerI.java - the interface for the orientation scheduler. 

/util/OrientationScheduler.java - this is the class that holds all the information of the scheduler which are the user’s choices for book store, campus tour, dorm selector and course registration, the user’s preferences for each choice, and all the measures (cost, effort, duration, carbon footprint) associated with the orientation schedule/checklist.

/util/OrientationSchedulerBuilderI.java - the interface for the workshop/builder file.

/util/OrientationSchedulerBuilder.java - this class is the builder/workshop class. It takes a orientation scheduler as an argument in the construct method and then builds it according to the user’s preferences. The idea is to loop through the enum's values then process the activity in the order of 1st, 2nd, 3rd and 4th. Once done, prints the results of the orientation schedule.


/util/PriorityI.java - the interface for Priority.java. Defines an enum for user preferences (1st, 2nd, 3rd, 4th)

/util/Priority.java - this class encapsulates the enum and returning the enum for user preferences.

/driver/Driver.java - the main file that builds an instance of the orientation schedule with the user’s choices and preferences then creates a scheduler workshop that constructs the orientation schedule.

/measure/CostI.java - the interface for Cost.java

/measure/Cost.java - the class for cost. Holds the price of activities/schedule.

/measure/CarbonFootprintI.java - the interface for CarbonFootprint.java

/measure/CarbonFootprint.java - the class for carbon footprint. Holds the carbon footprint in tonnes of activities/schedule.

/measure/DurationI.java - the interface for Duration.java

/measure/Duration.java - the class for Duration. Holds the time of duration in minutes of activities/schedule.

/measure/EffortI.java - the interface for Effort.java

/measure/Effort.java - the class for effort. Holds the effort in calories of activities/schedule.

/activities/CampusTourI.java - the interface for CampusTour. It defines the enum for the campus tour choices which are bus ride and on foot.

/activities/CampusTour.java - the class for the activity, campus tour.Holds information for which option the user picked and the values for all the measures (which were hardcoded).

/activities/DormSelectorI.java - the interface for DormSelector. It defines the enum for the dorm selector choices which are office queue and playing an online game.

/activities/DormSelector.java - the class for the activity, dorm selector.Holds information for which option the user picked and the values for all the measures (which were hardcoded).

/activities/BookStoreI.java - the interface for BookStore. It defines the enum for the book store choices which are the university book store and mando books.

/activities/BookStore.java - the class for the activity, book store.Holds information for which option the user picked and the values for all the measures (which were hardcoded).

/activities/CourseRegistrationI.java - the interface for CourseRegistration. It defines the enum for the course registration choices which are the registrars office and the computer lab.

/activities/CourseRegistration.java - the class for the activity, campus tour.Holds information for which option the user picked and the values for all the measures (which were hardcoded).



SAMPLE OUTPUT:

Orientation Checklist
----------------------
1. Course Registration: Registrar's Office
2. Campus Tour: Bus Ride
3. Book Store : University Book Store
4. Dorm Selector: Office Queue

Total Cost : $774.5
Total Carbon FootPrint: 230 tonnes
Total Duration: 165 minutes
Total Effort: 170 calories

TO COMPILE:

//within the directory of haque_shafkat/studentOrientation
ant
ant jar

TO RUN:

//within the directory of haque_shafkat/studentOrientation
ant run

EXTRA CREDIT:

-

BIBLIOGRAPHY:

-

ACKNOWLEDGEMENT:

-