using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;

namespace Student_Addresses
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        List<Student> lstStudents = new List<Student>(); 

        public MainWindow()
        {
            InitializeComponent();

            //Set focus to the first input control
            txtStudentID.Focus();
        }

        private void btnAddStudent_Click(object sender, RoutedEventArgs e)
        {

         
            if (UserValidation.IsValidID(txtStudentID.Text) == "" && UserValidation.IsPresent(txtFirstName.Text,"first name") == ""
                && UserValidation.IsPresent(txtLastName.Text,"lastname") == "" && UserValidation.IsPresent(txtAddress.Text,"address") == ""
                && UserValidation.IsPresent(txtState.Text,"state") == "" && UserValidation.IsPresent(txtZipcode.Text,"zipcode") == ""
                && UserValidation.IsPresent(txtCity.Text,"city") == "")
            {


                Student addStudent = new Student(txtStudentID.Text, txtFirstName.Text, txtLastName.Text, txtAddress.Text, txtCity.Text, txtState.Text, int.Parse(txtZipcode.Text));
                lstStudents.Add(addStudent);

                MessageBox.Show("Student sucessfully added");




            }
            else {


                MessageBox.Show(UserValidation.IsValidID(txtStudentID.Text));
                MessageBox.Show(UserValidation.IsPresent(txtFirstName.Text, "first name"));
                MessageBox.Show(UserValidation.IsPresent(txtLastName.Text, "lastname"));
                MessageBox.Show(UserValidation.IsPresent(txtAddress.Text, "address"));
                MessageBox.Show(UserValidation.IsPresent(txtState.Text, "state"));
                MessageBox.Show(UserValidation.IsPresent(txtZipcode.Text, "zipcode"));
                MessageBox.Show(UserValidation.IsPresent(txtCity.Text, "city"));

            }
           



        }

        private void btnExit_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void btnSave_Click(object sender, RoutedEventArgs e)
        {
            if (lstStudents.Count() < 1)
            {

                MessageBox.Show("There must be at least one student added to the list.");
                return;

            }

            else {


                StreamWriter writer = null;

                try
                {
                    writer = File.CreateText("student data.txt");
                }
                catch (IOException ex)
                {
                    MessageBox.Show(ex.Message, "IOException");
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message, "Exception");
                }


                finally
                {
                    if (writer != null)
                    {
                        foreach (Student s in lstStudents)
                        {


                            writer.WriteLine(s.getID().ToString() + "," + s.getFName().ToString() + "," + s.getLName().ToString() +
                                "," + s.getAddress().ToString() + "," + s.getCity().ToString() + "," + s.getState().ToString() + "," + s.getZip().ToString());



                        }
                        writer.Close();

                        MessageBox.Show("Data saved successfully");

                    }
                }





            }




        }
    }
}
