package wordCount.driver;

import wordCount.visitors.DSProcessingVisitorI;
import wordCount.visitors.PopulateVisitor;
import wordCount.visitors.WordCountVisitor;
import wordCount.util.FileProcessorI;
import wordCount.util.FileProcessor;
import wordCount.dsForStrings.Tree;
import wordCount.visitors.TestVisitor;
import wordCount.visitors.CloneAndObserveVisitor;

/**  (1) Validate that command line inputs for input and output file names.
 * (2) Create the elements (the trees and file processor)
 * (3) Create the two visitor instances
 * (4) Use the performance measurement loop given above.
 * (5) Test that the observer pattern and cloning works by using another visitor and writing the results of the tree and the clone tree to 2 different output files.
**/


public class Driver{
    public static void main(String args[]){
        int NUM_ITERATIONS = 0;
        
        if (args.length != 3){
            System.out.println("Wrong number of command line arguments");
            System.exit(0);
        } else {
            
            try {
                NUM_ITERATIONS = Integer.parseInt(args[2]);
            } catch (NumberFormatException e){
                e.printStackTrace(System.out);
                System.exit(1);
            }
        }
        
        
        
        long startTime = System.currentTimeMillis();
        for(int i = 0; i < NUM_ITERATIONS; i++){
            FileProcessorI fp = new FileProcessor(args[0],args[1]);
            Tree tree = new Tree();
            DSProcessingVisitorI pv = new PopulateVisitor(fp);
            DSProcessingVisitorI wcv = new WordCountVisitor(fp);
            tree.accept(pv);
            tree.accept(wcv);
        }
        long finishTime = System.currentTimeMillis();
        long total_time = (finishTime-startTime)/NUM_ITERATIONS;
        System.out.println("Total time: " + Long.toString(total_time));
        
        FileProcessorI fp = new FileProcessor(args[0],args[1]);
        Tree tree = new Tree();
        DSProcessingVisitorI pv = new PopulateVisitor(fp);
        DSProcessingVisitorI wcv = new WordCountVisitor(fp);
        tree.accept(pv);
        tree.accept(wcv);
        
        DSProcessingVisitorI cv = new CloneAndObserveVisitor();
        tree.accept(cv);
        
        DSProcessingVisitorI tv = new TestVisitor();
        tree.accept(tv);
        
        Tree backupTree = cv.returnTree();
        fp.writeToNewFile("originalTree.txt", tree);
        fp.writeToNewFile("backupTree.txt", backupTree);
        
        
        
    }

}