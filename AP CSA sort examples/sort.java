import java.util.*;

public class sort{


    
/*selection sort*/


//sort highest to lowest with ArrayList

public static void selectSort(ArrayList<Integer>list, boolean a){

//loop through ArrayList all the way to the end
    for(int j = 0; j<list.size()-1;j++){

        //grab a minimum via the index
      int minIndex = j;
     //compare minimum to all other values in the Arraylist   
      for(int k = j+1;k<list.size();k++){
        
          // if the other value is smaller than the selected minimum then that smaller value becomes the minimum by storing its index in the var
        if(list.get(k)>list.get(minIndex)){

           minIndex = k;
                 }

           }

//switch the values around, by temporarily storing the inital minimum, switching it with the new minimum then placing the original in the new minimum's old spot
     Integer temp = list.get(j);
     list.set(j,list.get(minIndex));
     list.set(minIndex,temp);

}
    
System.out.println(list);

}






//sort highest to lowest with Array

public static void selectSort(int[] list, int b){
    
    //follow similar steps as above 

    //loop through whole array
    for(int j = 0; j < list.length-1 ;j++){
    
        //grab a minimum via index
      int minIndex = j;
        
        //compare minimum to next value, if next value is smaller then it becomes the new minimum via its index being stored in the var now
      for(int k = j+1;k<list.length;k++){
        
        if(list[k]>list[minIndex]){

           minIndex = k;

        }

      }

//switch the places of the values, starting by storing the original minimum in a temp var, then put the new minimum in the original's place, and finally putting the original
        //minimum in the new minimum's old place
     Integer temp = list[j];
     list[j] = list[minIndex] ;
     list[minIndex] = temp;

    }
    
    //must use for each loop to print since Arrays dont have a ToString built into them.
    for(int a: list){
    
        System.out.print(a+ " ");
    
    }
    
    System.out.println(" ");
    
    
        
    }
    






//sort alphabetical order from A->Z 


public static void selectSort(ArrayList<String>list, int k ){

//loop through whole arraylist
    for(int j = 0; j < list.size()-1;j++){
      
        //grab a value in this case a "minimum" via its index
        int minIndex = j;

        //compare this value to the next one 
        for(int a = j+1;a<list.size();a++){

            //if the value stored at the index gotten by the inner loop comes lexigonically before the value stored at the index gotten by the outer loop 
            //then "minimum" becomes the value stored at the index gotten by the inner loop 
          if(list.get(a).compareTo(list.get(minIndex))  <= 0  ){
                   minIndex = a;

          }

        }        
        
        //switch the values around by temporarily storing the original minimum in another var, putting the new minimum in the original's place and then
        //putting the original minimum in the new minimum's old place
         String temp = list.get(j);
         list.set(j,list.get(minIndex));
         list.set(minIndex,temp);
        
       
    }
        
        System.out.println(list);
    
}




//sort alphabetically Z->A

//these follow the same steps as the above example except at the if statement
public static void selectSort(ArrayList<String>list, boolean b,int a){

 
    for(int j = 0; j < list.size()-1;j++){
      
        int minIndex = j;

        for(int c = j+1;c<list.size();c++){
  //if the value stored at the index gotten by the inner loop comes lexigonically after the value stored at the index gotten by the outer loop 
            //then "minimum" becomes the value stored at the index gotten by the inner loop 
        
          if(list.get(c).compareTo(list.get(minIndex))  >= 0  ){
                   minIndex = c;

          }

        }
        
        
         String temp = list.get(j);
         list.set(j,list.get(minIndex));
         list.set(minIndex,temp);
        
                
        }
        
        
        
        System.out.println(list);
        
    
}



//sort alphabetically Z->A
//same steps as the above example except using  an array    


public static void selectSort(String[]list,int a ,boolean b){


    for(int j = 0; j < list.length-1;j++){
      
        int minIndex = j;

        for(int c = j+1;c<list.length;c++){

          if(list[c].compareTo(list[minIndex])  >= 0  ){
                   minIndex = c;

          }

        }


         String temp = list[j];
         list[j] = list [minIndex];
         list[minIndex] = temp;
        
       
        }
       

        for(String str: list){
        
        System.out.print(str + " ");
        

        }


    }

    

/*insertion sort*/


//sort highest to lowest with ArrayList

public static void insertSort(ArrayList<Integer>list, boolean a){

    //loop through whole arraylist, start at 1 for index b/c of while condition
    for(int j = 1; j < list.size();j++){

        Integer temp = list.get(j);
        int possible = j;
        
        //check if the the possible index is greater than 0 or else inside cmd does not work, && check if currently selected value is greater than the value before it
        while(possible > 0 && temp > list.get(possible-1)){
        
        list.set(possible,list.get(possible-1));
        possible--;
        
        }
       
        
        list.set(possible,temp);
        
       
        }
       
        
        System.out.println(list);
        

}








//sort highest to lowest with Array
//same as above example but with array cmds
public static void insertSort(int[] list, int b){

for(int j = 1; j < list.length ;j++){


int temp = list[j];
int possible = j;

while(possible > 0 && temp > list[possible-1]){

list[possible] = list[possible -1];
possible--;


}


list[possible]= temp;

}


for(int a: list){

    System.out.print(a+ " ");

}

System.out.println(" ");

    
}





//sort A->Z, except with a while loop in place of a for loop  


public static void insertSort(ArrayList<String>list, int k ){


    for(int j = 1; j < list.size();j++){


        String temp = list.get(j);
        int possible = j;
        
        while(possible > 0 && temp.compareTo(list.get(possible-1)) <= 0){
        
        list.set(possible,list.get(possible-1));
        possible--;
        
       
        }
        
        list.set(possible,temp);
        
        }
        
        
        System.out.println(list);
   
    
}




//sort Z->A, same steps except with a while loop instead of a for loop


public static void insertSort(ArrayList<String>list, boolean b,int a){



    for(int j = 1; j < list.size();j++){


        String temp = list.get(j);
        int possible = j;
        
        while(possible > 0 && temp.compareTo(list.get(possible-1)) >= 0){
        
        list.set(possible,list.get(possible-1));
        possible--;
       
        
        }
        
        
        
        list.set(possible,temp);
        
 
        }
        

        System.out.println(list);
       
    
}



//sort Z->A, same steps except with a while loop instead of a for loop and an array 


public static void insertSort(String[]list,int a ,boolean b){


    for(int j = 1; j < list.length;j++){

        String temp = list[j];
        int possible = j;
        
        while(possible > 0 && temp.compareTo(list[possible-1]) >= 0){
        
        list[possible] = list[possible-1];
        possible--;
        
        
        }
       
        
        list[possible] = temp;
      
        
        }
       
        for(String str: list){
        
        System.out.print(str + " ");
       
        }

    
}


}
