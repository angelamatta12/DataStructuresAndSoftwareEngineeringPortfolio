using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab01
{
    public partial class frmName : Form
    {
        public frmName()
        {
            InitializeComponent();
        }

        private void frmLoad(object sender, EventArgs e)
        {
            this.Text = "Lab 01 - <Angela Matta>";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            String strFirstName = txtFirstName.Text;
            String strMiddleInit = txtMiddleIntial.Text;
            String strLastName = txtLastName.Text;

            lblMessage.Text = strFirstName + " " + strMiddleInit + " " + strLastName;


        }
    }
}
