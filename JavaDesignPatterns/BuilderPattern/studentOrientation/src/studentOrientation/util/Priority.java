package studentOrientation.util;

import studentOrientation.util.PriorityI;

/**
 * The priority class. This class will be used to capture the user's preferences for each orientation activity
 * ex. what the user wants first, second, third and fourth. These values are defined using an enum
 * that is in the interface of this class.
 */
public class Priority implements PriorityI{

    private static Choice choice; //the enum value for the priority/preference

    /**
     * The public constructor for choice
     * @param the enum choice
     */
    public Priority(Choice choiceIn){
        choice = choiceIn;
    }

    /**
     * The getter method for this class that returns the choice.
     */
    public Choice returnPriority(){
        return choice;
}
}