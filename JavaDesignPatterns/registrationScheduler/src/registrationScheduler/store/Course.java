
package registrationScheduler.store;

import java.util.Vector;
import registrationScheduler.util.Logger;

/**
 * This is class for the course.
 * @authors Adam Buschle & Shafkat Haque
 */
public class Course {
    private Vector<Student> students; //the vector to hold the students
    private String name;

    
    /**
     * Default constructor to initalize a course.
     * @param nameC the name of the course
     */
    public Course(String nameC) {
				Logger.writeOutput("Entering constructor for 'Course' with name: " + nameC, Logger.DebugLevel.CONSTRUCTOR);
        students = new Vector<Student>();
        name = nameC;      
    }
    
		/**
		* @return returns the name of the course
		*/
		public String getName(){
			return name;
		}

    /**
     * Adds a student to the course.
     * @param student the student to be added to the course
     */
    public void addStudent(Student student) {
        students.add(student);
    }

    /**
     * Returns whether or not the course is full
     * @return true if the course is not full, else returns false
     */
		public boolean isAvailable(){
			return students.size() < 60;
		}
    
    /**
     * Returns the current size of the course
     * @return students.size() the current size of the course
     */
    public int size() {
        return students.size();
    }
    
		public static String indexToString(int i){
			switch(i){
				case 0: return "A";
				case 1: return "B";
				case 2: return "C";
				case 3: return "D";
				case 4: return "E";
				case 5: return "F";
				case 6: return "G";
				default:
					System.err.println("Error: invalid string index. No course with index: " + i);
					System.exit(1);
			}
			return "";
		}
}
