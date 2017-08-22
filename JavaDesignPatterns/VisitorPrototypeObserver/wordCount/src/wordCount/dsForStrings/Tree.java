package wordCount.dsForStrings;

import wordCount.dsForStrings.Node;
import wordCount.visitors.DSProcessingVisitorI;
import wordCount.visitors.PopulateVisitor;
import wordCount.visitors.WordCountVisitor;
import java.util.LinkedList;
import java.util.Queue;

/**
 * The tree class that contains a root.
 */
public class Tree implements Cloneable{
    private Node root; //the root of the tree

  
    /**
     * The tree constructor.
     */
    public Tree() {
        root = null;
    }
    
    /**
     * The insert method giving a word. Used for the populate visitor.
     * I inserted following a binary trees rule with the length of the word and also 
     * kept track of the children and parents.
     * @param word - the word to be inserted within the tree
     */
    public void insert(String word){
        
        Node newNode = new Node(word);
        if(root==null){
            root = new Node(word);
            return;
        }
        Node current = root;
        Node parent = null;
        while(true){
            parent = current;
            if (current.returnWord().equals(word)){
                current.incrementCount();
                return;
            }
            
            
            if(word.length() < current.returnWord().length()){
                current = current.getLeftChild();
                if(current==null){
                    
                    parent.setLeftChild(word);
                    parent.getLeftChild().setParent(parent);
                    return;
                }
            }else{
                current = current.getRightChild();
                if(current==null){
                    
                    parent.setRightChild(word);
                    parent.getRightChild().setParent(parent);
                    return;
                }
            }
        }
    }
    
    /**
     * The insert method giving a node. Used for the clone and observe visitor.
     * I inserted following a binary trees rule with the length of the word and also
     * kept track of the children and parents.
     * @param n - the node to be inserted within the tree
     */
    public void insert(Node n){
        
        if(root==null){
            root = n;
            return;
        }
        Node current = root;
        Node parent = null;
        while(true){
            parent = current;
          
            
            
            if(n.returnWord().length() < current.returnWord().length()){
                current = current.getLeftChild();
                if(current==null){
                    parent.setLeftChild(n);
                    parent.getLeftChild().setParent(parent);
                    return;
                }
            }else{
                current = current.getRightChild();
                if(current==null){
                    parent.setRightChild(n);
                    parent.getRightChild().setParent(parent);
                    return;
                }
            }
        }
    }

    
    /**
     * A method to return the root of the tree.
     * @return root - the root of the tree
     */
    public Node returnRoot() {
        return root;
    }
    
    /**
     * the accept method for visitors.
     * @param visitor - the visitor that is being given permission to access/visit the tree
     */
    public void accept(DSProcessingVisitorI visitor){
        visitor.visit(this);
    }
}
