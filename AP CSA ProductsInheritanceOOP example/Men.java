public class Men extends Clothing{

  //color for men's clothing, probably should just be in the clothing class though
private String color;


  //populated constructor
public Men(double p,String c,String n,int q,String b,String s,String col){

super(p,c,n,q,b,s);
color = col;


}

//find color
public String getColor(){

return color;

}


//set color
public void setColor(String col){

color = col;

}


public String toString(){

return super.toString()+ "\n Color: "+ color;

}


}
