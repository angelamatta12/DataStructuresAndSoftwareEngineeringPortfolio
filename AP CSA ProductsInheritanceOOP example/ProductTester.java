import java.lang.*;


public class ProductTester{

//get the total cost of buying multiple of the same item
    public static double totalCost(Product p){

     return p.getPrice()* p.getQuantity();

    }
    
    
//get the total cost of everything you bought on your shopping list 
    public static double grandCost(Product [] p ){
      
    double sum = 0.0;

        //loop through the array to add the costs to sum
    for(int k = 0; k< p.length;k++){
  
        //use totalCost function to get value to add on to sum, array used is an array of products
        sum+= totalCost(p[k]);
        
    }

        return sum;
}




public static void main(String[] args){

//general product obj using Product parent class
Product pro1 = new Product(1.10,"Company","product",(int) Math.random()*4 +3);
    
// using electronics child class
Electronics elec = new Electronics(1.10,"Company","product",(int) (Math.random()*4)+3,true,10.8);

//using Media child class
Media med = new Media(1.10,"Company","product",(int) (Math.random()*4) +3,"book");

    //using clothing child class
Clothing cloth = new Clothing(1.10,"Company","product",(int) (Math.random()*4) +3,"GAP","Medium");

    //using women grandchild class
Women wom = new Women(1.10,"Company","product",(int) (Math.random()*4) +3,"GAP","Medium","long");
    
    
 //using men grandchild class
Men me = new Men(1.10,"Company","product",(int) (Math.random()*4) +3,"GAP","Medium","black");


//create array of all products instantiated above 
Product []  list = new Product[6];

list[0] = pro1;
list[1]= elec;
list[2]=med;
list[3]=cloth;
list[4]=wom;
list[5]=me;


    //loop through array to see if ToString() works for each 
for(Product pro: list){

System.out.println(pro);
System.out.println();

}

//creating the column headers accross the top 
System.out.printf("%4s","Name");
System.out.printf("%14s","Company");
System.out.printf("%15s","Quantity");
System.out.printf("%12s","Price ");
System.out.printf("%15ss","Total Cost");
System.out.println();
System.out.println("***************************************************************");

    //looping through whole array to display all product information 
for(int i =0; i< list.length;i++){

System.out.printf( "%s",list[i].getName());
System.out.printf("%12s",list[i].getCompany());
System.out.printf("%12d",list[i].getQuantity());
System.out.printf("%12.2f",list[i].getPrice());
System.out.printf("%12.2f",totalCost(list[i]) );
System.out.println();


}



System.out.println("***************************************************************");

    
    //getting the grand total at the end 
System.out.printf("%50s","Grand Total:  $");

System.out.printf("%.2f",grandCost(list));


}



}
