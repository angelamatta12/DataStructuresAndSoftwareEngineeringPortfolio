using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;

namespace Student_Addresses
{
    public static class UserValidation
    {

        public static string IsPresent(string value, string field)
        {
            string strMsg = "";
            if (value == "")
            {
                strMsg = field + " is a required field.\n";
            }
            return strMsg;
        }

        public static string IsValidID(string value)
        {
            string strMsg = "";

            //Phone number must be in the following format 999-999-9999
            Match IDFormat = Regex.Match(value, @"[A-Z][A-Z]-[0-9][0-9][0-9][0-9][0-9]");
            if (IDFormat.Success == false)
            {
                strMsg = "The student id must be in the following format: XX-99999.\n";
            }

            return strMsg;
        }


    }
}
