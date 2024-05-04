using System;
using System.Collections.Generic;
using System.Text;

namespace Time_Card
{
  public static  class UserValidation
    {
        //PLEASE NOTE: At the end of each error message
        //please add \n which is the newline character

        public static string IsValidEmployeeID(string ID)
        {
            string strMsg = "";

            // Validate Employee ID
            // Must be a length of 8 characters.
            // If not set error message and exit this method


            if (ID.Length != 8) {

                strMsg += "The ID is not the appropriate length, it must be a length of 8 characters \n";
                return strMsg;
               
            }


            // Must be 5 digits followed by a dash "-" and then two
            // letters of the alphabet.
            // If not set error message 



            for (int i = 0; i < 5; i++) {

                //check all the way up to the dash if the char is a number
                
                    if (!(char.IsDigit(ID[i]))) {

                        strMsg += "The ID must be 5 digits followed by a dash and then two letters of the alphabet \n";
                        return strMsg;

                    }

                


            }

                //check if that letter is a dash 
             

                    if (!((ID.Substring(5,1)) == "-")) {

                        strMsg += "The ID must be 5 digits followed by a dash and then two letters of the alphabet  \n";
                        return strMsg;

                    }



            //check if that part is made of letters
            for (int i = 6; i < 8; i++)
            {

                if (!(char.IsLetter(ID[i])))
                {

                    strMsg += "The ID must be 5 digits followed by a dash and then two letters of the alphabet \n";
                    return strMsg;

                }
            }
       
            

            return strMsg;

        }


        public static string IsValidName(string Name)
        {
            string strMsg = "";

            // Spaces before the first name and after the last name
            // will be trimmed
            Name = Name.Trim();

            // Validate Employee Name - cannot be blank
            // and needs at least one space between first and last name
            // If not set error message 


            if (Name == "") {

                strMsg += "Name cannot be blank, must be a valid name \n";
                return strMsg;

            }

            else if (!(Name.Contains(" "))) {

                strMsg += "Name must contain at least one space between first and last name";
                return strMsg;
            
            }


            return strMsg;
        }



        public static string IsValidWorkDate(DateTime WorkDate)
        {
            string strMsg = "";

            // Make sure Work Date is less than or equal Today's Date
            // If not set error message 

            if (WorkDate.Date > DateTime.Today) {

                strMsg += "Invalid date, date must be either today's date or a previous date";
            
            }

            return strMsg;
        }


        
    }
}
