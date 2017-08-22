package studentOrientation.util;

import studentOrientation.util.OrientationSchedulerI;
import studentOrientation.activities.BookStore;
import studentOrientation.activities.CampusTour;
import studentOrientation.activities.CourseRegistration;
import studentOrientation.activities.DormSelector;
import studentOrientation.activities.BookStoreI;
import studentOrientation.activities.CampusTourI;
import studentOrientation.activities.CourseRegistrationI;
import studentOrientation.activities.DormSelectorI;
import studentOrientation.measures.CarbonFootprint;
import studentOrientation.measures.Cost;
import studentOrientation.measures.Duration;
import studentOrientation.measures.Effort;
import studentOrientation.measures.CarbonFootprintI;
import studentOrientation.measures.CostI;
import studentOrientation.measures.DurationI;
import studentOrientation.measures.EffortI;
import studentOrientation.util.Priority;
import studentOrientation.util.PriorityI;

/**
 * This is the class for the orientation schedule.
 * It contains the options and preferences for the book store, campus tour,
 * dorm selector and course registration. It also has a total cost, carbon footprint,
 * duration, and effort.
 */
public class OrientationScheduler implements OrientationSchedulerI{
    
    //the activities of the orientation schedule
    private BookStoreI bookStore;
    private CampusTourI campusTour;
    private CourseRegistrationI courseRegistration;
    private DormSelectorI dormSelector;
    
    private PriorityI.Choice[] priorities; //the user's preferences
    
    //the total measures of the orientation schedule
    private CostI totalCost;
    private CarbonFootprintI totalCarbonFootprint;
    private DurationI totalDuration;
    private EffortI totalEffort;

    /**
     * The public constructor for the orientation scheduler. It takes the 4 activities,
     * and an array of priorities/preferences where the indexs reprsent a choice
     * Here position: 0 - book store preference, 1 - campus tour preference, 2 - dorm selector 
     * preference, 3 - coure registration.
     *@param bookStoreIn - the enum for the user's book store choice
     *@param campusTourIn - the enum for the user's campus tour choice
     *@param dormSelectorIn - the enum for the user's dorm selector choice
     *@param courseRegistrationIn - the enum for the user's course registration choice
     *@param prioritiesIn - an array that hold the preferences of the user's where the indexes
     *                      0,1,2,3 is the priority enum for what the user wants for book store
     *                      campus tour, dorm selector and course registration respectively.
     */
    public OrientationScheduler(BookStoreI.Store bookStoreIn,
                                CampusTourI.Tour campusTourIn,
                               
                                DormSelectorI.SelectorChoice dormSelectorIn,
                                
                                CourseRegistrationI.RegistrationChoice courseRegistrationIn,
                                PriorityI.Choice[] prioritiesIn ) {
        
        //make sure all the values in the priority enum are different
        if (prioritiesIn[0] == prioritiesIn[1] ||
            prioritiesIn[0] == prioritiesIn[2] ||
            prioritiesIn[0] == prioritiesIn[3] ||
            prioritiesIn[1] == prioritiesIn[2] ||
            prioritiesIn[1] == prioritiesIn[3] ||
            prioritiesIn[2] == prioritiesIn[3] ){
            System.out.println("The values for the array of preference choices must all be different.");
            System.exit(1);
        }
        
        priorities = prioritiesIn;
        
        bookStore = new BookStore(bookStoreIn);
        campusTour = new CampusTour(campusTourIn);
        dormSelector = new DormSelector(dormSelectorIn);
        courseRegistration = new CourseRegistration(courseRegistrationIn);
     
        totalCost = new Cost(0);
        totalCarbonFootprint = new CarbonFootprint(0);
        totalDuration = new Duration(0);
        totalEffort = new Effort(0);
    }
    
    /**
     * "Checks off" book store from the orientation checklist.
     * if the user choose university book store, he must pay 5% more
     * add all the measures of the book store to the total measures of the orientation schedule.
     */
    public void checkOffBookStore(){
        totalCost.addToCost(bookStore.returnBookStoreCost());
        
        if (BookStoreI.Store.UNIVERSITY_BOOK_STORE == bookStore.returnBookStoreEnumVal()){
            totalCost.multiplyToCost(1.05);
        }
        totalCarbonFootprint.addCarbonFootprint(bookStore.returnBookStoreCarbonFootprint());
        
        totalDuration.addDuration(bookStore.returnBookStoreDuration());
        
        totalEffort.addEffort(bookStore.returnBookStoreEffort());
    }
    

    /**
     * "Checks off" campus tour from the orientation checklist.
     * add all the measures of the campus tour to the total measures of the orientation schedule.
     */
    public void checkOffCampusTour(){
        totalCost.addToCost(campusTour.returnCampusTourCost());
        
        totalCarbonFootprint.addCarbonFootprint(campusTour.returnCampusTourCarbonFootprint());
        
        totalDuration.addDuration(campusTour.returnCampusTourDuration());
        
        totalEffort.addEffort(campusTour.returnCampusTourEffort());
    }

