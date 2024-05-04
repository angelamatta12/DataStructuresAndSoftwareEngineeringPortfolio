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

namespace Student_List
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
          
        }



        List<Student> lstStudents = new List<Student>();

        private void GetAllStudents() {

            
               StreamReader input = null;
               // string dirPath = @"C:\Assignment07\Assignment07\Student List\bin\Debug\netcoreapp3.1";
                string filePath = "StudentData.txt";

            try
            {
                input = new StreamReader(filePath);
                // code that uses the disk file
                // to read data from the file


            }
            catch (FileNotFoundException)
            {
                MessageBox.Show(filePath + " not found.",
                "File Not Found");
            }
            /*catch (DirectoryNotFoundException)
            {
                MessageBox.Show(dirPath + " not found.",
                "Directory Not Found");
            }
            */
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
                if (input != null)
                {
                    
                    while (input.EndOfStream == false)
                    {

                        string str = input.ReadLine();
                        string[] strData = str.Split(",");

                        //declare student object with populated constructor
                        //0- studentID
                        //1- fName
                        //2 lName
                        //3 address
                        //4 city 
                        //5 state
                        //6 zipcode
                        Student student = new Student(strData[0],strData[1],strData[2],strData[3],strData[4],strData[5],int.Parse(strData[6]));

                        //add to collection in the begginning of file
                        lstStudents.Add(student);
                        //grab ID first to add to collection then display it in the lstbox
                        lstStudentsID.Items.Add(strData[0]);
                       
                       
                    }
                    input.Close();

                }
            }


}


        

        private void btnGetStudents_Click(object sender, RoutedEventArgs e)
        {

            GetAllStudents();

        }

        private void lstStudentsID_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            int intIndex = lstStudentsID.SelectedIndex;

            lblFullName.Content = lstStudents[intIndex].getFName() + " " + lstStudents[intIndex].getLName();

            lblAddress.Content = lstStudents[intIndex].getAddress() + "\n" + lstStudents[intIndex].getCity()+", "
                + lstStudents[intIndex].getState()+ "  "+ lstStudents[intIndex].getZip();



        }
    }
}
