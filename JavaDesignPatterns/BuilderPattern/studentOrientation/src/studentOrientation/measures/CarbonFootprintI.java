package studentOrientation.measures;

/**
 * Interface for one of the ways activities are measured: Carbon Footprint.
 */
public interface CarbonFootprintI{
    
    //returns the carbon Footprint in tonnes
    public int returnCarbonFootprint();
    
    //adds two carbon footprints together
    public void addCarbonFootprint(CarbonFootprintI cf);
    
    //tostring method for printing to stdout
    public String toString();
}