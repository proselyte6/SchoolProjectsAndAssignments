package studentOrientation.util;

/**
 * The interface for the prirority class. Priority will be used to see the user's preferences for the choices
 * they have for the orientation checklist. (ex. campus tour first, bus ride second... etc);
 */
public interface PriorityI{
    public static enum Choice {FIRST, SECOND, THIRD, FOURTH} //the enum for priority
    
    //returns a value from the enum choice
    public Choice returnPriority();
}