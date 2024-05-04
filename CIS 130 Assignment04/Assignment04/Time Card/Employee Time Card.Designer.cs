
namespace Time_Card
{
    partial class frmTimeCard
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnSubmitEmployee = new System.Windows.Forms.Button();
            this.btnViewAllEmployees = new System.Windows.Forms.Button();
            this.btnExit = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.lstHours = new System.Windows.Forms.ListBox();
            this.label4 = new System.Windows.Forms.Label();
            this.cboPayrate = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.dtpWorkDate = new System.Windows.Forms.DateTimePicker();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtEmployeeName = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.txtEmployeeID = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnSubmitEmployee
            // 
            this.btnSubmitEmployee.Location = new System.Drawing.Point(98, 329);
            this.btnSubmitEmployee.Name = "btnSubmitEmployee";
            this.btnSubmitEmployee.Size = new System.Drawing.Size(169, 40);
            this.btnSubmitEmployee.TabIndex = 2;
            this.btnSubmitEmployee.Text = "&Submit Employee";
            this.btnSubmitEmployee.UseVisualStyleBackColor = true;
            this.btnSubmitEmployee.Click += new System.EventHandler(this.btnSubmitEmployee_Click);
            // 
            // btnViewAllEmployees
            // 
            this.btnViewAllEmployees.Location = new System.Drawing.Point(303, 329);
            this.btnViewAllEmployees.Name = "btnViewAllEmployees";
            this.btnViewAllEmployees.Size = new System.Drawing.Size(169, 40);
            this.btnViewAllEmployees.TabIndex = 3;
            this.btnViewAllEmployees.Text = "&View All...";
            this.btnViewAllEmployees.UseVisualStyleBackColor = true;
            this.btnViewAllEmployees.Click += new System.EventHandler(this.btnViewAllEmployees_Click);
            // 
            // btnExit
            // 
            this.btnExit.Location = new System.Drawing.Point(573, 329);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(169, 40);
            this.btnExit.TabIndex = 4;
            this.btnExit.Text = "E&xit";
            this.btnExit.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.lstHours);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.cboPayrate);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.dtpWorkDate);
            this.groupBox1.Location = new System.Drawing.Point(12, 151);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(859, 140);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Employee Time Card";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(610, 48);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(66, 25);
            this.label5.TabIndex = 5;
            this.label5.Text = "&Hours:";
            // 
            // lstHours
            // 
            this.lstHours.FormattingEnabled = true;
            this.lstHours.ItemHeight = 25;
            this.lstHours.Location = new System.Drawing.Point(704, 48);
            this.lstHours.Name = "lstHours";
            this.lstHours.Size = new System.Drawing.Size(149, 79);
            this.lstHours.TabIndex = 6;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(42, 56);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(78, 25);
            this.label4.TabIndex = 1;
            this.label4.Text = "&Payrate:";
            // 
            // cboPayrate
            // 
            this.cboPayrate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cboPayrate.FormattingEnabled = true;
            this.cboPayrate.Location = new System.Drawing.Point(126, 48);
            this.cboPayrate.Name = "cboPayrate";
            this.cboPayrate.Size = new System.Drawing.Size(123, 33);
            this.cboPayrate.TabIndex = 2;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(299, 51);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(102, 25);
            this.label3.TabIndex = 3;
            this.label3.Text = "&Work date:";
            // 
            // dtpWorkDate
            // 
            this.dtpWorkDate.Format = System.Windows.Forms.DateTimePickerFormat.Short;
            this.dtpWorkDate.Location = new System.Drawing.Point(407, 45);
            this.dtpWorkDate.Name = "dtpWorkDate";
            this.dtpWorkDate.Size = new System.Drawing.Size(167, 32);
            this.dtpWorkDate.TabIndex = 4;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.txtEmployeeName);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.txtEmployeeID);
            this.groupBox2.Location = new System.Drawing.Point(12, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(864, 133);
            this.groupBox2.TabIndex = 0;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Employee";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(304, 53);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(66, 25);
            this.label2.TabIndex = 3;
            this.label2.Text = "&Name:";
            // 
            // txtEmployeeName
            // 
            this.txtEmployeeName.Location = new System.Drawing.Point(412, 47);
            this.txtEmployeeName.Name = "txtEmployeeName";
            this.txtEmployeeName.Size = new System.Drawing.Size(329, 32);
            this.txtEmployeeName.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(91, 50);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(34, 25);
            this.label1.TabIndex = 1;
            this.label1.Text = "&ID:";
            // 
            // txtEmployeeID
            // 
            this.txtEmployeeID.Location = new System.Drawing.Point(131, 46);
            this.txtEmployeeID.Name = "txtEmployeeID";
            this.txtEmployeeID.Size = new System.Drawing.Size(123, 32);
            this.txtEmployeeID.TabIndex = 2;
            // 
            // frmTimeCard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(894, 388);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.btnViewAllEmployees);
            this.Controls.Add(this.btnSubmitEmployee);
            this.Font = new System.Drawing.Font("Segoe UI", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.Name = "frmTimeCard";
            this.Text = "Employee Time Card";
            this.Load += new System.EventHandler(this.frmLoad);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button btnSubmitEmployee;
        private System.Windows.Forms.Button btnViewAllEmployees;
        private System.Windows.Forms.Button btnExit;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ListBox lstHours;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox cboPayrate;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.DateTimePicker dtpWorkDate;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtEmployeeName;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtEmployeeID;
    }
}

