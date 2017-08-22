package studentOrientation.measures;

import studentOrientation.measures.EffortI;

/**
 * This is the class for the measure of effort.
 */
public class Effort implements EffortI{
    private int calories; //effort is measured in calories
    
    /**
     * Public constructor for effort.
     * @param caloriesIn - the value to make the calories equal to
     */
    public Effort(int caloriesIn){
        calories = caloriesIn;
    }
    
    /**
     * Getter method for effort
     * @return calories - the calories
     */
    public int returnEffort() {
        return calories;
    }
    
    /**
     * A method to add two efforts together.
     * @param e - the effort to add
     */
    public void addEffort(EffortI e){
        calories += e.returnEffort();
    }
    
    /**
     * toString() method that just returns the calories as a string
     * @return the calories
     */
    public String toString() {
        return Integer.toString(calories);
    }

}