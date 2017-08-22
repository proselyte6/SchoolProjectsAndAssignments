package wordCount.util;

import wordCount.dsForStrings.Tree;

/**
 * Interface for the file processor.
 */
public interface FileProcessorI{
    public String readLine();
    public void writeLine(String line);
    public void writeToNewFile(String outFile, Tree tree);
}