namespace Student_List
{
    internal class Student
    {

        private string studentID;
        private string firstName;
        private string lastName;
        private string address;
        private string city;
        private string state;
        private int zipCode;

        public Student(string id, string fName, string lName, string ad, string c, string sta, int zip) {

            studentID = id;
            firstName = fName;
            lastName = lName;
            address = ad;
            city = c;
            state = sta;
            zipCode = zip;
        
        }

        public string getID() {

            return studentID;
        
        }

        public string getFName() {

            return firstName;
        }



        public string getLName()
        {

            return lastName;
        }


        public string getAddress() {

            return address;
        }


        public string getCity() {

            return city;
        }

        public string getState() {


            return state;
        
        }

        public int getZip() {

            return zipCode;
        }


    }
}