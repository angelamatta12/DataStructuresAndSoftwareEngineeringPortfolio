using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Treasure_Game
{
    public partial class frmTreasureGame : Form
    {
        public frmTreasureGame()
        {
            InitializeComponent();

        }


        //field vars
        Random _Random = new Random();

        //number of guesses user makes
        int _CGuess;
        //number of guesses user is allowed
        int _NumofGuess;
        //chest that has the money 
        int _ChestNumMon;
        //value of the money 
        int _MonBagVal;





        private bool IsValidStart(){

            Boolean blFlag = true;

            //ensure player name is input 
            if (txtPlayerName.Text == "")
            {

                MessageBox.Show("Please enter your name.");
                blFlag = false;
                return blFlag;
            }

                int.TryParse(txtPlayerAge.Text, out int Age);

                //check if player age is correct
                if (Age < 5)
                {
                    MessageBox.Show("Age is too young");
                    blFlag = false;
                    return blFlag;

                }

                else if (Age > 7)
                {
                    MessageBox.Show("Age is too old");
                    blFlag = false;
                    return blFlag;

                }

                 if (cboNumber.SelectedIndex == -1)
                {
                    MessageBox.Show("You must select a number of guesses");
                    blFlag = false;
                    return blFlag;

                }

            return blFlag;
        }




        private void LoadDisplays() {

            //clear all output lbls 

            lblMessage.Text = "";

            //set all treasure to null
            picChest01.Image = null;
            picChest02.Image = null;
            picChest03.Image = null;
            picChest04.Image = null;
            picChest05.Image = null;
            picChest06.Image = null;
            picChest07.Image = null;
            picChest08.Image = null;
            picChest09.Image = null;
            picChest10.Image = null;
            picChest11.Image = null;
            picChest12.Image = null;
            picChest13.Image = null;
            picChest14.Image = null;
            picChest15.Image = null;


            //guess num lbl and field to 0 

            lblGuessNumber.Text = "0";
            _CGuess = 0;

            //number of guesses allowed

           _NumofGuess =  int.Parse(cboNumber.Text);


            //generate random chest 
            _ChestNumMon = _Random.Next(1,15);


            //generate money
            _MonBagVal = _Random.Next(1, 1000);


            //message for user 
            lblMessage.Visible = true;

            lblMessage.Text = "$$$ The money bag value is " + _MonBagVal +  " $$$";

            mnuStart.Enabled = false;

            btnOpenChest.Enabled = true;

            txtGuess.Enabled = true; 


        }






        private void mnuTreasure_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {   // When user clicks button on menu strip then this
            // event will fire. 
            if (e.ClickedItem.Name == "mnuExit")
                this.Close(); // Close Form

            if (e.ClickedItem.Name == "mnuStart")
                Start_Game();



        }


        private void Start_Game()
        { // This void method was added to handle click event of Start button


            if (IsValidStart()) {


                LoadDisplays();

            }
        }



        private void frmLoad(object sender, EventArgs e)
        {

            for (int i = 1; i < 11; i++) {


                cboNumber.Items.Add(i);
            
            
            }

        }



        public void Guessed_Correctly(int g1) {

            //money bag shows, 

            switch (g1) {

                case 1:
           
                    picChest01.Image = picMoneyBag.Image;
                    break;
                case 2:
                    picChest02.Image = picMoneyBag.Image;
                    break;
                case 3:
                    picChest03.Image = picMoneyBag.Image;
                    break;
                case 4:
                    picChest04.Image = picMoneyBag.Image;
                    break;
                case 5:
                    picChest05.Image = picMoneyBag.Image;
                    break;
                case 6:
                    picChest06.Image = picMoneyBag.Image;
                    break;
                case 7:
                    picChest07.Image = picMoneyBag.Image;
                    break;
                case 8:
                    picChest08.Image = picMoneyBag.Image;
                    break;
                case 9:
                    picChest09.Image = picMoneyBag.Image;
                    break;
                case 10:
                    picChest10.Image = picMoneyBag.Image;
                    break;
                case 11:
                    picChest11.Image = picMoneyBag.Image;
                    break;
                case 12:
                    picChest12.Image = picMoneyBag.Image;
                    break;
                case 13:
                    picChest13.Image = picMoneyBag.Image;
                    break;
                case 14:
                    picChest14.Image = picMoneyBag.Image;
                    break;
                case 15:
                    picChest15.Image = picMoneyBag.Image;
                    break;

            }

            // display win message
            lblMessage.Text = "You found the treasure chest and won!";

            //enable start menu item, double check this one 
            mnuStart.Enabled = true;

            //disable open chest button, and guess txt control, double check if he wants us to clear txtGuess then disable
            btnOpenChest.Enabled = false;

            txtGuess.Enabled = false;



        }


        public void Guessed_Incorrectly(int g1) {

            //display nothing image in the box
            switch (g1)
            {

                case 1:
                    picChest01.Image = picNothing.Image;
                    break;
                case 2:
                    picChest02.Image = picNothing.Image;
                    break;
                case 3:
                    picChest03.Image = picNothing.Image;
                    break;
                case 4:
                    picChest04.Image = picNothing.Image;
                    break;
                case 5:
                    picChest05.Image = picNothing.Image;
                    break;
                case 6:
                    picChest06.Image = picNothing.Image;
                    break;
                case 7:
                    picChest07.Image = picNothing.Image;
                    break;
                case 8:
                    picChest08.Image = picNothing.Image;
                    break;
                case 9:
                    picChest09.Image = picNothing.Image;
                    break;
                case 10:
                    picChest10.Image = picNothing.Image;
                    break;
                case 11:
                    picChest11.Image = picNothing.Image;
                    break;
                case 12:
                    picChest12.Image = picNothing.Image;
                    break;
                case 13:
                    picChest13.Image = picNothing.Image;
                    break;
                case 14:
                    picChest14.Image = picNothing.Image;
                    break;
                case 15:
                    picChest15.Image = picNothing.Image;
                    break;

            }






            //add one to field with current guess number, check if out of guesses

            _CGuess += 1;

            if (_CGuess >= _NumofGuess)
            {

                lblMessage.Text = "Sorry, you lose! The money was in treasure chest number " + _ChestNumMon;

                mnuStart.Enabled = true;

                btnOpenChest.Enabled = false;

                txtGuess.Enabled = false;



            }
            else {

                lblGuessNumber.Text = _CGuess.ToString();
            
            }




        }







        private void OpenChest(object sender, EventArgs e)
        {
            int checkNum = 0;

            if (int.TryParse(txtGuess.Text, out checkNum) && checkNum > 0 && checkNum <= 15) {


                //check to see how you would do this, check to see what is going on with the number. 


                if (checkNum == _ChestNumMon) {
                    Guessed_Correctly(checkNum);
                }

                else {
                    Guessed_Incorrectly(checkNum);


                }

            }


            else {

                MessageBox.Show("Invalid number entered, please enter a number between 1 and 15 ");
            
            }

        }


    }
}
