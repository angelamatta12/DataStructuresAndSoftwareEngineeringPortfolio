using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Event_Sales
{
    public partial class frmSalesEvent : Form
    {
        public frmSalesEvent()
        {
            InitializeComponent();
        }

        String _HighschoolName;
        String strStudentGrade;
        String strGameType;
        int intAmountSkittles;
        int intAmountPopcorn;
        int intAmountLays;
        int intAmountSnickers;


        private void tolButtons_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        { // Toolbar control was clicked so based upon the button
          // that was clicked execute the correct method.

            switch (e.ClickedItem.Name)  //use name of Toolbar button to
            {                          //determine which button was clicked
                case "tolbtnCalculate":
                    Perform_Calculations();
                    break;
                case "tolbtnClear":
                    Clear_Event();
                    break;
                case "tolbtnExit":
                    Exit_Application();
                    break;

            }
        }


        private void getGradeLevel(String grade){

            //switch statement to check what grade student is
            switch (grade) {

                case "Freshman":
                    strStudentGrade = "9th";
                    break;
                case "Sophomore":
                    strStudentGrade = "10th";
                    break;
                case "Junior":
                    strStudentGrade = "11th";
                    break;
                case "Senior":
                    strStudentGrade = "12th";
                    break;



        }


    }


        private void getGameType(bool gameType){

           strGameType =  gameType != true ? "football" : "basketball";






        }



        private void Perform_Calculations()
        { // when user clicks Calculate toolbar button then
          // this method should be called


            //price for each item
            const double LAYS_PRICE = 0.70;
            const double SKITTLES_PRICE = 0.75;
            const double SNICKERS_PRICE = 0.80;
            const double POPCORN_PRICE = 0.65;

            //getting the amount of items ordered
            int.TryParse(txtQtyLays.Text, out intAmountLays);
            int.TryParse(txtQtyPopcorn.Text, out intAmountPopcorn);
            int.TryParse(txtQtySkittles.Text, out intAmountSkittles);
            int.TryParse(txtQtySnickers.Text, out intAmountSnickers);


            //getting the amount of money earned through sales 
            double totalMoneyLays = LAYS_PRICE * intAmountLays;
            double totalMoneyPopcorn = POPCORN_PRICE * intAmountPopcorn;
            double totalMoneySkittles = SKITTLES_PRICE * intAmountSkittles;
            double totalMoneySnickers = SNICKERS_PRICE * intAmountSnickers;

            double totalSales = totalMoneyLays + totalMoneyPopcorn + totalMoneySkittles + totalMoneySnickers;


            lblTotals.Text = "Totals: Skittles " + totalMoneySkittles.ToString("C") + " Snickers "
              + totalMoneySnickers.ToString("C") + " Lays " + totalMoneyLays.ToString("C") + " Popcorn " + totalMoneyPopcorn.ToString("C")
              + " Sales Total " + totalSales.ToString("C");

            getGradeLevel(lstGrade.Text);
            getGameType(rdoBasketball.Checked);

            txtSummary.Text +=  txtFirstName.Text.ToString()+" "+ txtLastName.Text.ToString()
                +", who is in "+  strStudentGrade +" grade, sold "+ totalSales.ToString("C")+ " at a "+ strGameType + " event."+ "\r\n ";


        }




        private void Clear_Event()
        { // when user clicks Clear toolbar button then
          // this method should be called

            //select senior by default
            lstGrade.SelectedItem = "Senior";

            //check Football radio button by default
            rdoFootball.Checked = true;

            //clear student name
            txtFirstName.Text = "";

            txtLastName.Text = "";


            //checkboxes set to false

            chkLaysChips.Checked = false;
            chkPopcorn.Checked = false;
            chkSkittles.Checked = false;
            chkSnickers.Checked = false;


            // quantity textbox control cleared and set to false 
            txtQtyLays.Text = "";
            txtQtySkittles.Text = "";
            txtQtySnickers.Text = "";
            txtQtyPopcorn.Text = "";

            txtQtyLays.Enabled = false;
            txtQtyPopcorn.Enabled = false;
            txtQtySkittles.Enabled = false;
            txtQtySnickers.Enabled = false;


            //clear lbl and set accumulators to 0 
            lblTotals.Text = "Totals: ";
            intAmountLays = 0;
            intAmountPopcorn = 0;
            intAmountSkittles = 0;
            intAmountSnickers = 0;


            txtSummary.Text = "";


        }

        private void Exit_Application()
        { // when user clicks Exit toolbar button then
          // this method should be called

            this.Close();


        }

        private void frmSalesEvent_Load(object sender, EventArgs e)
        {
            //ask for highschool name and set as form title
            InputBoxForm.InputBox("Highschool Name", "Please enter your highschool name", ref _HighschoolName);
            this.Text="Snack Sales " +  _HighschoolName;

            //check Football radio button by default
            rdoFootball.Checked = true;


            //create listbox for grade level
            lstGrade.Items.Add("Freshman");
            lstGrade.Items.Add("Sophomore");
            lstGrade.Items.Add("Junior");
            lstGrade.Items.Add("Senior");


            //select senior by default
            lstGrade.SelectedItem = "Senior";

        }




        private void chkSkittles_CheckedChanged(object sender, EventArgs e)
        {

            if (chkSkittles.Checked == true)
            {

                txtQtySkittles.Enabled = true;
                txtQtySkittles.Focus();

            }

            else {

                txtQtySkittles.Text = "";
                txtQtySkittles.Enabled = false;


            }



        }

        private void chkSnickers_CheckedChanged(object sender, EventArgs e)
        {


            if (chkSnickers.Checked == true)
            {

                txtQtySnickers.Enabled = true;
                txtQtySnickers.Focus();

            }

            else
            {

                txtQtySnickers.Text = "";
                txtQtySnickers.Enabled = false;


            }



        }

        private void chkLaysChips_CheckedChanged(object sender, EventArgs e)
        {


            if (chkLaysChips.Checked == true)
            {

                txtQtyLays.Enabled = true;
                txtQtyLays.Focus();

            }

            else
            {

                txtQtyLays.Text = "";
                txtQtyLays.Enabled = false;


            }


        }

        private void chkPopcorn_CheckedChanged(object sender, EventArgs e)
        {

            if (chkPopcorn.Checked == true)
            {

                txtQtyPopcorn.Enabled = true;
                txtQtyPopcorn.Focus();

            }

            else
            {
                txtQtyPopcorn.Text = "";
                txtQtyPopcorn.Enabled = false;
            }

        }

        











    }
}
