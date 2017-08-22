package genericDeser.util;


    /**
     * Just a logger class used for debugging.
     */
    public class Logger{
        
        public static enum DebugLevel {CONSTRUCTOR, RESULTS}
        
        private static DebugLevel debugLevel;
        
        /**
         * @return None
         */
        public static void setDebugValue (int levelIn) {
            switch (levelIn) {

                case 1: debugLevel = DebugLevel.CONSTRUCTOR; break;
                case 0: debugLevel = DebugLevel.RESULTS; break;
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
