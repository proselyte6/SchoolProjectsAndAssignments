package studentOrientation.activities;

import studentOrientation.measures.CostI;
import studentOrientation.measures.DurationI;
import studentOrientation.measures.EffortI;
import studentOrientation.measures.CarbonFootprintI;

/**
 * This is the interface for bookstore. It define the enum for the book store choice 
 * called store and has options: university book store or mando books
 */
public interface BookStoreI{
     public static enum Store {UNIVERSITY_BOOK_STORE, MANDO_BOOKS} //enums for the book store choice
    
    /// returns the cost of the book store
    public CostI returnBookStoreCost();
    
    //returns the duration of the book store
    public DurationI returnBookStoreDuration();
    
    //returns the effort of the book store
    public EffortI returnBookStoreEffort();
    
    //returns the carbon footprint of the book store
    public CarbonFootprintI returnBookStoreCarbonFootprint();
    
    //returns the enum of the user's dorm selector choice
    public Store returnBookStoreEnumVal();
    
    //tostring method for printing the user's dorm selector choice to stdout
    public String toString();
}