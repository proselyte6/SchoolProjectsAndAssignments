package wordCount.visitors;

import wordCount.visitors.DSProcessingVisitorI;
import wordCount.util.FileProcessorI;
import wordCount.util.FileProcessor;
import wordCount.dsForStrings.Node;
import wordCount.dsForStrings.NodeI;
import wordCount.dsForStrings.Tree;

/**
 * This visitor is responsible for populating the data structure with the words from an input file.
 */
public class PopulateVisitor implements DSProcessingVisitorI{
    FileProcessorI fp; //file processor to use to process the input file
    
    /**
     * Constructor for populate visitor
     * @param fpIn - the file processor
     */
    public PopulateVisitor(FileProcessorI fpIn){
        fp = fpIn;
    }
    
    /**
     * This is the visit method, which takes a tree
     * it reads in by line of the input file, parses it by white space
     * then inserts the words into the tree.
     * @param tree - the tree to be populated
     */
    public void visit(Tree tree){
        String line = " ";
        
        while (true){
            line = fp.readLine();
            if (line == null){
                break;
            } else {
                String[] words = line.split("[ \t]+");
                for(int i = 0; i < words.length; i++){
                    tree.insert(words[i]);
                }
            }
            
        }
    }
    
    /**
     * A 'empty' method
     */
    public Tree returnTree() {
        Tree t = new Tree();
        return t;
    }

}