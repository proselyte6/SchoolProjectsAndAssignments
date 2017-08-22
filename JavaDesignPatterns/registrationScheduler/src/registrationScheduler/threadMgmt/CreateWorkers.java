
package registrationScheduler.threadMgmt;

import registrationScheduler.threadMgmt.WorkerThread;
import registrationScheduler.util.FileProcessor;
import registrationScheduler.util.Logger;
import registrationScheduler.store.Results;

public class CreateWorkers  {
  private FileProcessor fp;
  private Results r;

  // this class has the method startWokers(...)
  public CreateWorkers(FileProcessor fpC, Results rC){
			Logger.writeOutput("Creating 'CreateWorkers' class", Logger.DebugLevel.CONSTRUCTOR);
      fp = fpC;
      r = rC;
  }

  /**
	* @return None
	*/
  public void startWorkers(int numThreads){
		Thread wts[] = new Thread[numThreads];
  	for(int i = 0; i < numThreads; i++){
			wts[i] = new Thread(new WorkerThread(fp,r));
			wts[i].run();
		}
		//Wait for worker threads to finish
  	for(int i = 0; i < numThreads; i++){
			try{
				wts[i].join();
			}catch(InterruptedException e){
				System.err.println("Unexpected interuption in thread #" + i + ": " + e.toString());
			}
		}
  }

}
