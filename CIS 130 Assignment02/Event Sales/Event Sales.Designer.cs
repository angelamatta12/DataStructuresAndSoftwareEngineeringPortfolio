
namespace Event_Sales
{
    partial class frmSalesEvent
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.lstGrade = new System.Windows.Forms.ListBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtLastName = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.txtFirstName = new System.Windows.Forms.TextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.calEventDate = new System.Windows.Forms.MonthCalendar();
            this.rdoBasketball = new System.Windows.Forms.RadioButton();
            this.rdoFootball = new System.Windows.Forms.RadioButton();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.txtQtyPopcorn = new System.Windows.Forms.TextBox();
            this.chkPopcorn = new System.Windows.Forms.CheckBox();
            this.txtQtyLays = new System.Windows.Forms.TextBox();
            this.chkLaysChips = new System.Windows.Forms.CheckBox();
            this.txtQtySnickers = new System.Windows.Forms.TextBox();
            this.chkSnickers = new System.Windows.Forms.CheckBox();
            this.txtQtySkittles = new System.Windows.Forms.TextBox();
            this.chkSkittles = new System.Windows.Forms.CheckBox();
            this.label4 = new System.Windows.Forms.Label();
            this.txtSummary = new System.Windows.Forms.TextBox();
            this.tolButtons = new System.Windows.Forms.ToolStrip();
            this.tolbtnCalculate = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.tolbtnClear = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.tolbtnExit = new System.Windows.Forms.ToolStripButton();
            this.lblTotals = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.tolButtons.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.lstGrade);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.txtLastName);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.txtFirstName);
            this.groupBox1.Location = new System.Drawing.Point(20, 28);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(329, 290);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Seller";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(11, 122);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(55, 21);
            this.label3.TabIndex = 4;
            this.label3.Text = "&Grade:";
            // 
            // lstGrade
            // 
            this.lstGrade.FormattingEnabled = true;
            this.lstGrade.ItemHeight = 21;
            this.lstGrade.Location = new System.Drawing.Point(103, 122);
            this.lstGrade.Name = "lstGrade";
            this.lstGrade.Size = new System.Drawing.Size(204, 151);
            this.lstGrade.TabIndex = 8;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(11, 83);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(84, 21);
            this.label2.TabIndex = 2;
            this.label2.Text = "&Last name:";
            // 
            // txtLastName
            // 
            this.txtLastName.Location = new System.Drawing.Point(103, 75);
            this.txtLastName.Name = "txtLastName";
            this.txtLastName.Size = new System.Drawing.Size(191, 29);
            this.txtLastName.TabIndex = 3;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(11, 31);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(86, 21);
            this.label1.TabIndex = 0;
            this.label1.Text = "&First name:";
            // 
            // txtFirstName
            // 
            this.txtFirstName.Location = new System.Drawing.Point(103, 28);
            this.txtFirstName.Name = "txtFirstName";
            this.txtFirstName.Size = new System.Drawing.Size(191, 29);
            this.txtFirstName.TabIndex = 1;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.calEventDate);
            this.groupBox3.Controls.Add(this.rdoBasketball);
            this.groupBox3.Controls.Add(this.rdoFootball);
            this.groupBox3.Location = new System.Drawing.Point(365, 28);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(250, 290);
            this.groupBox3.TabIndex = 1;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Event and Date";
            // 
            // calEventDate
            // 
            this.calEventDate.Location = new System.Drawing.Point(11, 111);
            this.calEventDate.Name = "calEventDate";
            this.calEventDate.TabIndex = 2;
            // 
            // rdoBasketball
            // 
            this.rdoBasketball.AutoSize = true;
            this.rdoBasketball.Location = new System.Drawing.Point(28, 63);
            this.rdoBasketball.Name = "rdoBasketball";
            this.rdoBasketball.Size = new System.Drawing.Size(141, 25);
            this.rdoBasketball.TabIndex = 1;
            this.rdoBasketball.TabStop = true;
            this.rdoBasketball.Text = "&Basketball game";
            this.rdoBasketball.UseVisualStyleBackColor = true;
            // 
            // rdoFootball
            // 
            this.rdoFootball.AutoSize = true;
            this.rdoFootball.Location = new System.Drawing.Point(28, 32);
            this.rdoFootball.Name = "rdoFootball";
            this.rdoFootball.Size = new System.Drawing.Size(127, 25);
            this.rdoFootball.TabIndex = 0;
            this.rdoFootball.TabStop = true;
            this.rdoFootball.Text = "F&ootball game";
            this.rdoFootball.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.txtQtyPopcorn);
            this.groupBox2.Controls.Add(this.chkPopcorn);
            this.groupBox2.Controls.Add(this.txtQtyLays);
            this.groupBox2.Controls.Add(this.chkLaysChips);
            this.groupBox2.Controls.Add(this.txtQtySnickers);
            this.groupBox2.Controls.Add(this.chkSnickers);
            this.groupBox2.Controls.Add(this.txtQtySkittles);
            this.groupBox2.Controls.Add(this.chkSkittles);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Location = new System.Drawing.Point(642, 28);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(321, 290);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Snacks Sold";
            // 
            // txtQtyPopcorn
            // 
            this.txtQtyPopcorn.Enabled = false;
            this.txtQtyPopcorn.Location = new System.Drawing.Point(240, 184);
            this.txtQtyPopcorn.Name = "txtQtyPopcorn";
            this.txtQtyPopcorn.Size = new System.Drawing.Size(54, 29);
            this.txtQtyPopcorn.TabIndex = 9;
            // 
            // chkPopcorn
            // 
            this.chkPopcorn.AutoSize = true;
            this.chkPopcorn.Location = new System.Drawing.Point(20, 186);
            this.chkPopcorn.Name = "chkPopcorn";
            this.chkPopcorn.Size = new System.Drawing.Size(151, 25);
            this.chkPopcorn.TabIndex = 8;
            this.chkPopcorn.Text = "&Popcorn bag (.65)";
            this.chkPopcorn.UseVisualStyleBackColor = true;
            this.chkPopcorn.CheckedChanged += new System.EventHandler(this.chkPopcorn_CheckedChanged);
            // 
            // txtQtyLays
            // 
            this.txtQtyLays.Enabled = false;
            this.txtQtyLays.Location = new System.Drawing.Point(240, 149);
            this.txtQtyLays.Name = "txtQtyLays";
            this.txtQtyLays.Size = new System.Drawing.Size(54, 29);
            this.txtQtyLays.TabIndex = 5;
            // 
            // chkLaysChips
            // 
            this.chkLaysChips.AutoSize = true;
            this.chkLaysChips.Location = new System.Drawing.Point(20, 153);
            this.chkLaysChips.Name = "chkLaysChips";
            this.chkLaysChips.Size = new System.Drawing.Size(158, 25);
            this.chkLaysChips.TabIndex = 4;
            this.chkLaysChips.Text = "&Lays chip bag (.70)";
            this.chkLaysChips.UseVisualStyleBackColor = true;
            this.chkLaysChips.CheckedChanged += new System.EventHandler(this.chkLaysChips_CheckedChanged);
            // 
            // txtQtySnickers
            // 
            this.txtQtySnickers.Enabled = false;
            this.txtQtySnickers.Location = new System.Drawing.Point(240, 114);
            this.txtQtySnickers.Name = "txtQtySnickers";
            this.txtQtySnickers.Size = new System.Drawing.Size(54, 29);
            this.txtQtySnickers.TabIndex = 3;
            // 
            // chkSnickers
            // 
            this.chkSnickers.AutoSize = true;
            this.chkSnickers.Location = new System.Drawing.Point(20, 118);
            this.chkSnickers.Name = "chkSnickers";
            this.chkSnickers.Size = new System.Drawing.Size(149, 25);
            this.chkSnickers.TabIndex = 2;
            this.chkSnickers.Text = "S&nickers bar (.80)";
            this.chkSnickers.UseVisualStyleBackColor = true;
            this.chkSnickers.CheckedChanged += new System.EventHandler(this.chkSnickers_CheckedChanged);
            // 
            // txtQtySkittles
            // 
            this.txtQtySkittles.Enabled = false;
            this.txtQtySkittles.Location = new System.Drawing.Point(240, 79);
            this.txtQtySkittles.Name = "txtQtySkittles";
            this.txtQtySkittles.Size = new System.Drawing.Size(54, 29);
            this.txtQtySkittles.TabIndex = 1;
            // 
            // chkSkittles
            // 
            this.chkSkittles.AutoSize = true;
            this.chkSkittles.Location = new System.Drawing.Point(20, 81);
            this.chkSkittles.Name = "chkSkittles";
            this.chkSkittles.Size = new System.Drawing.Size(150, 25);
            this.chkSkittles.TabIndex = 0;
            this.chkSkittles.Text = "S&kittles pack (.75)";
            this.chkSkittles.UseVisualStyleBackColor = true;
            this.chkSkittles.CheckedChanged += new System.EventHandler(this.chkSkittles_CheckedChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(224, 47);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(81, 21);
            this.label4.TabIndex = 2;
            this.label4.Text = "Quantities";
            // 
            // txtSummary
            // 
            this.txtSummary.Location = new System.Drawing.Point(20, 350);
            this.txtSummary.Multiline = true;
            this.txtSummary.Name = "txtSummary";
            this.txtSummary.ReadOnly = true;
            this.txtSummary.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.txtSummary.Size = new System.Drawing.Size(946, 367);
            this.txtSummary.TabIndex = 3;
            // 
            // tolButtons
            // 
            this.tolButtons.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tolbtnCalculate,
            this.toolStripSeparator1,
            this.tolbtnClear,
            this.toolStripSeparator2,
            this.tolbtnExit});
            this.tolButtons.Location = new System.Drawing.Point(0, 0);
            this.tolButtons.Name = "tolButtons";
            this.tolButtons.Size = new System.Drawing.Size(987, 25);
            this.tolButtons.TabIndex = 4;
            this.tolButtons.Text = "toolStrip1";
            this.tolButtons.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.tolButtons_ItemClicked);
            // 
            // tolbtnCalculate
            // 
            this.tolbtnCalculate.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.tolbtnCalculate.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tolbtnCalculate.Name = "tolbtnCalculate";
            this.tolbtnCalculate.Size = new System.Drawing.Size(60, 22);
            this.tolbtnCalculate.Text = "Calculate";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // tolbtnClear
            // 
            this.tolbtnClear.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.tolbtnClear.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tolbtnClear.Name = "tolbtnClear";
            this.tolbtnClear.Size = new System.Drawing.Size(38, 22);
            this.tolbtnClear.Text = "Clear";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // tolbtnExit
            // 
            this.tolbtnExit.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.tolbtnExit.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tolbtnExit.Name = "tolbtnExit";
            this.tolbtnExit.Size = new System.Drawing.Size(30, 22);
            this.tolbtnExit.Text = "Exit";
            // 
            // lblTotals
            // 
            this.lblTotals.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lblTotals.Font = new System.Drawing.Font("Segoe UI", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.lblTotals.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(0)))), ((int)(((byte)(192)))));
            this.lblTotals.Location = new System.Drawing.Point(20, 318);
            this.lblTotals.Name = "lblTotals";
            this.lblTotals.Size = new System.Drawing.Size(946, 29);
            this.lblTotals.TabIndex = 9;
            this.lblTotals.Text = "Totals:";
            // 
            // frmSalesEvent
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 21F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(987, 720);
            this.Controls.Add(this.lblTotals);
            this.Controls.Add(this.tolButtons);
            this.Controls.Add(this.txtSummary);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox1);
            this.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.Name = "frmSalesEvent";
            this.Load += new System.EventHandler(this.frmSalesEvent_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.tolButtons.ResumeLayout(false);
            this.tolButtons.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ListBox lstGrade;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtLastName;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtFirstName;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.MonthCalendar calEventDate;
        private System.Windows.Forms.RadioButton rdoBasketball;
        private System.Windows.Forms.RadioButton rdoFootball;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox txtQtyPopcorn;
        private System.Windows.Forms.CheckBox chkPopcorn;
        private System.Windows.Forms.TextBox txtQtyLays;
        private System.Windows.Forms.CheckBox chkLaysChips;
        private System.Windows.Forms.TextBox txtQtySnickers;
        private System.Windows.Forms.CheckBox chkSnickers;
        private System.Windows.Forms.TextBox txtQtySkittles;
        private System.Windows.Forms.CheckBox chkSkittles;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtSummary;
        private System.Windows.Forms.ToolStrip tolButtons;
        private System.Windows.Forms.ToolStripButton tolbtnCalculate;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripButton tolbtnClear;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripButton tolbtnExit;
        private System.Windows.Forms.Label lblTotals;

    }
}

