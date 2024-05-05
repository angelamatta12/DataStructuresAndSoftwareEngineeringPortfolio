import java.util.*;

public class UniversityDriver{


public static void main(String[] args){
  
  //two scanners to combat the problem 
Scanner scan = new Scanner(System.in);
//Scanner scanNum = new Scanner(System.in);
  
//Name of uni
String uniN;

//Location of uni
String uniLoc;

//tuition of uni 
double uniTut;

//num of students for uni
int uniStu;

//num of buildings on uni campus 
int uniBuild;


// array with all instantiated universties, because the objects are all in an array, they all share the same static variable. 
University [] uniList = new University[6];

System.out.println("Help us create 3 new  universities");


//address skipping issue, will skip inputting name the 2nd and 3rd time it loops, edit 1/8/21: skipping issue caused by scanner mistakenly reading the enter key
// when inputting the tuition as the name, solution: split both into 2 different for loops.

for(int i = 0; i<3;i++){
 
   System.out.println("Please enter the number of students attending the university: ");
    uniStu = scan.nextInt();

    System.out.println("Please enter  the number of buildings on the university's campus: ");
    uniBuild = scan.nextInt();

    System.out.println("Please enter the university's tuition: ");
    uniTut = scan.nextDouble();

    System.out.println("Please enter a name for the university: ");
    uniN = scan.nextLine();

    System.out.println("Please enter  the university's location: ");
    uniLoc = scan.nextLine();


    uniList[i] =  new University(uniN,uniLoc);
    
}
  
  

System.out.println("Great! Now enter the other data for the university!");


for(int i = 0; i<3;i++){
 
    

    System.out.println("Please enter the number of students attending the university: ");
     uniStu = scan.nextInt();
     uniList[i].setUniPop(uniStu);
 
     System.out.println("Please enter  the number of buildings on the university's campus: ");
     uniBuild = scan.nextInt();
     uniList[i].setUniBuilding(uniBuild);
 
     System.out.println("Please enter the university's tuition: ");
     uniTut = scan.nextDouble();
     uniList[i].setUniCost(uniTut);
 
 
 }


 System.out.println("\n \n \n ");

 University addedUni1 = new University();
 University addedUni2 = new University();
 University addedUni3 = new University();
 
// add  newly instantiated objects to array

uniList[3]= addedUni1;
uniList[4]= addedUni2;
uniList[5]= addedUni3;


System.out.println("Printing original array using for-each loop");


for(University uni : uniList ){

System.out.println(uni);

System.out.println(" ");


}


  
// change tuition cost, initially had previous skipping issue, the last enter used to input the tuition would be read as the new name of the university so 
//changing tution instead, edit: this fixed the problem.


System.out.println("Changing original array using for-each loop");


for(University uni : uniList ){

    System.out.println("Change the university tuition ");
     uniTut = scan.nextDouble();

     uni.setUniCost(uniTut);

System.out.println(" \n \n");


}



System.out.println("Printing the new array using while loop");

int count = 0;

while(count < 6){


    System.out.println(uniList[count]);
    count++;
    
System.out.println(" ");
System.out.println(" ");

}




//OrganizeUniversity section

OrganizeUniversity orgUni = new OrganizeUniversity(uniList[0],uniList[1],uniList[2],uniList[3],uniList[4],uniList[5]);

orgUni.doubleSize();

 //uniList = doubleSize();

  System.out.println("Printing array after calling doubleSize using for-each loop");
  System.out.println(orgUni);

//With the way the directions were worded, it sounded like you wanted us to add 3 new default objects to the uni array in the OrganizeUniversity class
// so I did that one 

  University addedUni4 = new University();
  University addedUni5 = new University();
  University addedUni6 = new University();
  

  int insert = 0;
// add  newly instantiated objects to array
System.out.println("Enter the index number to insert this default item into the array.");
insert = scan.nextInt();
orgUni.insertUni(addedUni4,insert);

System.out.println("Enter the index number to insert this default item into the array.");
insert = scan.nextInt();
orgUni.insertUni(addedUni5,insert);

System.out.println("Enter the index number to insert this default item into the array.");
insert = scan.nextInt();
orgUni.insertUni(addedUni6,insert);


  System.out.println("Printing array after adding more University objects using for-each loop");
  System.out.println(orgUni);


 
University.selectSort();



}

}
