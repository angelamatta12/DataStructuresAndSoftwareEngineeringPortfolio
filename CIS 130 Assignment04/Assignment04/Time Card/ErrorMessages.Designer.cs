
namespace Time_Card
{
    partial class frmErrorMessages
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
            this.lblErrorMessages = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // lblErrorMessages
            // 
            this.lblErrorMessages.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lblErrorMessages.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lblErrorMessages.Location = new System.Drawing.Point(0, 0);
            this.lblErrorMessages.Name = "lblErrorMessages";
            this.lblErrorMessages.Size = new System.Drawing.Size(1273, 663);
            this.lblErrorMessages.TabIndex = 0;
            // 
            // frmErrorMessages
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 21F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1273, 663);
            this.Controls.Add(this.lblErrorMessages);
            this.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "frmErrorMessages";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Attention!";
            this.ResumeLayout(false);

        }

        #endregion

        public System.Windows.Forms.Label lblErrorMessages;
    }
}