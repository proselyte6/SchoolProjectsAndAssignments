package studentOrientation.measures;

import studentOrientation.measures.DurationI;

/**
 * This is the class for the measure of duration/time.
 */
public class Duration implements DurationI{
    private int time; //time measured in minutes
    
    /**
     * Public constructor for duration.
     * @param timeIn - the value to make the time equal to
     */
    public Duration(int timeIn){
        time = timeIn;
    }
    
    /**
     * Getter method for the duration
     * @return time - the time
     */
    public int returnDuration() {
        return time;
    }
    
    /**
     * A method to add two durations together.
     * @param d - the duration to add
     */
    public void addDuration(DurationI d){
        time += d.returnDuration();
    }
    
    /**
     * toString() method that just returns the time as a string
     * @return the time
     */
    public String toString() {
        return Integer.toString(time);
    }
}