    /**
     * "Checks off" dorm selector from the orientation checklist.
     * if the user chooses to play the online game, he must pay 2% surcharge
     * add all the measures of the dorm selector to the total measures of the orientation schedule.
     */
    public void checkOffDormSelector(){
        totalCost.addToCost(dormSelector.returnDormSelectorCost());
        if (DormSelectorI.SelectorChoice.ONLINE_GAME == dormSelector.returnDormSelectorEnumVal()){
            totalCost.multiplyToCost(1.02);
        }
        
        totalCarbonFootprint.addCarbonFootprint(dormSelector.returnDormSelectorCarbonFootprint());
        
        totalDuration.addDuration(dormSelector.returnDormSelectorDuration());
        
        totalEffort.addEffort(dormSelector.returnDormSelectorEffort());
    }
 
    /**
     * "Checks off" course registration from the orientation checklist.
     * if the user chooses to go to the registrars office, he gets 3% off.
     * add all the measures of the course registration to the total measures of the orientation schedule.
     */
    public void checkOffCourseRegistration(){
        totalCost.addToCost(courseRegistration.returnCourseRegistrationCost());
        if(CourseRegistrationI.RegistrationChoice.REGISTRARS_OFFICE == courseRegistration.returnCourseRegistrationEnumVal()){
            totalCost.multiplyToCost(.97);
        }
        
        totalCarbonFootprint.addCarbonFootprint(courseRegistration.returnCourseRegistrationCarbonFootprint());
        
        totalDuration.addDuration(courseRegistration.returnCourseRegistrationDuration());
        
        totalEffort.addEffort(courseRegistration.returnCourseRegistrationEffort());
    }
    /**
     * Print the orientation checklist, in order with what the user specified and the total measures of the orientation checklist.
     */
    public void printResults(){
        System.out.println("Orientation Checklist");
        System.out.println("----------------------");
        
        
        
        for (PriorityI.Choice c : PriorityI.Choice.values()){
            switch(c){
                case FIRST:
                    for (int i = 0; i<4; i++){
                        if (PriorityI.Choice.FIRST == priorities[i] ){
                            switch(i){
                                case 0:
                                     System.out.println("1. Book Store : "+bookStore.toString());
                                     break;
                                case 1:
                                    System.out.println("1. Campus Tour: "+campusTour.toString());
                                     break;
                                case 2:
                                  System.out.println("1. Dorm Selector: "+dormSelector.toString());
                                     break;
                                case 3:
                                   System.out.println("1. Course Registration: "+courseRegistration.toString());
                                     break;
                            }
                        }
                    }
                     break;
                case SECOND:
                    for (int i = 0; i<4; i++){
                        if (PriorityI.Choice.SECOND == priorities[i]){
                            switch(i){
                                case 0:
                                    System.out.println("2. Book Store : "+bookStore.toString());
                                     break;
                                case 1:
                                    System.out.println("2. Campus Tour: "+campusTour.toString());
                                     break;
                                case 2:
                                    System.out.println("2. Dorm Selector: "+dormSelector.toString());
                                     break;
                                case 3:
                                    System.out.println("2. Course Registration: "+courseRegistration.toString());
                                     break;
                            }
                        }
                    }
                     break;
                    case THIRD:
                        for (int i = 0; i<4; i++){
                            if (PriorityI.Choice.THIRD == priorities[i]){
                                switch(i){
                                    case 0:
                                        System.out.println("3. Book Store : "+bookStore.toString());
                                         break;
                                    case 1:
                                        System.out.println("3. Campus Tour: "+campusTour.toString());
                                         break;
                                    case 2:
                                        System.out.println("3. Dorm Selector: "+dormSelector.toString());
                                         break;
                                    case 3:
                                        System.out.println("3. Course Registration: "+courseRegistration.toString());
                                         break;

                                }
                            }
                        }
                         break;
                        case FOURTH:
                        for (int i = 0; i<4; i++){
                                if ( PriorityI.Choice.FOURTH == priorities[i]){
                                    switch(i){
                                        case 0:
                                            System.out.println("4. Book Store : "+bookStore.toString());
                                             break;
                                        case 1:
                                            System.out.println("4. Campus Tour: "+campusTour.toString());
                                             break;
                                        case 2:
                                            System.out.println("4. Dorm Selector: "+dormSelector.toString());
                                             break;
                                        case 3:
                                            System.out.println("4. Course Registration: "+courseRegistration.toString());
                                             break;

                                    }
                                }
                                
                            }
                     break;
                    }
        }
        

        
            
        
        System.out.println();
        System.out.println("Total Cost : $" + totalCost.toString());
        System.out.println("Total Carbon FootPrint: "+ totalCarbonFootprint.toString()+" tonnes");
        System.out.println("Total Duration: "+ totalDuration.toString()+" minutes");
        System.out.println("Total Effort: "+ totalEffort.toString()+" calories");

    }
    
    /**
     * Getter method for obtaining a preference from the array.
     * @param the index
     * @return the preference at the index
     */
    public PriorityI.Choice valueAt(int index){
        return priorities[index];
    }
}