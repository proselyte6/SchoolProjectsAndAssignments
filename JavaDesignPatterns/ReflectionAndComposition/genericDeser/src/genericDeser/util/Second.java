package genericDeser.util;

import genericDeser.util.SecondI;

public class Second implements SecondI{
    //all set methods
    private int IntValue;
    private double DoubleValue;
    private boolean BooleanValue;
    private int count;
    
    public Second() {
        count = 1;
    }
    
    public void setIntValue(int iIn){
        IntValue = iIn;
    }
    
    public int getIntValue() {
        return IntValue;
    }
    
    public void setDoubleValue(double dIn){
        DoubleValue = dIn;
    }
    
    public double getDoubleValue() {
        return DoubleValue;
    }
    
    public void setBooleanValue(boolean bIn){
        BooleanValue = bIn;
    }
    
    public boolean getBooleanValue() {
        return BooleanValue;
    }
    
    
    public void incrementCount() {
        count++;
    }
    
    public int getCount(){
        return count;
    }
    
    @Override
    public boolean equals(Object obj){
        boolean returnValue = false;
        if (obj instanceof SecondI){
            
            SecondI s = (Second) obj;
            //s.print();
            returnValue = (s.getIntValue() == this.IntValue) && (s.getDoubleValue() == this.DoubleValue)
            && (s.getBooleanValue() == this.BooleanValue);
          
        }
        return returnValue;
    }
    
    @Override
    public int hashCode() {
        return 12*IntValue;
    }
   
    public void print() {
        System.out.println("IntValue : "+ Integer.toString(IntValue));
    }
    
    
    
  
}