public class Product{

// price of product, name of product, how much of product is in stock, and what company makes product
private double price;
private String company;
private String name;
private int quantity;


//populated constructor
public Product(double p,String c,String n,int q){

price = p;
company = c;
name = n;
quantity = q;


}



//get the price of product, name of product, quantity of product ,and company making product 
public double getPrice(){

return price;

}


public String getName(){

return name;


}


public int getQuantity(){

return quantity;


}


public String getCompany(){

return company;


}






//set the price of product, name of product, quantity of product ,and company making product 
public void setPrice(double p){

price = p;


}


public void setName(String n){

name = n;


}


public void setQuantity(int q){

quantity = q;


}


public void setCompany(String c){

company = c;


}



public String toString(){

    return "Name: " +name +"\n Quantity: " + quantity+ " \n Price: "+ price+ " \n Company: "+ company; 
 }


}
