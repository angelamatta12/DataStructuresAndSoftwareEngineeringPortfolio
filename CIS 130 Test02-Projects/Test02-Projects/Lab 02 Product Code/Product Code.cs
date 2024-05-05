using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab_02_Product_Code
{
    public partial class frmProductCodes : Form
    {
        public frmProductCodes()
        {
            InitializeComponent();
        }

        List<string> products = new List<string>();

        private void btnSubmit_Click(object sender, EventArgs e)
        {

            products.Add(txtProductCode.Text);



            if (IsValidData(txtProductCode.Text))
            {
                lblMessage.Text += "The product code of " + txtProductCode.Text + " is valid.\n\r";

            }


        }

        private bool IsValidData(string Code)
        {
            bool IsValid = false;
            //Write code to check if code is 7 characters. If not 
            //display an error using MessageBox class and return false

            if (Code.Length > 7 || Code.Length < 7) {

                MessageBox.Show("The product code must be 7 characters long.");

                return IsValid;
            }
            else {
                //Write code to check if product code is in the following
                //format 99999-X where the last character X is either the
                //character S or D. If not display an error using the MessageBox
                //class and return false.

                char end = Code[Code.Length - 1];

                if (!(end.Equals('D')|| end.Equals('S') || Code[Code.Length - 1].Equals('/')))
                {
                    MessageBox.Show("The code must end with an /S or /D");
                    return IsValid;


                }

                else
                {

                    for (int i = 0; i < Code.Length-2; i++)
                    {

                        if (Char.IsNumber(Code, i))
                        {

                            IsValid = true;

                        }

                        else {

                            IsValid = false;
                        
                        }


                    }



                }

            }

            return IsValid;

        } 
    }

           
 }

