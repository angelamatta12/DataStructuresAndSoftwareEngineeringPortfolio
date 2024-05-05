using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;


namespace Lab_01_Sales_List
{
    public partial class frmSales : Form
    {
        public frmSales()
        {
            InitializeComponent();
        }

        private void btnGetSales_Click(object sender, EventArgs e)
        {
            int total = 0;

            int count = 0;

            double average = 0;

            StreamReader read = new StreamReader("SalesData.txt");

            while (read.Peek() != -1) {

                int num = int.Parse(read.ReadLine());

                lstSales.Items.Add(num);

                total += num;

                count++;
            
            
            }

            lblTotalSales.Text = total.ToString();

            average = total / (count * 1.0);

            lblAverage.Text = average.ToString();
            


        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
