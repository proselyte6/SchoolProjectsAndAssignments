package genericDeser.driver;

import genericDeser.fileOperations.FileProcessorI;
import genericDeser.fileOperations.FileProcessor;
import genericDeser.util.FirstI;
import genericDeser.util.SecondI;
import genericDeser.util.PopulateObjectsI;
import genericDeser.util.Logger;
import genericDeser.util.First;
import genericDeser.util.Second;
import genericDeser.util.PopulateObjects;
import genericDeser.util.Logger;

public class Driver{
    public static void main(String args[]){
        int DEBUG_VALUE = 0;
        
        if (args.length != 2){
            System.out.println("Wrong number of command line arguments");
            System.exit(0);
        } else {
            try {
            DEBUG_VALUE = Integer.parseInt(args[1]);
            } catch (NumberFormatException e){
                e.printStackTrace(System.out);
                System.exit(1);
            }
        }
        
        Logger.setDebugValue(DEBUG_VALUE);
        FileProcessorI fp = new FileProcessor(args[0]);
        PopulateObjectsI po = new PopulateObjects();
        po.deserObjects(fp);
        po.printResults();
    }
}