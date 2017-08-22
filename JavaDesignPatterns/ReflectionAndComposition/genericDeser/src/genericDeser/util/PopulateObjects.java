package genericDeser.util;

import genericDeser.util.FirstI;
import genericDeser.util.SecondI;
import genericDeser.util.First;
import genericDeser.util.Second;
import genericDeser.util.PopulateObjectsI;
import genericDeser.fileOperations.FileProcessorI;
import genericDeser.fileOperations.FileProcessor;
import java.util.*;
import java.lang.reflect.Method;

public class PopulateObjects implements PopulateObjectsI{
    //all set methods
    //two data structures, one for First and one for Second
    private Set<FirstI> firstSet;
    private Set<SecondI> secondSet;
    private Map<String, Class> typeMap;
    
    public PopulateObjects() {
        firstSet = new HashSet<FirstI>();
        secondSet = new HashSet<SecondI>();
        typeMap = new HashMap<String, Class>();
        typeMap.put("int", Integer.TYPE);
        typeMap.put("float", Float.TYPE);
        typeMap.put("short", Short.TYPE);
        typeMap.put("String", String.class );
        typeMap.put("double", Double.TYPE);
        typeMap.put("boolean", Boolean.TYPE);
    }
    
    public int uniqueFirstObjects() {
        return firstSet.size();
    }
    
    public int totalFirstObjects() {
        int total = 0;
        for (FirstI f: firstSet){
            total += f.getCount();
        }
        return total;
    }
    
    public int uniqueSecondObjects() {
        return secondSet.size();
    }
    
    public int totalSecondObjects() {
        int total = 0;
        for (SecondI s: secondSet){
            total += s.getCount();
        }
        return total;
        
    }
    
    //possible problem here
    public void addToFirstSet(FirstI f){
   
        if (firstSet.contains(f)){
            for (FirstI x: firstSet){
                if (x.equals(f)){
                    x.incrementCount();
                    return;
                }
            }
        } else {
      
            firstSet.add(f);
        }
        
        
        
    }
    
    public void addToSecondSet(SecondI s){
        
    
     
        if (secondSet.contains(s)){
            for (SecondI x: secondSet){
                if (x.equals(s)){
                    x.incrementCount();
                    return;
                }
            }
        } else {
            secondSet.add(s);
        }
        
    }
    
    public void printResults() {
        
        Logger.writeOutput( "Number of unique First objects: " + Integer.toString(uniqueFirstObjects()) ,Logger.DebugLevel.RESULTS);
        Logger.writeOutput( "Total Number of First objects: " + Integer.toString(totalFirstObjects()) ,Logger.DebugLevel.RESULTS);

        Logger.writeOutput( "Number of unique Second objects: " + Integer.toString(uniqueSecondObjects()) ,Logger.DebugLevel.RESULTS);

        Logger.writeOutput( "Total Number of Second objects: " + Integer.toString(totalSecondObjects()),Logger.DebugLevel.RESULTS);
    }
    

    
    public void deserObjects(FileProcessorI fp){
        String line = " ";
        String clsName = null;
        Class cls = null;
        Object obj = null;
        String methdName = null;
        Method meth = null;
        Class[] signature = new Class[1];
        Object[] params = new Object[1];
        Object result = null;
        
        while (true){
            line = fp.readLine();
            if (line == null){
                if (obj instanceof FirstI){
                    FirstI f = (First) obj;
                    addToFirstSet(f);
                } else if (obj instanceof SecondI){
                    SecondI s = (Second) obj;
                    addToSecondSet(s);
                }
                break;
            } else {
                String[] words = line.split("[ \t]+");
                // if the length is one, then it is fqn
                if (1 == words.length){
                    if (obj instanceof FirstI){
                        FirstI f = (First) obj;
                        addToFirstSet(f);
                    } else if (obj instanceof SecondI){
                        SecondI s = (Second) obj;
                        addToSecondSet(s);
                    }

                    clsName = words[0].substring(4);
                    
                    try{
                        cls = Class.forName(clsName);
                        obj = cls.newInstance();
                    } catch (Exception e){
                        e.printStackTrace(System.out);
                        System.exit(1);
                    }
                    
                    
                    
                                    } else {
                   // System.out.println(words[0].substring(5,words[0].length()-1));
                   // System.out.println(words[1].substring(4,words[1].length()-1));
                    
                    signature[0] = typeMap.get(words[0].substring(5,words[0].length()-1));
                    methdName = "set"+ words[1].substring(4,words[1].length()-1);
                    
                    try{
                    meth = cls.getMethod(methdName, signature);
                    params[0] = check(words[0].substring(5,words[0].length()-1), words[2].substring(6));
                    result = meth.invoke(obj, params);
                    } catch (Exception e){
                        e.printStackTrace(System.out);
                        System.exit(1);
                    }
                }
                
                
            }
        }
    }
    
    private Object check(String type, String value){
        Object retVal = null;
        if (type.equals("String")){
            return value;
        } else if (type.equals("int")){
            return Integer.parseInt(value);
        } else if (type.equals("float")){
            return Float.parseFloat(value);
        } else if (type.equals("short")){
            return Short.parseShort(value);
        } else if (type.equals("boolean")){
            return Boolean.parseBoolean(value);
        } else if (type.equals("double")){
            return Double.parseDouble(value);
        }
        return retVal;
    }
    
    public void printFirstSet() {
        for(FirstI f : firstSet){
            f.print();
        }
    }
    
    public void printSecondSet() {
        for(SecondI s: secondSet){
            s.print();
        }
    }
}