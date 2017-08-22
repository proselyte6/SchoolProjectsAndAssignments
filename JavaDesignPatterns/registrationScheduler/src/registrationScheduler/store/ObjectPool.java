package registrationScheduler.store;

import java.util.concurrent.TimeUnit;
import registrationScheduler.util.Logger;

/**
 *This is the class for the ObjectPool
 *@authors Adam Buschle & Shafkat Haque
 */
public class ObjectPool {
    private static ObjectPool uniqueInstance; //The objecpool instance following singleton pattern
    private Course[] courses; // the courses
    private boolean[] checked; // a parallel array with courses to check if they are in use or not
    
    /**
     * Default Constructor to initialized objectpool. Follows singleton pattern.
     * Creates the courses and set them all to available.
     */
    private ObjectPool() {
				Logger.writeOutput("Entering constructor for 'ObjectPool'", Logger.DebugLevel.CONSTRUCTOR);
        courses = new Course[7];
        courses[0] = new Course("A"); //A
        courses[1] = new Course("B"); //B
        courses[2] = new Course("C"); //C
        courses[3] = new Course("D"); //D
        courses[4] = new Course("E"); //E
        courses[5] = new Course("F"); //F
        courses[6] = new Course("G"); //G
				checked = new boolean[7];
        
        for( int i = 0; i < 7; i ++){
            checked[i] = false;
        }
    }
    
    /**
     * Gets instance of objectpool
     */
    public static synchronized ObjectPool getCourses() {
        if (uniqueInstance == null){
            uniqueInstance = new ObjectPool();
        }
        return uniqueInstance;
    }
    
    /**
     * Checks if the course wanted is not at full capacity and is not being used by a thread.
     * Notifies it is being used and returns the course.
     * @param c the name of the course that needs to be borrowed
     */
    public synchronized Course borrowCourse(String c){
        for(int i = 0; i < 7; i++){
            if (courses[i].getName().equals(c)){
								while(checked[i] == true){
									try{
										TimeUnit.MILLISECONDS.sleep(10);
									}catch(InterruptedException e){
										System.err.println("Unexpected interupt in 'borrowCourse': " + e.toString());
									}
								}
                checked[i] = true;
                return courses[i];
            }
        }

				System.err.println("Error: could not find course with name: " + c);
				System.exit(1);
        return new Course(c);
    }
        
    /**
     * Returns the course that was being used by a thread
     * Notifies it is now available to use.
     * @param c the name of the course that is being returned
     */
    public void returnCourse(String c){
        for(int i = 0; i < 7; i++){
            if (courses[i].getName().equals(c)){
                checked[i] = false;
            }
        }
    }
    
    /**
     * Returns the number of courses not being used by a thread.
     * @return num number of courses available
     */
    public int availableNumberOfCourses() {
        int num = 0;
        for( int i = 0; i< 7; i++){
            if( !checked[i]){
                num++;
            }
        }
        return num;
    }

    /**
     * Returns the number of courses being used by a thread
     * @return num the number of courses being used by a thread.
     */
    public int getNumberIdle() {
        int num = 0;
        for( int i = 0; i< 7; i++){
            if( checked[i]){
                num++;
            }
        }
        return num;
    }

}
