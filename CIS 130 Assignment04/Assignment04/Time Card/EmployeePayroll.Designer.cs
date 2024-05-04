
namespace Time_Card
{
    partial class frmViewAllEmployees
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.lstAllEmployees = new System.Windows.Forms.ListBox();
            this.stbTotals = new System.Windows.Forms.StatusStrip();
            this.tolCaption01 = new System.Windows.Forms.ToolStripStatusLabel();
            this.lblTotalHours = new System.Windows.Forms.ToolStripStatusLabel();
            this.stbTotals.SuspendLayout();
            this.SuspendLayout();
            // 
            // lstAllEmployees
            // 
            this.lstAllEmployees.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lstAllEmployees.FormattingEnabled = true;
            this.lstAllEmployees.ItemHeight = 21;
            this.lstAllEmployees.Location = new System.Drawing.Point(0, 0);
            this.lstAllEmployees.Name = "lstAllEmployees";
            this.lstAllEmployees.Size = new System.Drawing.Size(1071, 511);
            this.lstAllEmployees.TabIndex = 0;
            // 
            // stbTotals
            // 
            this.stbTotals.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tolCaption01,
            this.lblTotalHours});
            this.stbTotals.Location = new System.Drawing.Point(0, 489);
            this.stbTotals.Name = "stbTotals";
            this.stbTotals.Size = new System.Drawing.Size(1071, 22);
            this.stbTotals.TabIndex = 1;
            this.stbTotals.Text = "statusStrip1";
            // 
            // tolCaption01
            // 
            this.tolCaption01.Name = "tolCaption01";
            this.tolCaption01.Size = new System.Drawing.Size(68, 17);
            this.tolCaption01.Text = "Total hours:";
            // 
            // lblTotalHours
            // 
            this.lblTotalHours.AutoSize = false;
            this.lblTotalHours.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom)));
            this.lblTotalHours.Name = "lblTotalHours";
            this.lblTotalHours.Size = new System.Drawing.Size(50, 17);
            // 
            // frmViewAllEmployees
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 21F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1071, 511);
            this.Controls.Add(this.stbTotals);
            this.Controls.Add(this.lstAllEmployees);
            this.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.Name = "frmViewAllEmployees";
            this.Text = "Employee Payroll List";
            this.stbTotals.ResumeLayout(false);
            this.stbTotals.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Windows.Forms.ListBox lstAllEmployees;
        public System.Windows.Forms.StatusStrip stbTotals;
        public System.Windows.Forms.ToolStripStatusLabel tolCaption01;
        public System.Windows.Forms.ToolStripStatusLabel lblTotalHours;
    }
}