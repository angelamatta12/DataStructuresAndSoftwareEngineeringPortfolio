public class UniversityTester{

public static void main(String[] args){


// instantiate 4 objects, must print objects after instantiated or else the static var printed is wrong. 

University def1 = new University();
System.out.println("Object 1 made with default constructor:\n\n" + def1);

University def2 = new University();
System.out.println("Object 2 made with default constructor:\n\n" + def2);

University catU = new University("Cattastic", "Meowtropolis",2000,30000,10);
System.out.println("Object 3 made with populated constructor:\n\n" + catU);

University dogU = new University("Dog", "Dogtopia",1000,15000,10);
System.out.println("Object 4 made with populated constructor:\n\n" + dogU);


System.out.println("Static variable: " + University.getUniNum());


// compare all objects
System.out.println("Comparing Object 1 with Object 2: " + def1.equals(def2));
System.out.println("Comparing Object 3 with Object 4: " + catU.equals(dogU));


//increasing the number of buildings

def1.expandUniBuild(10);
def2.expandUniBuild(15);

System.out.println("Def1 now has " + def1.getUniBuilding() + " buildings.");
System.out.println("Def2 now has " + def2.getUniBuilding() + " buuildings. ");

  
// enrolling and graduating students,(adding and subtracting students)

catU.gradUniPop(15000);
dogU.enrollUniPop(15000);


System.out.println("DogU now has " + dogU.getUniPop() + " students.");
System.out.println("CatU now has " + catU.getUniPop() + " students. ");


//hiring teachers and adding classes based on the student population, (showing how student population has been programmed to be the determinant of the # of classes and teachers)

System.out.println("DogU now has " + dogU.addUniTeach() + " teachers.");
System.out.println("CatU now has " + catU.addUniTeach() + " teachers. ");


System.out.println("DogU now has " + dogU.addUniClass() + " classes.");
System.out.println("CatU now has " + catU.addUniClass() + " classes. ");



//System.out.println("Object 3 made with populated constructor:\n\n" + catU);


//System.out.println("Object 4 made with populated constructor:\n\n" + dogU);

}

}
