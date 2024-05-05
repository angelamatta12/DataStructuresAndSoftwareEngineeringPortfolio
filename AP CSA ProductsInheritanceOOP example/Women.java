public class Women extends Clothing{

  //length of women clothing item
private String length;

//populated constructor
public Women(double p,String c,String n,int q,String b,String s,String l){

super(p,c,n,q,b,s);

length = l;

}

  //get length of item
public String getLength(){

return length;

}


  //set length of item
public void setLength(String l){

length = l;

}


public String toString(){

return super.toString()+ "\n Length: "+ length;

}



}
