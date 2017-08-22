package wordCount.util;

import wordCount.util.LoggerI;

/**
 * Just a logger class used for debugging.
 */
public class Logger implements LoggerI{
    
    public static enum DebugLevel {CONSTRUCTOR, RUN, RESULTS, STORE, NONE}
    
    private static DebugLevel debugLevel;
    
    /**
     * @return None
     */
    public static void setDebugValue (int levelIn) {
        switch (levelIn) {
            case 4: debugLevel = DebugLevel.CONSTRUCTOR; break;
            case 3: debugLevel = DebugLevel.RUN; break;
            case 2: debugLevel = DebugLevel.RESULTS; break;
            case 1: debugLevel = DebugLevel.STORE; break;
            case 0: debugLevel = DebugLevel.NONE; break;
        }
    }
    
    /**
     * @return None
     */
    public static void setDebugValue (DebugLevel levelIn) {
        debugLevel = levelIn;
    }
    
    /**
     * @return None
     */
    public static void writeOutput (String message, DebugLevel levelIn) {
        if(levelIn == debugLevel){
            System.out.println(message);
        }
    }
    
    /**
     * @return String of the current debug level
     */
    public String toString() {
        return "Debug Level is " + debugLevel;
    }
}
