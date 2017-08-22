package wordCount.visitors;

import wordCount.dsForStrings.Tree;

/**
 * The data structure processing visitor interface.
 */
public interface DSProcessingVisitorI{
    public void visit(Tree tree);
    public Tree returnTree();
}