package studentOrientation.activities;

import studentOrientation.activities.BookStoreI;
import studentOrientation.measures.Cost;
import studentOrientation.measures.Duration;
import studentOrientation.measures.Effort;
import studentOrientation.measures.CarbonFootprint;
import studentOrientation.measures.CostI;
import studentOrientation.measures.DurationI;
import studentOrientation.measures.EffortI;
import studentOrientation.measures.CarbonFootprintI;

/**
 * This is the class for one of the activities for the orientation.
 * This activity has only two choices for the type of book store: university book store and mando books
 * This activitiy has its own cost, duration, effort and carbon footprint.
 * Hardcoded values for the measures.
 */
public class BookStore implements BookStoreI{
    
    private static Store storeChoice; //enum for the user's choice
   
    //each measure for the book store
    private CostI cost;
    private DurationI duration;
    private EffortI effort;
    private CarbonFootprintI carbonFootprint;
    
    /** The public constructor for book store.
     * The measures have been hardcoded for each type of book store.
     * @param storeChoiceIn - the enum for the user's choice
     */
    public BookStore(Store storeChoiceIn){
    
        storeChoice = storeChoiceIn;
        if (BookStoreI.Store.UNIVERSITY_BOOK_STORE == storeChoice){
            cost = new Cost(300);
            duration = new Duration(30);
            effort = new Effort(20);
            carbonFootprint = new CarbonFootprint(10);
        } else if (BookStoreI.Store.MANDO_BOOKS == storeChoice){
            cost = new Cost(300);
            duration = new Duration(30);
            effort = new Effort(20);
            carbonFootprint = new CarbonFootprint(100);
        }
    }
    
    /** Getter method for the cost of the book store
     * @return the cost
     */
    public CostI returnBookStoreCost() {
        return cost;
    }
    
    /** Getter method for the duration of the book store
     * @return the duration
     */
    public DurationI returnBookStoreDuration() {
        return duration;
    }
    
    /** Getter method for the effort of the book store
     * @return the effort
     */
    public EffortI returnBookStoreEffort() {
        return effort;
    }
    
    /** Getter method for the carbon footprint of the book store
     * @return the carbon footprint
     */
    public CarbonFootprintI returnBookStoreCarbonFootprint() {
        return carbonFootprint;
    }
    
    /** Getter method for the user's book store choice
     * @return the book store choice
     */
    public Store returnBookStoreEnumVal(){
        return storeChoice;
    }
    
    /** ToString method for printing out the user's book store choice
     * @return user's book store choice
     */
    public String toString() {
        
        String s = "";
        if (BookStoreI.Store.UNIVERSITY_BOOK_STORE == storeChoice){
            s = "University Book Store";
        } else if (BookStoreI.Store.MANDO_BOOKS == storeChoice){
            s = "Mando Books";
        }
        return s;
    }
    



}