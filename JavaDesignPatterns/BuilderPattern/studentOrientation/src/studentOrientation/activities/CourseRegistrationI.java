package studentOrientation.activities;

import studentOrientation.measures.CostI;
import studentOrientation.measures.DurationI;
import studentOrientation.measures.EffortI;
import studentOrientation.measures.CarbonFootprintI;

/**
 * The interface for course registration. There are two options for the course registration
 * waiting on line to the registrars office or going to the computer lab.
 */
public interface CourseRegistrationI{
    public static enum RegistrationChoice {REGISTRARS_OFFICE , COMPUTER_LAB  } //the enum to specify the user's choice
    
    //return the cost of course registration
    public CostI returnCourseRegistrationCost();
    
    //return the duration for course registration
    public DurationI returnCourseRegistrationDuration();
    
    //return the effort for the course registration
    public EffortI returnCourseRegistrationEffort();
    
    //return the carbon footprint for the course registration
    public CarbonFootprintI returnCourseRegistrationCarbonFootprint();
    
    //return the enum value for the user's course registration choice
    public RegistrationChoice returnCourseRegistrationEnumVal();
    
    //tostirng method ot print the user's course registration choice
    public String toString();
}