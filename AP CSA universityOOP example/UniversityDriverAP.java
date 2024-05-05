import java.util.*;

public class UniversityDriverAP{


public static void main(String[] args ){


//array of objects holds 6 items
    University [] uniList = new University[6];

University a = new University(); 

University b = new University("ex1", "loc1",111,111,11);

University c = new University();

University d = new University("ex2", "loc2",222,222,22);

University e = new University();

University f = new University("ex3", "loc3",333,333,33);



uniList[0]= a;
uniList[1]= b;
uniList[2]= c;
uniList[3]= d;
uniList[4]= e;
uniList[5]= f;


int count = 0;
 //prints out every other university 
for(University uni: uniList){

if(count%2 ==0 && count < uniList.length){
  System.out.println(uni);

}

count++;

}


    //create a new arraylist with all previously made university objects
ArrayList <University> uniArr = new ArrayList <University>(6);

uniArr.add(0,f);

uniArr.add(1,e);

uniArr.add(2,d);

uniArr.add(3,c);

uniArr.add(4,b);

uniArr.add(5,a);


University other = new University("ex4", "loc2",321,123,33);

int iter = 0;
int num = 0;




  //checks how many university objects in arraylist are equal to one unviersity object outside of arraylist   
while( iter < uniArr.size()){
  
if(uniArr.get(iter) .equals (other) ){

  num++;
  
}

iter++;

}



System.out.print("Other is equal is to "+ num+ "objects");

}
}
