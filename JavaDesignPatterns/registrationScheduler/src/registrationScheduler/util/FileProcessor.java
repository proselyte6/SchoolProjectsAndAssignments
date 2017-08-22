package registrationScheduler.util;

import registrationScheduler.util.Logger;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.Path;

public class FileProcessor{
	BufferedReader inFile;
	BufferedWriter outFile;

	public FileProcessor(String inFileName, String outFileName){
		Logger.writeOutput("Constructing FileProcessor with inFileName = " + inFileName
										+ "  and outFileName = " + outFileName, Logger.DebugLevel.CONSTRUCTOR);
		try{
			Path inPath = Paths.get("./" + inFileName);
			Path outPath = Paths.get("./" + outFileName);
			inFile = Files.newBufferedReader(inPath, StandardCharsets.UTF_8);
			outFile = Files.newBufferedWriter(outPath, StandardCharsets.UTF_8);
		}catch(IOException e){
			System.err.println("Error when reading in files: " + e.getMessage());
		}
	}

	/**
	* @return String of the next line in the input file
	*/
	public synchronized String readLine(){
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
	* @return None
	*/
	public synchronized void writeLine(String line){
		try{
			outFile.write(line + "\n");
			outFile.flush();
		}catch(IOException e){
			System.err.println("Error when writing to file: " + e.getMessage());
			System.exit(1);
		}	
	}
}
