
namespace Lab02
{
    partial class frmSalesCommission
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
            this.txtSalesAmount = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.lstDepartNum = new System.Windows.Forms.ListBox();
            this.btnCommission = new System.Windows.Forms.Button();
            this.btnExit = new System.Windows.Forms.Button();
            this.lblCommEarned = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // txtSalesAmount
            // 
            this.txtSalesAmount.Location = new System.Drawing.Point(271, 16);
            this.txtSalesAmount.Name = "txtSalesAmount";
            this.txtSalesAmount.Size = new System.Drawing.Size(213, 36);
            this.txtSalesAmount.TabIndex = 1;
            this.txtSalesAmount.TextChanged += new System.EventHandler(this.txtChangeSales);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(49, 19);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(147, 30);
            this.label1.TabIndex = 0;
            this.label1.Text = "&Sales amount:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(49, 70);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(216, 30);
            this.label2.TabIndex = 2;
            this.label2.Text = "&Department number:";
            // 
            // lstDepartNum
            // 
            this.lstDepartNum.FormattingEnabled = true;
            this.lstDepartNum.ItemHeight = 30;
            this.lstDepartNum.Location = new System.Drawing.Point(271, 68);
            this.lstDepartNum.Name = "lstDepartNum";
            this.lstDepartNum.Size = new System.Drawing.Size(213, 94);
            this.lstDepartNum.TabIndex = 3;
            this.lstDepartNum.SelectedIndexChanged += new System.EventHandler(this.SelectIndexDepartment);
            // 
            // btnCommission
            // 
            this.btnCommission.Location = new System.Drawing.Point(93, 280);
            this.btnCommission.Name = "btnCommission";
            this.btnCommission.Size = new System.Drawing.Size(147, 59);
            this.btnCommission.TabIndex = 4;
            this.btnCommission.Text = "&Commission";
            this.btnCommission.UseVisualStyleBackColor = true;
            this.btnCommission.Click += new System.EventHandler(this.btnCommission_Click);
            // 
            // btnExit
            // 
            this.btnExit.Location = new System.Drawing.Point(290, 280);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(147, 59);
            this.btnExit.TabIndex = 5;
            this.btnExit.Text = "E&xit";
            this.btnExit.UseVisualStyleBackColor = true;
            this.btnExit.Click += new System.EventHandler(this.btnExit_Click);
            // 
            // lblCommEarned
            // 
            this.lblCommEarned.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lblCommEarned.Location = new System.Drawing.Point(12, 181);
            this.lblCommEarned.Name = "lblCommEarned";
            this.lblCommEarned.Size = new System.Drawing.Size(522, 83);
            this.lblCommEarned.TabIndex = 6;
            // 
            // frmSalesCommission
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 30F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(546, 364);
            this.Controls.Add(this.lblCommEarned);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.btnCommission);
            this.Controls.Add(this.lstDepartNum);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtSalesAmount);
            this.Font = new System.Drawing.Font("Segoe UI", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.Name = "frmSalesCommission";
            this.Text = "Sales Commission";
            this.Load += new System.EventHandler(this.frmSalesCommission_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtSalesAmount;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ListBox lstDepartNum;
        private System.Windows.Forms.Button btnCommission;
        private System.Windows.Forms.Button btnExit;
        private System.Windows.Forms.Label lblCommEarned;
    }
}

