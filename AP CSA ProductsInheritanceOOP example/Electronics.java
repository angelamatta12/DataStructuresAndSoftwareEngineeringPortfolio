public class Electronics extends Product{

 //screensize and battery included/not included
private boolean batteryIncluded;
private double screenSize;

//populated constructor 
public Electronics(double p,String c,String n,int q,boolean b,double s){

super(p,c,n,q);
batteryIncluded = b;
screenSize = s;

}


//find out if battery is included and the screen size 
public boolean getBattInc(){

return batteryIncluded;

}

public double getScreen(){

return screenSize;

}



//change whether or not battery is included and the screen size 

public void setBattInc(boolean b){

 batteryIncluded = b;

}

public void setScreen(double s){

 screenSize = s;

}



public String toString(){

return super.toString() + "\n Battery Included: "+ batteryIncluded + " \n Screen Size: "+ screenSize;

}



}
