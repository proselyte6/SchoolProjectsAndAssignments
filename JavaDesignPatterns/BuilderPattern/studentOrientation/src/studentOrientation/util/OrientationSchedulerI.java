package studentOrientation.util;

import studentOrientation.util.PriorityI;

/**
 * This is the interface for the orientation scheduler.
 */
public interface OrientationSchedulerI{
    
    //computes the measures of adding the book store to the whole orientation
    public void checkOffBookStore();
    
   //computes the measures of adding the campus tour to the whole orientation
    public void checkOffCampusTour();
    
   //computes the measures of adding the dorm selector to the whole orientation
    public void checkOffDormSelector();
    
    //computes the measures of adding the course registration to the whole orientation
    public void checkOffCourseRegistration();
    
    //print the whole orientation schedule
    public void printResults();
    
    //return the enum/preference for an activity
    public PriorityI.Choice valueAt(int index);
}