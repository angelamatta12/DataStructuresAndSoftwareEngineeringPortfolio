using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Fantasy_Wedding_Catering__Assignment1_Angela_Matta_
{
    public partial class frmFantasyWeddingCaterers : Form
    {
        public frmFantasyWeddingCaterers()
        {
            InitializeComponent();
        }


        const double CHICKEN_PRICE = 45.25;
        const double BEEF_PRICE = 55.50;
        const double VEGETARIAN_PRICE = 44.25;
        const double GLUTENFREE_PRICE = 60.00;

        // all of the amount of meals bought
        int intBeefMealNum = 0 ;
        int intChickMealNum = 0 ;
        int intVegMealNum = 0 ;
        int intGlutenFreeMealNum = 0 ;



        private void btnExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnClear_Click(object sender, EventArgs e)
        {

            txtBrideName.Text = "";
            txtGroomName.Text = "";
            txtWeddingDate.Text = "";
            txtBeefDin.Text = "";
            txtChickDin.Text = "";
            txtGlutenFreeDin.Text = "";
            txtVegDin.Text = "";

            lblNumMeal.Text = "";
            lblSubtotal.Text = "";
            lblSalesTax.Text = "";
            lblTotalPrice.Text = "";

            txtBrideName.Focus();






        }

        private void btnCalc_Click(object sender, EventArgs e)
        {

            int.TryParse(txtBeefDin.Text, out intBeefMealNum);


            int.TryParse(txtChickDin.Text, out intChickMealNum);

      
            int.TryParse(txtVegDin.Text, out intVegMealNum);

   
            int.TryParse(txtGlutenFreeDin.Text, out intGlutenFreeMealNum);


            int totalNumMeals = intBeefMealNum + intChickMealNum + intVegMealNum + intGlutenFreeMealNum;

            lblNumMeal.Text = totalNumMeals.ToString();

            // cost before sales tax
            
            double dblBeefCost = Math.Round((intBeefMealNum * BEEF_PRICE), 2);
            double dblChickCost = Math.Round((intChickMealNum * CHICKEN_PRICE), 2);
            double dblVegCost = Math.Round((intVegMealNum * VEGETARIAN_PRICE),2);
            double dblGlutenFreeCost = Math.Round((intGlutenFreeMealNum * GLUTENFREE_PRICE),2);

            double dblBeforeSalesTax = dblBeefCost + dblChickCost + dblGlutenFreeCost + dblVegCost;

            lblSubtotal.Text = dblBeforeSalesTax.ToString();


            double dblSalesTax = Math.Round((dblBeforeSalesTax * 0.06),2);

            lblSalesTax.Text = dblSalesTax.ToString();

            double dblTotalPrice = Math.Round((dblBeforeSalesTax + dblSalesTax),2);

            lblTotalPrice.Text = dblTotalPrice.ToString();


        }


        //ask about this part next class period
        private void frmLoad(object sender, EventArgs e)
        {

            this.Text = "Wedding Calculator- Fantasy Wedding Caterers";

        }

        private void textChanged(object sender, EventArgs e)
        {



            lblNumMeal.Text = "";
            lblSubtotal.Text = "";
            lblSalesTax.Text = "";
            lblTotalPrice.Text = "";




        }
    }
}
