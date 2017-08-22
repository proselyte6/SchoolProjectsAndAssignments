package studentOrientation.activities;

import studentOrientation.measures.CostI;
import studentOrientation.measures.DurationI;
import studentOrientation.measures.EffortI;
import studentOrientation.measures.CarbonFootprintI;

/**
 * This is the interface for the campus tour class. This class defines the choice the user can choose
 * through enums.
 */
public interface CampusTourI{
     public static enum Tour {BUS_RIDE, ON_FOOT} //the enum for specifying the choice for the campus tour
    
    
    //returns the cost of the campus tour
    public CostI returnCampusTourCost();
    
    //returns the duration of the campus tour
    public DurationI returnCampusTourDuration();
    
    //returns the effort of the campus tour
    public EffortI returnCampusTourEffort();
    
    //returns the carbon footprint of the campus tour
    public CarbonFootprintI returnCampusTourCarbonFootprint();
    
    //returns the choice picked for the style of the campus tour
    public Tour returnCampusTourEnumVal();
    
    //toString method for pritnign to stdout the choice picked for the style of the campus tour
    public String toString();

}