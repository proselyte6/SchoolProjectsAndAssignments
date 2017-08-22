package studentOrientation.util;

import studentOrientation.util.OrientationSchedulerWorkshopI;
import studentOrientation.util.PriorityI;


/**
 * This is the class for the Orientation scheduler workshop/builder.
 * This class has the construct method for building the scheduler
 */
public class OrientationSchedulerWorkshop implements OrientationSchedulerWorkshopI{
    
    //Empty constructor for OrientationSchedulerWorkshop
    public OrientationSchedulerWorkshop() {};

    /**
     * This is the construct method of the Orientation scheduler workshop,
     * The idea is to loop through the enum's values then process
     * the activity in the order of 1st, 2nd, 3rd and 4th.
     * Once done, print the results of the orientation schedule.
     * @param schedule - the orientation schedule to be constructed
     */
    public void construct(OrientationSchedulerI schedule){
        for (PriorityI.Choice c : PriorityI.Choice.values()){
            switch(c){
                case FIRST:
                    for (int i = 0; i<4; i++){
                        if (PriorityI.Choice.FIRST == schedule.valueAt(i) ){
                            switch(i){
                                case 0:
                                    schedule.checkOffBookStore();
                                    break;
                                case 1:
                                    schedule.checkOffCampusTour();
                                    break;
                                case 2:
                                    schedule.checkOffDormSelector();
                                    break;
                                case 3:
                                    schedule.checkOffCourseRegistration();
                                    break;
                            }
                        }
                    }
                    break;
                case SECOND:
                    for (int i = 0; i<4; i++){
                        if (PriorityI.Choice.SECOND == schedule.valueAt(i) ){
                            switch(i){
                                case 0:
                                    schedule.checkOffBookStore();
                                    break;
                                case 1:
                                    schedule.checkOffCampusTour();
                                    break;
                                case 2:
                                    schedule.checkOffDormSelector();
                                     break;
                                case 3:
                                    schedule.checkOffCourseRegistration();
                                     break;
                            }
                        }
                    }
                     break;
                case THIRD:
                        for (int i = 0; i<4; i++){
                            if (PriorityI.Choice.THIRD == schedule.valueAt(i)){
                                switch(i){
                                    case 0:
                                        schedule.checkOffBookStore();
                                         break;
                                    case 1:
                                        schedule.checkOffCampusTour();
                                         break;
                                    case 2:
                                        schedule.checkOffDormSelector();
                                         break;
                                    case 3:
                                        schedule.checkOffCourseRegistration();
                                         break;
                                }
                            }
                        }
                     break;

                case FOURTH:
                            for (int i = 0; i<4; i++){
                                if ( PriorityI.Choice.FOURTH == schedule.valueAt(i)){
                                    switch(i){
                                        case 0:
                                            schedule.checkOffBookStore();
                                             break;
                                        case 1:
                                            schedule.checkOffCampusTour();
                                             break;
                                        case 2:
                                            schedule.checkOffDormSelector();
                                             break;
                                        case 3:
                                            schedule.checkOffCourseRegistration();
                                             break;
                                    }
                                }
                            }
                     break;

            }
        }
        
        schedule.printResults();
        
    };
}