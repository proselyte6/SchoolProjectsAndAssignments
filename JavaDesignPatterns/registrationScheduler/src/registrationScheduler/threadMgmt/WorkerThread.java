
package registrationScheduler.threadMgmt;

import registrationScheduler.util.FileProcessor;
import registrationScheduler.util.Logger;
import registrationScheduler.store.Results;
import registrationScheduler.store.Student;
import registrationScheduler.store.Course;
import registrationScheduler.store.ObjectPool;


public class WorkerThread implements Runnable  {
	FileProcessor fileP;
	Results results;

	public WorkerThread(FileProcessor filePIn, Results resultsIn){
		Logger.writeOutput("Creating 'WorkerThread' class", Logger.DebugLevel.CONSTRUCTOR);
		fileP = filePIn;
		results = resultsIn;
	}
	
	/**
	* @return None
	*/
  public void run() {
		Logger.writeOutput("'run()' being called in WorkerThread", Logger.DebugLevel.RUN);

		while(results.beginAddStudent()){
			String studentString = fileP.readLine();
			String[] prefS = studentString.split("[ \t]+");
			int[] prefI = new int[7];
			for(int i = 0; i < 7; i++){
				prefI[i] = Integer.parseInt(prefS[i + 1]);
			}
			Student newStudent = new Student(prefI[0],prefI[1],prefI[2],prefI[3],prefI[4],prefI[5],prefI[6]);
			int numberLeft = 5;
			int maxScore = 5;
			while(numberLeft > 0){
				for(int i = 0; i < 7; i++){
					Course currCourse = ObjectPool.getCourses().borrowCourse(Course.indexToString(i));
					if(prefI[i] <= maxScore && currCourse.isAvailable()){
						newStudent.addCourse(currCourse.getName());
						currCourse.addStudent(newStudent);
						numberLeft--;
					}
					ObjectPool.getCourses().returnCourse(currCourse.getName());
				}
				maxScore++;
			}
			results.addStudent(newStudent);	
		}
  }
}
