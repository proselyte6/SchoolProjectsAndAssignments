
package registrationScheduler.driver;

import registrationScheduler.util.FileProcessor;
import registrationScheduler.util.Logger;
import registrationScheduler.threadMgmt.CreateWorkers;
import registrationScheduler.store.Results;

public class Driver{

	public static void main(String args[]) {
		int numThreads = 0;
		int debugVal = 0;
		if(args.length != 4){
			System.out.println("Parameters should include: <input file> <output file> <number of threads> <debug value>");
			System.exit(0);
		}

		try{
			numThreads = Integer.parseInt(args[2]);
			debugVal = Integer.parseInt(args[3]);
		}catch(NumberFormatException e){
            e.printStackTrace(System.out);
			System.exit(1);
		}

		if(numThreads < 1 || numThreads > 3){
			System.err.println("Error: Number of Threads should be between 1 and 3");
			System.exit(1);
		}	

		if(debugVal < 0 || debugVal > 4){
			System.err.println("Error: Debug Value should be between 0 and 4");
			System.exit(1);
		}
        
    Logger.setDebugValue(debugVal);
    FileProcessor fp = new FileProcessor(args[0],args[1]);
    Results r = new Results(fp);
    CreateWorkers cw = new CreateWorkers(fp, r);
    cw.startWorkers(numThreads);
    
    r.writeScheduleToFile();
		r.writeScheduleToScreen();
        

	} // end main(...)

} // end public class Driver

