//methods to read a line and write to a file
//check project two for this
package wordCount.util;

import wordCount.util.FileProcessorI;
import wordCount.dsForStrings.Tree;
import wordCount.dsForStrings.Node;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.PrintWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.Path;

/**
 * The file processing class. Has a buffered reader (to read from a file)
 * and a buffered writer (to write to a file).
 */
public class FileProcessor implements FileProcessorI{
    BufferedReader inFile;
    BufferedWriter outFile;
    
    /**
     * FileProcessor constructor
     * @param inFileName - the input file name
     * @param outFileName - the output file name
     */
    public FileProcessor(String inFileName, String outFileName){
       
        try{
            Path inPath = Paths.get("./" + inFileName);
            Path outPath = Paths.get("./" + outFileName);
            inFile = Files.newBufferedReader(inPath, StandardCharsets.UTF_8);
            outFile = Files.newBufferedWriter(outPath, StandardCharsets.UTF_8);

        } catch(IOException e){
            System.err.println("Error when reading in files: " + e.getMessage());
        }
    }
    
    /**
     * Reads a line of the input file using the buffered reader
     * @return retVal - String of the next line in the input file
     */
    public String readLine(){
        String retVal = "";
        
        
            try{
                retVal = inFile.readLine();
            }catch(IOException e){
                System.err.println("Error when reading from file: " + e.getMessage());
                System.exit(1);
            }
        return retVal;
    }
    
    /**
     * Writes a line to the output file using the buffered writer.
     * @param line - the line to be written to the output file.
     */
    public void writeLine(String line){
        try{
            outFile.write(line + "\n");
            outFile.flush();
        }catch(IOException e){
            System.err.println("Error when writing to file: " + e.getMessage());
            System.exit(1);
        }	
    }
    
    /**
     * This method is for the test visitor to prove the obersver pattern works
     * It traverses the tree, and writes its contents to a file.
     * @param outFile - the output file to be written to
     * @param tree - the tree to be traversed
     */
    public void writeToNewFile(String outFile, Tree tree){
        try{
            PrintWriter writer = new PrintWriter(outFile, "UTF-8");
            Node root = tree.returnRoot();
            traverse_(writer, root);
            writer.close();
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
    
    /**
     * This helper function is for traversing the tree in inorder and writing its contents to a file
     * @param writer - the writer taht writes to the output file
     * @node n - the current node its visiting
     */
    private void traverse_(PrintWriter writer, Node n){
        if (n == null){
            return;
        }
        traverse_(writer, n.getLeftChild());
        writer.println(n.returnWord() + " "+ Integer.toString(n.returnCount()));
        traverse_(writer, n.getRightChild());
    }
}
