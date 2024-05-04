using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;


    public  class InputBoxForm
    {   //static class means all members will be static
        public static  DialogResult InputBox(string title, string promptText, ref string value)
        {
            //dynamically create form in memory with a label for the prompt messade, a textbox for
            //the data input and two buttons
            Form frmInput = new Form();
            Label lblPrompt = new Label();
            TextBox txtDataEntry = new TextBox();
            Button btnOk = new Button();
            Button btnCancel = new Button();

            //Set up Title bar text, prompt message in label, and start an intital
            //value in textbox control
            frmInput.Text = title;
            lblPrompt.Text = promptText;
            txtDataEntry.Text = value;
            
            //Set up two buttons, one for OK and the other for the Cancel button
            btnOk.Text = "OK";
            btnCancel.Text = "Cancel";
            btnOk.DialogResult = DialogResult.OK;
            btnCancel.DialogResult = DialogResult.Cancel;
             
            //Position controls on form
            lblPrompt.SetBounds(9, 20, 372, 13);
            txtDataEntry.SetBounds(12, 36, 372, 20);
            btnOk.SetBounds(228, 72, 75, 23);
            btnCancel.SetBounds(309, 72, 75, 23);
            
            //anchor edges of label, textbox and buttons to the parent (form)
            lblPrompt.AutoSize = true;   //Prompt messages will be different sizes
            txtDataEntry.Anchor = txtDataEntry.Anchor | AnchorStyles.Right;
            btnOk.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
            btnCancel.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
             
            //Set up properties of form
            frmInput.ClientSize = new Size(396, 107);
            frmInput.Controls.AddRange(new Control[] { lblPrompt, txtDataEntry, btnOk, btnCancel });
            frmInput.ClientSize = new Size(Math.Max(300, lblPrompt.Right + 10), frmInput.ClientSize.Height);
            frmInput.FormBorderStyle = FormBorderStyle.FixedDialog;
            frmInput.StartPosition = FormStartPosition.CenterScreen;
            frmInput.MinimizeBox = false;
            frmInput.MaximizeBox = false;
            frmInput.AcceptButton = btnOk;
            frmInput.CancelButton = btnCancel;
            
            //Show form as a Dialog and retrieve data from textbox
            //and assign it to the value variable
            DialogResult dialogResult = frmInput.ShowDialog();
            value = txtDataEntry.Text;
            return dialogResult;
        }
    }
