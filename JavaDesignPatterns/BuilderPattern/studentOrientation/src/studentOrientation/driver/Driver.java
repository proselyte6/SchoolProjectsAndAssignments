package studentOrientation.driver;

import studentOrientation.util.OrientationScheduler;
import studentOrientation.util.OrientationSchedulerWorkshop;
import studentOrientation.util.OrientationSchedulerI;
import studentOrientation.util.OrientationSchedulerWorkshopI;
import studentOrientation.activities.BookStoreI;
import studentOrientation.activities.CampusTourI;
import studentOrientation.activities.DormSelectorI;
import studentOrientation.activities.CourseRegistrationI;
import studentOrientation.util.PriorityI;
import studentOrientation.measures.CostI;
import studentOrientation.measures.DurationI;
import studentOrientation.measures.EffortI;
import studentOrientation.measures.CarbonFootprintI;

/**
 * The main driver class.
 **/
public class Driver{
    
    /**
     * The main function where we create an instance of an orientation schedule and the workshop (builder), then call the workshop to build/construct the orientation schedule/
     **/
    public static void main(String args[]){
        
        
        /**
         * First parameter is the book store choice: "BookStoreI.Store.UNIVERISTY_BOOK_STORE" or "BookStoreI.Store.MANDO_BOOKS"
         * Second parameter is the campus tour choice: "CampusTourI.Tour.BUS_RIDE" or "CampusTourI.Tour.ON_FOOT"
         * Third parameter is the dorm selector choice: "DormSelectorI.SelectorChoice.OFFICE_QUEUE" or "DormSelectorI.SelectorChoice.ONLINE_GAME"
         * Fourth parameter is the course registration choice: "CourseRegistrationI.RegistrationChoice.REGISTRARS_OFFICE" or "CourseRegistrationI.RegistrationChoice.COMPUTER_LAB"
         * fifth parameter is the array of user choices where index 0,1,2,3 correspond to bookstore, campus tour, dorm selector and course registration respectively.
         * the enum values for this array can be (must be different from eac other) : "PriorityI.Choice.FIRST", "PriorityI.Choice.SECOND", 
         * "PriorityI.Choice.THIRD" , "PriorityI.Choice.FOURTH"
         */
        OrientationSchedulerI os = new OrientationScheduler(BookStoreI.Store.UNIVERSITY_BOOK_STORE, CampusTourI.Tour.BUS_RIDE, DormSelectorI.SelectorChoice.OFFICE_QUEUE, CourseRegistrationI.RegistrationChoice.REGISTRARS_OFFICE, new PriorityI.Choice[] {PriorityI.Choice.THIRD, PriorityI.Choice.SECOND, PriorityI.Choice.FOURTH, PriorityI.Choice.FIRST});
        OrientationSchedulerWorkshopI shop = new OrientationSchedulerWorkshop();
        shop.construct(os);
    }


}