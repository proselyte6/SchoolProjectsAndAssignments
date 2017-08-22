package studentOrientation.measures;

import studentOrientation.measures.CarbonFootprintI;

/**
 * This is the class for the measure of carbon footprint.
 */
public class CarbonFootprint implements CarbonFootprintI{
    private int tonnes; //carbon footprint is CO2 measured in tonnes
    
    /**
     * Public constructor for carbon footprint.
     * @param tonnesIn - the value to make the tonnes equal to
     */
    public CarbonFootprint(int tonnesIn){
        tonnes = tonnesIn;
    }
    
    /**
     * Getter method for carbon footprint
     * @return tonnes - the amount of co2 in tonnes
     */
    public int returnCarbonFootprint() {
        return tonnes;
    }

    /**
     * A method to add two carbon footprints together.
     * @param cf - the carbon footprint to add to add
     */
    public void addCarbonFootprint(CarbonFootprintI cf){
        tonnes += cf.returnCarbonFootprint();
    }
    
    /**
     * toString() method that just returns the carbon footprint as a string
     * @return the tonnes
     */
    public String toString() {
        return Integer.toString(tonnes);
    }
}