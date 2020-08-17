namespace DrvLoader
{
    partial class MainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.lblDrvPath = new System.Windows.Forms.Label();
            this.txtDrvPath = new System.Windows.Forms.TextBox();
            this.btnBrow = new System.Windows.Forms.Button();
            this.btnInst = new System.Windows.Forms.Button();
            this.btnStart = new System.Windows.Forms.Button();
            this.btnStop = new System.Windows.Forms.Button();
            this.btnDel = new System.Windows.Forms.Button();
            this.lblSrvName = new System.Windows.Forms.Label();
            this.txtSrvName = new System.Windows.Forms.TextBox();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.SuspendLayout();
            // 
            // lblDrvPath
            // 
            this.lblDrvPath.AutoSize = true;
            this.lblDrvPath.Font = new System.Drawing.Font("更纱黑体 UI SC", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblDrvPath.Location = new System.Drawing.Point(12, 9);
            this.lblDrvPath.Name = "lblDrvPath";
            this.lblDrvPath.Size = new System.Drawing.Size(68, 17);
            this.lblDrvPath.TabIndex = 0;
            this.lblDrvPath.Text = "驱动程序:";
            // 
            // txtDrvPath
            // 
            this.txtDrvPath.Enabled = false;
            this.txtDrvPath.Font = new System.Drawing.Font("更纱黑体 UI SC", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtDrvPath.Location = new System.Drawing.Point(86, 6);
            this.txtDrvPath.Name = "txtDrvPath";
            this.txtDrvPath.Size = new System.Drawing.Size(362, 24);
            this.txtDrvPath.TabIndex = 1;
            this.txtDrvPath.TextChanged += new System.EventHandler(this.txtDrvPath_TextChanged);
            // 
            // btnBrow
            // 
            this.btnBrow.AutoSize = true;
            this.btnBrow.Font = new System.Drawing.Font("更纱黑体 UI SC", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnBrow.Location = new System.Drawing.Point(454, 4);
            this.btnBrow.Name = "btnBrow";
            this.btnBrow.Size = new System.Drawing.Size(75, 27);
            this.btnBrow.TabIndex = 2;
            this.btnBrow.Text = "浏览…";
            this.btnBrow.UseVisualStyleBackColor = true;
            this.btnBrow.Click += new System.EventHandler(this.btnBrow_Click);
            // 
            // btnInst
            // 
            this.btnInst.AutoSize = true;
            this.btnInst.Enabled = false;
            this.btnInst.Font = new System.Drawing.Font("更纱黑体 UI SC", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnInst.Location = new System.Drawing.Point(211, 34);
            this.btnInst.Name = "btnInst";
            this.btnInst.Size = new System.Drawing.Size(75, 27);
            this.btnInst.TabIndex = 3;
            this.btnInst.Text = "安装";
            this.btnInst.UseVisualStyleBackColor = true;
            this.btnInst.Click += new System.EventHandler(this.btnInst_Click);
            // 
            // btnStart
            // 
            this.btnStart.AutoSize = true;
            this.btnStart.Enabled = false;
            this.btnStart.Font = new System.Drawing.Font("更纱黑体 UI SC", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnStart.Location = new System.Drawing.Point(292, 34);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(75, 27);
            this.btnStart.TabIndex = 4;
            this.btnStart.Text = "启动";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // btnStop
            // 
            this.btnStop.AutoSize = true;
            this.btnStop.Enabled = false;
            this.btnStop.Font = new System.Drawing.Font("更纱黑体 UI SC", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnStop.Location = new System.Drawing.Point(373, 34);
            this.btnStop.Name = "btnStop";
            this.btnStop.Size = new System.Drawing.Size(75, 27);
            this.btnStop.TabIndex = 5;
            this.btnStop.Text = "停止";
            this.btnStop.UseVisualStyleBackColor = true;
            this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
            // 
            // btnDel
            // 
            this.btnDel.AutoSize = true;
            this.btnDel.Enabled = false;
            this.btnDel.Font = new System.Drawing.Font("更纱黑体 UI SC", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnDel.Location = new System.Drawing.Point(454, 34);
            this.btnDel.Name = "btnDel";
            this.btnDel.Size = new System.Drawing.Size(75, 27);
            this.btnDel.TabIndex = 6;
            this.btnDel.Text = "卸载";
            this.btnDel.UseVisualStyleBackColor = true;
            this.btnDel.Click += new System.EventHandler(this.btnDel_Click);
            // 
            // lblSrvName
            // 
            this.lblSrvName.AutoSize = true;
            this.lblSrvName.Font = new System.Drawing.Font("更纱黑体 UI SC", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblSrvName.Location = new System.Drawing.Point(26, 39);
            this.lblSrvName.Name = "lblSrvName";
            this.lblSrvName.Size = new System.Drawing.Size(54, 17);
            this.lblSrvName.TabIndex = 7;
            this.lblSrvName.Text = "服务名:";
            // 
            // txtSrvName
            // 
            this.txtSrvName.Font = new System.Drawing.Font("更纱黑体 UI SC", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtSrvName.Location = new System.Drawing.Point(86, 36);
            this.txtSrvName.Name = "txtSrvName";
            this.txtSrvName.Size = new System.Drawing.Size(119, 24);
            this.txtSrvName.TabIndex = 8;
            this.txtSrvName.TextChanged += new System.EventHandler(this.txtSrvName_TextChanged);
            // 
            // MainForm
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(541, 67);
            this.Controls.Add(this.txtSrvName);
            this.Controls.Add(this.lblSrvName);
            this.Controls.Add(this.btnDel);
            this.Controls.Add(this.btnStop);
            this.Controls.Add(this.btnStart);
            this.Controls.Add(this.btnInst);
            this.Controls.Add(this.btnBrow);
            this.Controls.Add(this.txtDrvPath);
            this.Controls.Add(this.lblDrvPath);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MainForm";
            this.Text = "DrvLoader";
            this.TopMost = true;
            this.DragDrop += new System.Windows.Forms.DragEventHandler(this.MainForm_DragDrop);
            this.DragEnter += new System.Windows.Forms.DragEventHandler(this.MainForm_DragEnter);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblDrvPath;
        private System.Windows.Forms.TextBox txtDrvPath;
        private System.Windows.Forms.Button btnBrow;
        private System.Windows.Forms.Button btnInst;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Button btnStop;
        private System.Windows.Forms.Button btnDel;
        private System.Windows.Forms.Label lblSrvName;
        private System.Windows.Forms.TextBox txtSrvName;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
    }
}

