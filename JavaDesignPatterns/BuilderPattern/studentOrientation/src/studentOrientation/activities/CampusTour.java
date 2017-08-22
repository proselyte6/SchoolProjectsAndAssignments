package studentOrientation.activities;

import studentOrientation.activities.CampusTourI;
import studentOrientation.measures.CostI;
import studentOrientation.measures.DurationI;
import studentOrientation.measures.EffortI;
import studentOrientation.measures.CarbonFootprintI;
import studentOrientation.measures.Cost;
import studentOrientation.measures.Duration;
import studentOrientation.measures.Effort;
import studentOrientation.measures.CarbonFootprint;

/**
 * This is the class for one of the activities for the orientation.
 * This activity has only two choices for the type of campus tour: bus ride and on foot
 * This activitiy has its own cost, duration, effort and carbon footprint.
 *If a bus ride is chosen, the price if $2, while on foot is 10 cents.
 */
public class CampusTour implements CampusTourI{
   
    
    private static Tour tourChoice; //enum for the user's choice
    
    //each measure for the campus tour
    private CostI cost;
    private DurationI duration;
    private EffortI effort;
    private CarbonFootprintI carbonFootprint;
    
    /** The public constructor for Campustour.
     * The measures have been hardcoded for each type of tour.
     * @param tourChoiceIn - the enum for the user's choice
     */
    public CampusTour(Tour tourChoiceIn){
      
        tourChoice = tourChoiceIn;
        if (CampusTourI.Tour.BUS_RIDE == tourChoice){
            cost = new Cost(2);
            duration = new Duration(15);
            effort = new Effort(0);
            carbonFootprint = new CarbonFootprint(200);
        } else if (CampusTourI.Tour.ON_FOOT == tourChoice){
            cost = new Cost(.1);
            duration = new Duration(60);
            effort = new Effort(300);
            carbonFootprint = new CarbonFootprint(10);
        }
    }
    
    /** Getter method for the cost of the campus tour
     * @return the cost
     */
    public CostI returnCampusTourCost() {
        return cost;
    }
    
    /** Getter method for the durationof the campus tour
     * @return the duration
     */
    public DurationI returnCampusTourDuration() {
        return duration;
    }
    
    /** Getter method for the effort of the campus tour
     * @return the effort
     */
    public EffortI returnCampusTourEffort() {
        return effort;
    }
    
    /** Getter method for the carbon footprint of the campus tour
     * @return the carbon footprint
     */
    public CarbonFootprintI returnCampusTourCarbonFootprint() {
        return carbonFootprint;
    }
    
    /** Getter method for the user's choice of the campus tour
     * @return the tour cnoice
     */
    public Tour returnCampusTourEnumVal(){
        return tourChoice;
    }
    
    /** ToString method for printing out the user's campus tour choice
     * @return user's campus tour choice
     */
    public String toString(){
         
        String s = "";
        if (CampusTourI.Tour.BUS_RIDE == tourChoice){
            s =  "Bus Ride";
        } else if (CampusTourI.Tour.ON_FOOT == tourChoice){
            s = "On Foot";
        }
        return s;

    }
    
    
}