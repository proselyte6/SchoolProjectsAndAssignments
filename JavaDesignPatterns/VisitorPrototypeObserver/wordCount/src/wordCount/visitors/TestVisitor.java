package wordCount.visitors;

import wordCount.visitors.DSProcessingVisitorI;
import wordCount.util.FileProcessorI;
import wordCount.util.FileProcessor;
import wordCount.dsForStrings.Node;
import wordCount.dsForStrings.Tree;

/**
 * This visitor class is just for showing that the observer pattern works
 */
public class TestVisitor implements DSProcessingVisitorI{
    
    //an empty constructor
    public  TestVisitor(){
    }
    
    /**
     * This visit method grabs the root of the tree and passes it to a helper function
     */
    public void visit(Tree tree){
        Node root = tree.returnRoot();
        visit_(root);
    }
    
    /**
     * The helper method traverses the tree and updates the count to show the observer pattern works.
     */
    private void visit_(Node n){
        if (n == null){
            return;
        }
        visit_(n.getLeftChild());
        n.addCount(5);
        visit_(n.getRightChild());
    }
    
    //an empty method
    public Tree returnTree() {
        Tree t = new Tree();
        return t;
    }
}