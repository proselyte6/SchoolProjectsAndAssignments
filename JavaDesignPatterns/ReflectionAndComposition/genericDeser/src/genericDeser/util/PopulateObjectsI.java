package genericDeser.util;

import genericDeser.util.FirstI;
import genericDeser.util.SecondI;
import genericDeser.fileOperations.FileProcessorI;

public interface PopulateObjectsI{
    public int uniqueFirstObjects();
    public int totalFirstObjects();
    public int uniqueSecondObjects();
    public int totalSecondObjects();
    public void addToFirstSet(FirstI f);
    public void addToSecondSet(SecondI s);
    public void printResults();
    public void deserObjects(FileProcessorI fp);
    public void printFirstSet();
    public void printSecondSet();
}