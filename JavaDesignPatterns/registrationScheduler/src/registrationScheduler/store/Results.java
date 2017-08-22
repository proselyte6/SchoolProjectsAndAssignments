
package registrationScheduler.store;

import registrationScheduler.util.FileProcessor;
import registrationScheduler.util.Logger;
import registrationScheduler.store.StdoutDisplayInterface;
import registrationScheduler.store.FileDisplayInterface;
import registrationScheduler.store.Student;

public class Results implements StdoutDisplayInterface, FileDisplayInterface {
    // appropriate data structure as private data member
    private Student[] students;
    private FileProcessor fp;
		private int numStudents;
    
    // appropriate method to save prime number to the data structure

		/**
		* @return None
		*/
    public void writeScheduleToScreen() {
        float avgPreferenceScore = 0;
        
        for (int i = 0; i<80; i++){
            avgPreferenceScore += students[i].calculatePreferenceScore();
            Logger.writeOutput("Student_" + Integer.toString(i + 1) + " " + students[i].getAddedCourses().elementAt(0) + " " + students[i].getAddedCourses().elementAt(1) + " " + students[i].getAddedCourses().elementAt(2) + " " + students[i].getAddedCourses().elementAt(3) + " " + students[i].getAddedCourses().elementAt(4) + " "+ Integer.toString(students[i].calculatePreferenceScore()),Logger.DebugLevel.STORE);
        }
        System.out.println("Average preference score is: " + Float.toString(avgPreferenceScore / 80));
	// ..
    }
    
    public Results(FileProcessor fpC) {
				Logger.writeOutput("Entering constructor for 'Results'", Logger.DebugLevel.CONSTRUCTOR);
        students = new Student[80];
				numStudents = 0;
        fp = fpC;
    }
    
		/**
		* @return The student at the given index
		*/
    public Student getStudent(int index){
        return students[index];
    }
    
		/**
		* @return None
		*/
    public void addCourse(Student s, String c){
				Logger.writeOutput("Adding course to 'Results'", Logger.DebugLevel.RESULTS);
        s.addCourse(c);
    }

		/**
		* @return None
		*/
		public synchronized void addStudent(Student s){
				Logger.writeOutput("Adding student to 'Results'", Logger.DebugLevel.RESULTS);
			students[numStudents - 1] = s;
		}

		/**
		* @return Whether or not there are any more students to add
		*/
		public synchronized boolean beginAddStudent(){
			if(numStudents < 80){
				numStudents++;
				return true;
			}else{
				return false;
			}
		}

    /**
		* @return None
		*/
    private void calculatePreferenceScoreAvg() {
        double avgPreferenceScore = 0.0;
        
        for(int i = 0; i < 80; i++){
            avgPreferenceScore += students[i].calculatePreferenceScore();
        }
        
        avgPreferenceScore = avgPreferenceScore/80.0;
        
        System.out.println("The average preference value is: " + Double.toString(avgPreferenceScore));
    }

		/**
		* @return None
		*/
    public void writeScheduleToFile() {
        
        float avgPreferenceScore = 0;
        for (int n = 0; n < 80; n++) {
            avgPreferenceScore += students[n].calculatePreferenceScore();
            fp.writeLine("Student_" + Integer.toString(n + 1) + " " + students[n].getAddedCourses().elementAt(0) + " " + students[n].getAddedCourses().elementAt(1) + " " + students[n].getAddedCourses().elementAt(2) + " " + students[n].getAddedCourses().elementAt(3) + " " + students[n].getAddedCourses().elementAt(4) + " "+ Integer.toString(students[n].calculatePreferenceScore()));
        }
        fp.writeLine("Average preference score is: " + Float.toString(avgPreferenceScore / 80));
       
    }
}


