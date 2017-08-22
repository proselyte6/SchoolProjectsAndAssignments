
package registrationScheduler.store;

import java.util.Vector;
import registrationScheduler.util.Logger;

/**
 * This class is for a Student. It contains the preference value for courses A,B,C,D labeled respectively.
 * It also has a private int for the preference score of the student which is based on the courses the student has.
 * I also made two vectors: One to keep the enrolled courses, and another one to keep the preference values of the respective enrolled course.
 * I made those two public because it is accessible in the output.txt file anyways.
 * @author Shafkat Haque
 */
public class Student {
    private int A;
    private int B;
    private int C;
    private int D;
    private int E;
    private int F;
    private int G;
    private int preferenceScore;
    private Vector<Integer> chosenCourseNumbers;
    private Vector<String> addedCourses;
    
    /** 
     *Constructor for the student. Initializes A,B,C,D,E,F,G the vectors and preferencescore as 0.
     * @param A the preference value for A
     * @param B the preference value for B
     * @param C the preference value for C
     * @param D the preference value for D
     * @param E the preference value for E
     * @param F the preference value for F
     * @param G the preference value for G
     */
    public Student(int A, int B, int C, int D, int E, int F, int G){
				Logger.writeOutput("Entering constructor for 'Student' ", Logger.DebugLevel.CONSTRUCTOR);
        this.A = A;
        this.B = B;
        this.C = C;
        this.D = D;
        this.E = E;
        this.F = F;
        this.G = G;
        chosenCourseNumbers = new Vector<Integer>();
        addedCourses = new Vector<String>();
        preferenceScore = 0;
    }
    
    /**
     * Acessor for preference value of A
     * @return A the preference value of A
     */
    public int preferenceNumberForA() {
        return this.A;
    }
    
    /**
     * Acessor for preference value of B
     * @return B the preference value of B
     */
    public int preferenceNumberForB() {
        return this.B;
    }
    
    /**
     * Acessor for preference value of C
     * @return C the preference value of C
     */
    public int preferenceNumberForC() {
        return this.C;
    }
    
    /**
     * Acessor for preference value of D
     * @return D the preference value of D
     */
    public int preferenceNumberForD() {
        return this.D;
    }

    /**
     * Acessor for preference value of E
     * @return E the preference value of E
     */
    public int preferenceNumberForE() {
        return this.E;
    }

    /**
     * Acessor for preference value of F
     * @return E the preference value of F
     */
    public int preferenceNumberForF() {
        return this.F;
    }

    /**
     * Acessor for preference value of G
     * @return E the preference value of G
     */
    public int preferenceNumberForG() {
        return this.G;
    }
    
    /**
     * Acessor for preference score of the student
     * @return preferenceScore the preference score of the student
     */
    public int returnPreferenceScore() {
        return this.preferenceScore;
    }
    
    /**
     * Accessor for courses the student has been added to
     * @return vector of the courses the student has been added to
     */
		public Vector<String> getAddedCourses(){
			return addedCourses;
		}

    /**
     * Calculates the preference score of the student by adding up the enrolled course preference values
     * @return preferenceScore the preferene score of the student
     */
    public int calculatePreferenceScore(){
        preferenceScore = 0;
        for(int i = 0; i < 5; i++){
            this.preferenceScore += chosenCourseNumbers.get(i);
        }
        return this.preferenceScore;
    }
    
    /**
     * Adds a course to the students courses as well as the corressponding preference value.
		 * @return None
     */
    public void addCourse(String course){
        addedCourses.add(course);
        
        if (course == "A"){
            chosenCourseNumbers.add(A);
        } else if (course == "B"){
            chosenCourseNumbers.add(B);
        } else if (course == "C"){
            chosenCourseNumbers.add(C);
        } else if (course == "D") {
            chosenCourseNumbers.add(D);
        } else if (course == "E") {
            chosenCourseNumbers.add(E);
        } else if (course == "F") {
            chosenCourseNumbers.add(F);
        } else if (course == "G") {
            chosenCourseNumbers.add(G);
        }
    }

    
    
    
}
