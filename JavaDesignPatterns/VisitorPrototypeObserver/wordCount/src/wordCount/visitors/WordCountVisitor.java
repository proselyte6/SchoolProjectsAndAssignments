package wordCount.visitors;

import wordCount.visitors.DSProcessingVisitorI;
import wordCount.util.FileProcessorI;
import wordCount.util.FileProcessor;
import wordCount.dsForStrings.Node;
import wordCount.dsForStrings.Tree;

/**
 * this Visitor determines the total number of words, total number of unique words, and characters stored in the data structure
 */
public class WordCountVisitor implements DSProcessingVisitorI{
    FileProcessorI fp; //needed for writing to the output file.
    private int totalWords;
    private int totalDistinctWords;
    private int totalChars;
    
    /**
     * The constructor for the word count visitor
     * @param fpIn - the file processor
     */
    public WordCountVisitor(FileProcessorI fpIn){
        fp = fpIn;
        totalWords = 0;
        totalDistinctWords = 0;
        totalChars = 0;
    }
    
    /**
     * This visit method, sends the root of the tree through a recursive method
     * this recursive method thus updates the values of the total words, characters and distinct words
     * then writes all this info to the output file using the file processor.
     * @param tree - the tree to visit
     */
    public void visit(Tree tree){
        Node root = tree.returnRoot();
        visit_(root);
        fp.writeLine("Total number of words: "+ Integer.toString(totalWords));
        fp.writeLine("Total distinct number of words: "+Integer.toString(totalDistinctWords));
        fp.writeLine("Total number of characters: "+Integer.toString(totalChars));
    }
    
    /**
     * This is the helper recursive function. Visits the tree through
     * "inorder" traversal and updates all the value for the total words, characters and distinct words
     * @param n - the node currently being visited
     */
    private void visit_(Node n){
        if (n == null){
            return;
        }
        visit_(n.getLeftChild());
        totalWords += n.returnCount();
        totalDistinctWords++;
        totalChars = totalChars +( n.returnWord().length() * n.returnCount());
        visit_(n.getRightChild());
    }
    
    /**
     * An empty method
     */
    public Tree returnTree(){
        Tree t = new Tree();
        return t;
    }
    
 
}