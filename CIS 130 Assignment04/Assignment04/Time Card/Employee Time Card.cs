using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Time_Card
{
    public partial class frmTimeCard : Form
    {
        public frmTimeCard()
        {
            InitializeComponent();
        }

        List<string> strList = new List<string>();
        List<decimal> decList = new List<decimal>();



        private void btnSubmitEmployee_Click(object sender, EventArgs e)
        {
            String MSGTEST = "";
            
            IsValidData(out MSGTEST);





        }

        //*********************************************
        // V A L I D A T I O N      M E T H O D S
        //*********************************************
        private bool IsValidData(out string Message)
        {//Call methods to validate employee id, name and work date
            Message = "";


          Message +=  UserValidation.IsValidEmployeeID(txtEmployeeID.Text);
          Message += UserValidation.IsValidName(txtEmployeeName.Text);
          Message += UserValidation.IsValidWorkDate(dtpWorkDate.Value);



            if (Message != "")
            {


                frmErrorMessages frmErrors = new frmErrorMessages();

                frmErrors.lblErrorMessages.Text = Message;

                frmErrors.Show();


            }


            else {


                Add_Employee();



            }


            return true;
        }



        private void Add_Employee(){

            decimal deciHours = decimal.Parse(lstHours.SelectedItem.ToString());
            decimal deciPayrate= decimal.Parse(cboPayrate.SelectedItem.ToString());
            decimal deciTotalPay = 0.0M;
            decimal deciNum = 1.5M;
        

            if (deciHours > 40)
            {
                deciTotalPay = (40 * deciPayrate)+(deciHours-40)*deciPayrate*deciNum;

            }
            else if(deciHours <= 40) {

               deciTotalPay = deciPayrate * deciHours;
            }


            strList.Add($"{txtEmployeeName.Text} worked {deciHours} hours and has a pay rate of {deciPayrate}.Gross = {deciTotalPay}" );
            decList.Add(deciHours);
        
        
        }






        private void frmLoad(object sender, EventArgs e)
        {
          decimal addingPayrate = 10.00M;

            for (int i = 0; i < 17; i++) {


                cboPayrate.Items.Add(addingPayrate.ToString("N2"));

                addingPayrate += 0.50M;

            }


            cboPayrate.SelectedIndex = 0;


            double hours = 1;

            for (int i = 0; i < 79; i++) {

                lstHours.Items.Add(hours);

                hours += 0.5;
            
            }


            lstHours.SelectedItem = 40.0;




        }

        private void btnViewAllEmployees_Click(object sender, EventArgs e)
        {
            decimal deciTotalHours = 0.0M;

            frmViewAllEmployees frmViewAll = new frmViewAllEmployees();

            foreach(decimal d in decList )
            {

                
                deciTotalHours += d;


            }

            foreach (string str in strList)
            {
                frmViewAll.lstAllEmployees.Items.Add(str);
                //frmViewAll.lstAllEmployees.Add(str);

            }

            frmViewAll.lblTotalHours.Text = deciTotalHours.ToString();

            frmViewAll.ShowDialog();

        }


    }
}
