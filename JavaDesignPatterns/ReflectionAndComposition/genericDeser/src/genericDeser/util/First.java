package genericDeser.util;

import genericDeser.util.FirstI;

public class First implements FirstI{
 
    private int IntValue;
    private String StringValue;
    private float FloatValue;
    private short ShortValue;
    private int count;
    
    public First() {
        count = 1;
    }
    
    public void setIntValue(int iIn){
        IntValue = iIn;
    }
    
    public int getIntValue() {
        return IntValue;
    }
    
    public void setStringValue(String sIn){
        StringValue = sIn;
    }
    
    public String getStringValue() {
        return StringValue;
    }
    
    public void setFloatValue(float fIn){
        FloatValue = fIn;
    }
    
    public float getFloatValue() {
        return FloatValue;
    }
    
    public void setShortValue(short shIn){
        ShortValue = shIn;
    }
    
    public short getShortValue(){
        return ShortValue;
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
        if (obj instanceof FirstI){
            FirstI f = (First) obj;
            //f.print();
        
            
returnValue = (f.getIntValue() == this.IntValue) && (f.getStringValue().equals(this.StringValue)) && (f.getFloatValue() == this.FloatValue) && (f.getShortValue() == this.ShortValue);
        }
        return returnValue;
    }
    
    @Override
    public int hashCode() {
        return 31*IntValue;
    }
    
    public void print() {
        System.out.println("IntValue : "+ Integer.toString(IntValue));
    }
    
}