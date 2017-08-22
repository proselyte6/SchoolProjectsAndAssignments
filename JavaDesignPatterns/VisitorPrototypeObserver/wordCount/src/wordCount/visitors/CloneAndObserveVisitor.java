package wordCount.visitors;

import wordCount.visitors.DSProcessingVisitorI;
import wordCount.util.FileProcessorI;
import wordCount.util.FileProcessor;
import wordCount.dsForStrings.Node;
import wordCount.dsForStrings.Tree;

/**
 * This visitor is used for cloning and setting up the subject - observer relationship
 */
public class CloneAndObserveVisitor implements DSProcessingVisitorI{
    private Tree backupTree; //the 'soon to be cloned' tree
    
    /**
     * Constructor for this visitor
     */
    public CloneAndObserveVisitor(){
        backupTree = new Tree();
    }
    
    /**
     * the visit method takes the root of the original tree and pases it to a helper function
     */
    public void visit(Tree tree) {
        Node root = tree.returnRoot();
        cloneTree_(root);
    }
    
    /**
     * This helper function clones the node passed to it from the original tree.
     * it traverses the original tree (inorder) while cloning its nodes and isnerting it into the back up
     */
    private void cloneTree_(Node n){
       
        if (n == null){
            return;
        }
        try{
            Node clone = (Node) n.clone();
            n.registerObserver(clone);
            cloneTree_(n.getLeftChild());
            backupTree.insert(clone);
            cloneTree_(n.getRightChild());
        } catch (CloneNotSupportedException e){
            e.printStackTrace();
            System.exit(1);
        }
        
    }
    
    /**
     * Getter for the back up tree
     */
    public Tree returnTree() {
        return backupTree;
    }
    
}