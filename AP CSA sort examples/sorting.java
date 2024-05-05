import java.util.*;

public class sorting{
public static void main(String [] args){


    int [] arr1 = {2,4,5,1,3,6};

    
 ArrayList <Integer> arr2 = new ArrayList();

 arr2.add(1);
 arr2.add(5);
 arr2.add(2);
 arr2.add(4);
 arr2.add(3);
 arr2.add(6);

 
ArrayList <String> arr3 = new ArrayList();

arr3.add("dog");
arr3.add("elephant");
arr3.add("fish");
arr3.add("apple");
arr3.add("bear");
arr3.add("cats");


String [] arr4 = {"diminish","efficient","full","able","back","cower"};



/*selection sort*/


//using arrayList and sorting it(integers), highest to lowest
System.out.println("Sorting an arrayList of Integers from highest to lowest with selection");

 System.out.println(" ");

sort.selectSort(arr2, true);


//using array and sorting it(ints), highest to lowest

System.out.println("Sorting an array of ints from highest to lowest with selection");

sort.selectSort(arr1,1);

System.out.println(" ");
    
    
//using arrayList and sorting it(Strings), A->Z

System.out.println("Sorting an arrayList of Strings from A to Z with selection");
sort.selectSort(arr3, 3);
System.out.println(" ");
    
    
    //using arrayList and sorting it(strings)Z->A
System.out.println("Sorting an arrayList of Strings from Z to A with selection");

sort.selectSort(arr3, true,1);



System.out.println(" ");

    
//using arrays and sorting it(strings)Z->A

System.out.println("Sorting an array of Strings from Z to A with selection");

sort.selectSort(arr4,1,true);


System.out.println(" ");




/*insertion sort*/



//using array and sorting it(ints), highest to lowest

System.out.println("Sorting an array of ints from highest to lowest with insertion");

sort.insertSort(arr1,1);
    
System.out.println(" ");
    
    
//using arrayList and sorting it(integers), highest to lowest
System.out.println("Sorting an arrayList of Integers from highest to lowest with insertion");

sort.insertSort(arr2, true);

System.out.println(" ");

    
    
//using arrayList and sorting it(Strings), A->Z

System.out.println("Sorting an arrayList of Strings from A to Z with insertion");

sort.insertSort(arr3, 3);

System.out.println(" ");

    
    //using arrayList and sorting it(strings)Z->A
System.out.println("Sorting an arrayList of Strings from Z to A with insertion");

sort.insertSort(arr3, true,1);
    
System.out.println(" ");


//using arrays and sorting it(strings)Z->A

System.out.println("Sorting an array of Strings from Z to A with insertion");


sort.insertSort(arr4,1,true);


System.out.println(" ");
    
}
}
