package wordCount.dsForStrings;

import wordCount.observer.Observer;
import wordCount.observer.Subject;

/**
 * The node class, that implements the prototype pattern and the observer pattern
 */
public class Node implements Cloneable, Observer, Subject{
    private String word; //the word it holds
    private int count; //the number of times the word appeared in the file
    private Node right; //the right child
    private Node left; //the left child
    private Node parent; //the parent of this node
    private Node observer; //the node's observer
    
    /**
     * The constructor for a node.
     * @param wordIn - the word the node holds
     */
    public Node(String wordIn){
        word = wordIn;
        count = 1;
        right = null;
        left = null;
        parent = null;
        observer = null;
    }
    
    /**
     * The clone method for the prototype pattern.
     * I copy the word and count but not the children nor parents because
     * that is up to the clone and observe visitor to set that up.
     * @return clone - the cloned node
     */
    public Object clone() throws CloneNotSupportedException{
        Node clone = new Node(this.word);
        clone.setCount(this.count);
        clone.setFamilyNull();
        return clone;
    }
    
    /**
     * This method is for nodes that are observers.
     * they are updated with a new count
     * @param newCount - the new count
     */
    public void update(int newCount){
        count = newCount;
    }
    
    /**
     * This method is for nodes that are subjects.
     * they register a node as an observer (a node from the orignal tree registers its
     * correspondsing node from the back up tree as an observer).
     * @param n - the node to become an observer
     */
    public void registerObserver(Node n){
        observer = n;
    }
    
    /**
     * This method is for nodes that are subjects.
     * it notifes the observers there was a change and updates them.
     */
    public void notifyObservers(){
        observer.update(count);
    }
    
    /**
     * Returns the word the node holds
     * @return word - the word the node holds
     */
    public String returnWord() {
        return word;
    }
    
    /**
     * This method is for the test visitor to show the observer pattern works.
     * allows one to change the count of a node
     * @param countIn - the count to be changed to
     */
    private void setCount(int countIn) {
        count = countIn;
        if (observer != null){
            notifyObservers();
        }
    }
    
    /**
     * this is for the prototype pattern.
     * it is only called in the clone() method and just sets the children and parent to null.
     */
    private void setFamilyNull() {
        parent = null;
        left = null;
        right = null;
    }
    
    /**
     * Setter for right child given a word. used for populate visitor
     * @param word - the word for the node.
     */
    public void setRightChild(String word){
        right = new Node(word);
    }
    
    /**
     * Setter for left child given a word. used for populate visitore
     * @param word - the word for the node.
     */
    public void setLeftChild(String word){
        left = new Node(word);
    }
    
    /**
     * Setter for right child given a node. used for clone visitor
     * @param node - the node to become a right child
     */
    public void setRightChild(Node n){
        right = n;
    }
    
    /**
     * Setter for left child given a node. used for clone visitor
     * @param node - the node to become a left child
     */
    public void setLeftChild(Node n){
        left = n;
    }
    
    /**
     * getter for right child
     * @return right - the right child
     */
    public Node getRightChild(){
        return right;
    }
    
    /**
     * getter for left child
     * @return left - the left child
     */
    public Node getLeftChild(){
        return left;
    }
    
    /**
     * getter for the parent
     * @return parent - the parent
     */
    public Node getParent() {
        return parent;
    }
    
    /**
     * setter for the parent
     * @param n - the parent
     */
    public void setParent(Node n){
        parent = n;
    }
    
    
    /**
     * getter for the count
     * @return count - the count of the node
     */
    public int returnCount() {
        return count;
    }
    
    /**
     * increments the count
     */
    public void incrementCount() {
        count++;
        if (observer != null){
            notifyObservers();
        }
    }
    
    /**
     * allows one to add to the count. used in test visitor to show the observer pattern works.
     */
    public void addCount(int num) {
        count += num;
        if (observer != null){
            notifyObservers();
        }
    }
 }