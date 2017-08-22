package studentOrientation.measures;

/**
 * Interface for one of the ways activities are measured: Effort.
 */
public interface EffortI{
    
    //returns the effort in calories
    public int returnEffort();
    
    //adds two efforts together
    public void addEffort(EffortI e);
    
    //toString method for printing the effort to stdout
    public String toString();
}