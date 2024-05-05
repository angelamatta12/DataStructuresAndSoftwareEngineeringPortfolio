public class Clothing extends Product{

  //clothing brand and size
private String brand;
private String size;

    
//populated constructor
public Clothing(double p,String c,String n,int q,String b,String s){

super(p,c,n,q);
brand = b;
size = s; 

}



    //find the brand or the size
public String getBrand(){

return brand;

}

    
public String getSize(){

    return size;
}



//set the brand or size to a new value 
public void setBrand(String b){

brand = b;

}

public void setSize(String s){

size = s;

}



public String toString(){

return super.toString() + " \n Brand: "+ brand+ " \n Size: "+ size;

}


}
