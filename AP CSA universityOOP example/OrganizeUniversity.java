import java.lang.reflect.Array;

//beginning of class
public class OrganizeUniversity{

//array to hold University objects    
private University [] uni;

//populated constructor
public OrganizeUniversity(University a, University b, University c,University d, University e, University f){
uni = new University[6];
uni[0] = a;
uni[1] = b;
uni[2] = c;
uni[3] = d;
uni[4] = e;
uni[5] = f;



}




    //doubling the size of a the array (original uni obj)
    
public void doubleSize(){

    //create new Uni array obj to be used for temp storing
University [] doubleUni = new University[uni.length * 2];

//put all values from original Uni array obj into the temp storing
for(int i = 0; i< uni.length;i++){
    doubleUni[i]= uni[i];

}

    //double length for original Uni obj array  
uni = new University[uni.length*2];

    //put all values from temp storing back into original Uni obj array 
for(int i = 0; i< uni.length;i++){
    uni[i]= doubleUni[i];
}


}

    
    //add a Uni obj to the Uni obj array 

public void insertUni(University a, int insertUni){
    uni[insertUni] = a;

}


public String toString(){
String uniStr = " ";

    for(University university:uni){
        uniStr+= university;
        uniStr+= "\n ";
    
    } 
   
    return uniStr;
}

}
