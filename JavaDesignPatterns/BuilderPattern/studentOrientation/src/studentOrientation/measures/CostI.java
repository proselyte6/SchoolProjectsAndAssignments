package studentOrientation.measures;

/**
 * Interface for one of the ways activities are measured: Cost.
 */
public interface CostI{
    
    //returns the cost
    public double returnCost();
    
    //adds two costs togetner
    public void addToCost(CostI c);
    
    //multiplies two costs together
    public void multiplyToCost(double percentage);
    
    //toString() method used for printing to stdout
    public String toString();
}