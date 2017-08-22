package studentOrientation.activities;

import studentOrientation.measures.CostI;
import studentOrientation.measures.DurationI;
import studentOrientation.measures.EffortI;
import studentOrientation.measures.CarbonFootprintI;

/**
 * The interface for the dorm selector.
 */
public interface DormSelectorI{
    //the user has two choices: queue in the office line or play the online game
    public static enum SelectorChoice {OFFICE_QUEUE, ONLINE_GAME}

    // return the cost
    public CostI returnDormSelectorCost();
    
    //return the duration
    public DurationI returnDormSelectorDuration();
    
    //return the effort
    public EffortI returnDormSelectorEffort();
    
    //return the carbon footprint
    public CarbonFootprintI returnDormSelectorCarbonFootprint();
    
    //return tbe user's choice for the dorm selector
    public SelectorChoice returnDormSelectorEnumVal();
    
    //tostring method for printing the user's dorm selector choice to stdout
    public String toString();
}
