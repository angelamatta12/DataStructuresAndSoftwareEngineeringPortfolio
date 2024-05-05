public class University{

   
//instance data
private String uniName; // University name
private String uniLocation;// university location  city,state
private double uniTuition; // university cost of tuition
private int uniStudentPop; // # of students attending university
private int uniNumofBuildings; // # of buildings that make up university
private int uniTeacher; // # of teachers needed for university, lets say 30 for each class. 
private int uniClass;// # of classes on campus, based on # of students
private static int numUni = 0; // total # of universities in US, ++ everytime new object is created





//default constructor, sets values when object is not created w/any parameters
public University(){

    this("unknown","unknown",0.00,0,0);

}

//test constructor, sets values when object is not created w/only name and location
public University(String name, String loc){

    this(name,loc,0.00,0,0);

}


//test constructor 2  sets values when object is not created w/only student pop, tuition, num of buildings
public University(int studentPop, int build, double tut){

    this("unknown","unknown",tut,studentPop,build);


}

//populated constructor, sets values when object is created w/ parameters
public University(String name, String loc, double tuit, int studentPop, int numBuild){

 

 uniName = name;
 uniLocation = loc;
 uniTuition = tuit;
 uniStudentPop = studentPop;
 uniNumofBuildings = numBuild;
 uniTeacher = this.addUniTeach();
 uniClass = this.addUniClass();
 numUni++;


}



//accessor methods for each instance

//accessor 1: returns university name 
public String getUniName(){

    return uniName;
}


//accessor 2: returns university location
public String getUniLocation(){

    return uniLocation;
}



//accessor 3: returns university tuition cost
public double getUniCost(){

    return uniTuition;
}


//accessor 4: returns # of students attending university 
public int getUniPop(){

    return uniStudentPop;
}



//accessor 5: returns # of buildings university has
public int getUniBuilding(){

    return uniNumofBuildings;
}



//accessor 6: returns # of universities in US   
public static int getUniNum(){

    return numUni;
}



//accessor 7: returns # of teachers university has
public int getUniTeacher(){

    return uniTeacher;
}




//accessor 8: returns # of classes university has
public int getUniClass(){

    return uniClass;
}





//mutator methods for all instance data


//mutator 1: change university name 
public void setUniName(String name){

    uniName = name;
}


//mutator 2: change university location
public void setUniLocation(String loc){

     uniLocation = loc;
}



//mutator 3: change university tuition cost
public void setUniCost(double tuit){

    uniTuition = tuit;
}


//mutator 4: change # of students attending university 
public void setUniPop(int pop){

    uniStudentPop = pop;
}



//mutator 5: change # of buildings university has
public void setUniBuilding(int build){

    uniNumofBuildings = build;
}


// toString method, allows printing of university object

public String toString(){
  
  
/*
 uniName = name;
 uniLocation = loc;
 uniTuition = tuit;
 uniStudentPop = studentPop;
 uniNumofBuildings = numBuild;
 numUni++;

*/

return uniName+ " is located in " + uniLocation + ". The tuition costs $" + uniTuition + ".\nThere are " +
uniStudentPop + " students attending."+ " There are " + uniNumofBuildings + " buildings on campus. There are "+
uniClass+ " classes on campus and "+ uniTeacher+ " teachers. "+ "\nThis is university number " +
numUni; 

}


// equals method, checks if 2 university objects are equal; based on tuition cost, # of students and location 

public boolean equals(University other){

if(uniLocation.equals(other.getUniLocation()) && uniStudentPop == other.getUniPop() && uniTuition == other.getUniCost()){

     return true; 

    }

return false;

}






//other methods for altering the object




//you can gain/lose students at the university ie. adding newly enrolled students, subtracting graduating students 

//other method 1: enroll new students, increase population

public void enrollUniPop(int increase){
 
 uniStudentPop = uniStudentPop + increase;


}

// other method 2: graduate students, decrease student population 
public void gradUniPop(int decrease){
 

    uniStudentPop = uniStudentPop - decrease;
     
    if(uniStudentPop<0){

        uniStudentPop = 0;
    }
  
  
  }
  




//can expand the university or tear down buildings 


// other method 3: expanding university

public void expandUniBuild(int increase){

    uniNumofBuildings = uniNumofBuildings + increase;

  

}



// other method 4: decreasing university size (number of buildings)

public void decreaseUniBuild(int decrease){

    uniNumofBuildings = uniNumofBuildings - decrease;

    if(uniNumofBuildings < 0){

    uniNumofBuildings = 0; 

    }


   

}







// can hire new teachers for uni 

// other method 5: hire new teachers for uni

public int addUniTeach(){

if(uniStudentPop <= 30){

uniTeacher = 1;

}

else if (uniStudentPop > 30){

 uniTeacher = uniStudentPop / 30;


}

return uniTeacher;

}




//can add new classrooms based on # of students

// other method 6: creating new classrooms based on student pop


public int addUniClass(){

    if(uniStudentPop <= 30){
    
    uniClass = 1;
    
    }
    
    else if (uniStudentPop > 30){
    
     uniClass = uniStudentPop / 30;
    
    
    }

    return uniClass;
    }
    

   
}
