package studentOrientation.measures;

import studentOrientation.measures.CostI;

/**
 * This is the class for the measure of cost/price.
 */
public class Cost implements CostI{
    private double cost; //private double variable cost to represent the price/money
    
    /**
     * Public constructor for cost.
     * @param costIn - the value to make the cost equal to
     */
    public Cost(double costIn){
        cost = costIn;
    }
    
    /**
     * Getter method for the cost
     * @return cost - the cost
     */
    public double returnCost() {
        return cost;
    }
    
    /**
     * A method to add two costs together.
     * @param c - the cost to add
     */
    public void addToCost(CostI c){
        cost += c.returnCost();
    }
    
    /**
     * A method to multiple a percentage to a cost.
     * @param percentage - the percentage to multiple the cost by
     */
    public void multiplyToCost(double percentage){
        cost *= percentage;
    }
    
    /**
     * toString() method that just returns the cost as a string
     * @return the cost
     */
    public String toString() {
        return Double.toString(cost);
    }

}