package studentOrientation.activities;

import studentOrientation.activities.DormSelectorI;
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
  * This activity has only two choices for the type of dorm selector: office queue and online game
  * This activitiy has its own cost, duration, effort and carbon footprint.
  */
public class DormSelector implements DormSelectorI{
    
    private static SelectorChoice choice; //enum for user's choice

    //each measure for the dorm selector
    private CostI cost;
    private DurationI duration;
    private EffortI effort;
    private CarbonFootprintI carbonFootprint;
    
    /** The public constructor for dorm selector.
     * The measures have been hardcoded for each choice.
     * @param choiceIn - the enum to set for the user's choice
     */
    public DormSelector(SelectorChoice choiceIn){
      
        choice = choiceIn;
        if (DormSelectorI.SelectorChoice.OFFICE_QUEUE == choice){
            cost = new Cost(50);
            duration = new Duration(60);
            effort = new Effort(100);
            carbonFootprint = new CarbonFootprint(10);
        } else if (DormSelectorI.SelectorChoice.ONLINE_GAME == choice){
            cost = new Cost(50);
            duration = new Duration(5);
            effort = new Effort(0);
            carbonFootprint = new CarbonFootprint(50);
        }
    }
    
    /** Getter method for the cost of the dorm selector
     * @return the cost
     */
    public CostI returnDormSelectorCost() {
        return cost;
    }
    
    /** Getter method for the duration of the dorm selector
     * @return the duration
     */
    public DurationI returnDormSelectorDuration() {
        return duration;
    }
    
    /** Getter method for the effort of the dorm selector
     * @return the effort
     */
    public EffortI returnDormSelectorEffort() {
        return effort;
    }
    
    /** Getter method for the carbon footprint of the dorm selector
     * @return the carbon footprint
     */
    public CarbonFootprintI returnDormSelectorCarbonFootprint() {
        return carbonFootprint;
    }
    
    /** Getter method for the user's choice of the dorm selector
     * @return the dorm selector cnoice
     */
    public SelectorChoice returnDormSelectorEnumVal(){
        return choice;
    }
    
    /** ToString method for printing out the user's dorm selector choice
     * @preturn user's dorm selector choice
     */
    public String toString() {
         
        String s = "";
        if (DormSelectorI.SelectorChoice.OFFICE_QUEUE == choice){
            s =  "Office Queue";
        } else if (DormSelectorI.SelectorChoice.ONLINE_GAME == choice){
            s = "Online Game";
        }
        return s;
    }

}