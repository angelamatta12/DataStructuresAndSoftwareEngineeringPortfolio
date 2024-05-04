using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab02
{
    public partial class frmSalesCommission : Form
    {
        public frmSalesCommission()
        {
            InitializeComponent();
        }

        Double dblSalesAmount;
        Double dblCommission;
        Double dblCommissionRate;

        private void frmSalesCommission_Load(object sender, EventArgs e)
        {
            //load the department numbers in the list box
            for(int i=10;i<=50;i=i+10)
            {
                lstDepartNum.Items.Add(i);
            }

            lstDepartNum.SelectedIndex = 0;

        }

        private void btnCommission_Click(object sender, EventArgs e)
        {
            

            if (double.TryParse(txtSalesAmount.Text ,out dblSalesAmount)) {


                String strDeptNumList = lstDepartNum.GetItemText(lstDepartNum.SelectedItem);

                int intDeptNum;

                int.TryParse(strDeptNumList, out intDeptNum);

                
                switch (intDeptNum)
                {

                    case 10:
                        dblCommissionRate = .01;
                       
                        break;
                    case 20:
                      dblCommissionRate =  .03;
                      
                        break;
                    case 30:
                    case 40:
                       dblCommissionRate= .02;
                       
                        break;
                    case 50:
                        dblCommissionRate = .05;
                      
                        break;


                }


                dblCommission = dblCommissionRate * dblSalesAmount;
                lblCommEarned.Text = "Your commission rate is " + dblCommissionRate.ToString() + "! \r\n" +  "Commission earned is "+ dblCommission.ToString() + "!";



            }

            else {


                MessageBox.Show("Please Use a Valid Decimal Value");
                txtSalesAmount.Focus();
            }


          

        }

        private void txtChangeSales(object sender, EventArgs e)
        {
            lblCommEarned.Text = "";
        }

        private void SelectIndexDepartment(object sender, EventArgs e)
        {
            lblCommEarned.Text = "";
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
