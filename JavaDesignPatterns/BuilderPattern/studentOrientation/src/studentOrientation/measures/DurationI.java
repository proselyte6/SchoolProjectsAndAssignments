package studentOrientation.measures;

/**
 * Interface for one of the ways activities are measured: Duration.
 */
public interface DurationI{
    
    //returns the duration
    public int returnDuration();
    
    //adds two durations together
    public void addDuration(DurationI d);
    
    //toString method used for printing to stdout
    public String toString();
}