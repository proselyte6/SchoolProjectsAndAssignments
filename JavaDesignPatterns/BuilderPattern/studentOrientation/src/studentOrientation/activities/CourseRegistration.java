package studentOrientation.activities;

import studentOrientation.activities.CourseRegistrationI;
import studentOrientation.measures.Cost;
import studentOrientation.measures.Duration;
import studentOrientation.measures.Effort;
import studentOrientation.measures.CarbonFootprint;
import studentOrientation.measures.CostI;
import studentOrientation.measures.DurationI;
import studentOrientation.measures.EffortI;
import studentOrientation.measures.CarbonFootprintI;

/**
 * This is the class for one of the activities for the orientation.
 * This activity has only two choices for the type of course registration: the registrars office or the computer labs
 * This activitiy has its own cost, duration, effort and carbon footprint.
 * All the hardcoded values are for the measures
 */
public class CourseRegistration implements CourseRegistrationI{
    
    
    private static RegistrationChoice registrationChoice;// enum for user's choice

    //each measure for course registration
    private CostI cost;
    private DurationI duration;
    private EffortI effort;
    private CarbonFootprintI carbonFootprint;
    
    /** The public constructor for Course registration.
     * The measures have been hardcoded for each course registration option.
     * @param registrationChoiceIn - the enum for the user's choice
     */
    public CourseRegistration(RegistrationChoice registrationChoiceIn){
        
        registrationChoice = registrationChoiceIn;
        if (CourseRegistrationI.RegistrationChoice.REGISTRARS_OFFICE == registrationChoice){
            cost = new Cost(400);
            duration = new Duration(60);
            effort = new Effort(50);
            carbonFootprint = new CarbonFootprint(10);
        } else if (CourseRegistrationI.RegistrationChoice.COMPUTER_LAB == registrationChoice){
            cost = new Cost(400);
            duration = new Duration(30);
            effort = new Effort(10);
            carbonFootprint = new CarbonFootprint(10);
        }
    }
    
    /** Getter method for the cost of the Course registration
     * @return the cost
     */
    public CostI returnCourseRegistrationCost() {
        return cost;
    }
    
    /** Getter method for the durationof the Course registration
     * @return the duration
     */
    public DurationI returnCourseRegistrationDuration() {
        return duration;
    }
    
    /** Getter method for the effort of the Course registration
     * @return the effort
     */
    public EffortI returnCourseRegistrationEffort() {
        return effort;
    }
    
    /** Getter method for the carbon footprint of the Course registration
     * @return the carbon footprint
     */
    public CarbonFootprintI returnCourseRegistrationCarbonFootprint() {
        return carbonFootprint;
    }
    
    /** Getter method for the user's choice of the Course registration
     * @return the tour cnoice
     */
    public RegistrationChoice returnCourseRegistrationEnumVal() {
        return registrationChoice;
    }
    
    /** ToString method for printing out the user's campus Course registration
     * @return user's Course registration choice
     */
    public String toString(){
 
        String s = "";
        if (CourseRegistrationI.RegistrationChoice.REGISTRARS_OFFICE == registrationChoice){
            s = "Registrar's Office";
        } else if (CourseRegistrationI.RegistrationChoice.COMPUTER_LAB == registrationChoice){
            s = "Computer Lab";
        }
        return s;
    }
}