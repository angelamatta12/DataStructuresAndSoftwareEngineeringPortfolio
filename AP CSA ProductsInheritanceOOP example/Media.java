public class Media extends Product{

  //type of media 
private String type;

//populated constructor
public Media(double p,String c,String n,int q, String t){

super(p,c,n,q);
type = t;

}

  //find the type
public String getType(){

return type;

}

//change the type
public void setType(String t){

type = t;

}




public String toString(){

return super.toString()+ " \n Type: "+ type;


}


}
