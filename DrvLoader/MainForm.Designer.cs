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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.lblDrvPath = new System.Windows.Forms.Label();
            this.btnBrow = new System.Windows.Forms.Button();
            this.btnInst = new System.Windows.Forms.Button();
            this.btnStart = new System.Windows.Forms.Button();
            this.btnStop = new System.Windows.Forms.Button();
            this.btnDel = new System.Windows.Forms.Button();
            this.lblSrvName = new System.Windows.Forms.Label();
            this.txtSrvName = new System.Windows.Forms.TextBox();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.tlpMain = new System.Windows.Forms.TableLayoutPanel();
            this.pnlDrv = new System.Windows.Forms.Panel();
            this.txtDrvPath = new System.Windows.Forms.TextBox();
            this.pnlSrv = new System.Windows.Forms.Panel();
            this.btnLookup = new System.Windows.Forms.Button();
            this.pnlLog = new System.Windows.Forms.Panel();
            this.txtLog = new System.Windows.Forms.TextBox();
            this.chkAutoUnload = new System.Windows.Forms.CheckBox();
            this.pnlChk = new System.Windows.Forms.Panel();
            this.tlpMain.SuspendLayout();
            this.pnlDrv.SuspendLayout();
            this.pnlSrv.SuspendLayout();
            this.pnlLog.SuspendLayout();
            this.pnlChk.SuspendLayout();
            this.SuspendLayout();
            // 
            // lblDrvPath
            // 
            this.lblDrvPath.AutoSize = true;
            this.lblDrvPath.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblDrvPath.Location = new System.Drawing.Point(13, 8);
            this.lblDrvPath.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblDrvPath.Name = "lblDrvPath";
            this.lblDrvPath.Size = new System.Drawing.Size(86, 24);
            this.lblDrvPath.TabIndex = 0;
            this.lblDrvPath.Text = "驱动文件:";
            // 
            // btnBrow
            // 
            this.btnBrow.AutoSize = true;
            this.btnBrow.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnBrow.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnBrow.Location = new System.Drawing.Point(632, 2);
            this.btnBrow.Margin = new System.Windows.Forms.Padding(4);
            this.btnBrow.Name = "btnBrow";
            this.btnBrow.Size = new System.Drawing.Size(71, 34);
            this.btnBrow.TabIndex = 2;
            this.btnBrow.Text = "浏览…";
            this.btnBrow.UseVisualStyleBackColor = true;
            this.btnBrow.Click += new System.EventHandler(this.btnBrow_Click);
            // 
            // btnInst
            // 
            this.btnInst.AutoSize = true;
            this.btnInst.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnInst.Enabled = false;
            this.btnInst.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnInst.Location = new System.Drawing.Point(391, 4);
            this.btnInst.Margin = new System.Windows.Forms.Padding(4);
            this.btnInst.Name = "btnInst";
            this.btnInst.Size = new System.Drawing.Size(56, 34);
            this.btnInst.TabIndex = 3;
            this.btnInst.Text = "安装";
            this.btnInst.UseVisualStyleBackColor = true;
            this.btnInst.Click += new System.EventHandler(this.btnInst_Click);
            // 
            // btnStart
            // 
            this.btnStart.AutoSize = true;
            this.btnStart.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnStart.Enabled = false;
            this.btnStart.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnStart.Location = new System.Drawing.Point(519, 4);
            this.btnStart.Margin = new System.Windows.Forms.Padding(4);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(56, 34);
            this.btnStart.TabIndex = 4;
            this.btnStart.Text = "启动";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // btnStop
            // 
            this.btnStop.AutoSize = true;
            this.btnStop.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnStop.Enabled = false;
            this.btnStop.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnStop.Location = new System.Drawing.Point(583, 4);
            this.btnStop.Margin = new System.Windows.Forms.Padding(4);
            this.btnStop.Name = "btnStop";
            this.btnStop.Size = new System.Drawing.Size(56, 34);
            this.btnStop.TabIndex = 5;
            this.btnStop.Text = "停止";
            this.btnStop.UseVisualStyleBackColor = true;
            this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
            // 
            // btnDel
            // 
            this.btnDel.AutoSize = true;
            this.btnDel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnDel.Enabled = false;
            this.btnDel.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnDel.Location = new System.Drawing.Point(647, 4);
            this.btnDel.Margin = new System.Windows.Forms.Padding(4);
            this.btnDel.Name = "btnDel";
            this.btnDel.Size = new System.Drawing.Size(56, 34);
            this.btnDel.TabIndex = 6;
            this.btnDel.Text = "卸载";
            this.btnDel.UseVisualStyleBackColor = true;
            this.btnDel.Click += new System.EventHandler(this.btnDel_Click);
            // 
            // lblSrvName
            // 
            this.lblSrvName.AutoSize = true;
            this.lblSrvName.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblSrvName.Location = new System.Drawing.Point(35, 10);
            this.lblSrvName.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblSrvName.Name = "lblSrvName";
            this.lblSrvName.Size = new System.Drawing.Size(68, 24);
            this.lblSrvName.TabIndex = 7;
            this.lblSrvName.Text = "服务名:";
            // 
            // txtSrvName
            // 
            this.txtSrvName.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtSrvName.Location = new System.Drawing.Point(112, 6);
            this.txtSrvName.Margin = new System.Windows.Forms.Padding(4);
            this.txtSrvName.Name = "txtSrvName";
            this.txtSrvName.Size = new System.Drawing.Size(269, 30);
            this.txtSrvName.TabIndex = 8;
            this.txtSrvName.TextChanged += new System.EventHandler(this.txtSrvName_TextChanged);
            // 
            // tlpMain
            // 
            this.tlpMain.AutoSize = true;
            this.tlpMain.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.tlpMain.ColumnCount = 1;
            this.tlpMain.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tlpMain.Controls.Add(this.pnlDrv, 0, 0);
            this.tlpMain.Controls.Add(this.pnlSrv, 0, 1);
            this.tlpMain.Controls.Add(this.pnlLog, 0, 2);
            this.tlpMain.Controls.Add(this.pnlChk, 0, 3);
            this.tlpMain.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tlpMain.Location = new System.Drawing.Point(0, 0);
            this.tlpMain.Margin = new System.Windows.Forms.Padding(4);
            this.tlpMain.Name = "tlpMain";
            this.tlpMain.RowCount = 4;
            this.tlpMain.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tlpMain.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tlpMain.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tlpMain.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tlpMain.Size = new System.Drawing.Size(760, 450);
            this.tlpMain.TabIndex = 10;
            // 
            // pnlDrv
            // 
            this.pnlDrv.AutoSize = true;
            this.pnlDrv.Controls.Add(this.lblDrvPath);
            this.pnlDrv.Controls.Add(this.txtDrvPath);
            this.pnlDrv.Controls.Add(this.btnBrow);
            this.pnlDrv.Location = new System.Drawing.Point(4, 4);
            this.pnlDrv.Margin = new System.Windows.Forms.Padding(4);
            this.pnlDrv.Name = "pnlDrv";
            this.pnlDrv.Size = new System.Drawing.Size(707, 40);
            this.pnlDrv.TabIndex = 0;
            // 
            // txtDrvPath
            // 
            this.txtDrvPath.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtDrvPath.Location = new System.Drawing.Point(112, 4);
            this.txtDrvPath.Margin = new System.Windows.Forms.Padding(4);
            this.txtDrvPath.Name = "txtDrvPath";
            this.txtDrvPath.ReadOnly = true;
            this.txtDrvPath.Size = new System.Drawing.Size(512, 30);
            this.txtDrvPath.TabIndex = 1;
            this.txtDrvPath.TextChanged += new System.EventHandler(this.txtDrvPath_TextChanged);
            // 
            // pnlSrv
            // 
            this.pnlSrv.AutoSize = true;
            this.pnlSrv.Controls.Add(this.btnLookup);
            this.pnlSrv.Controls.Add(this.lblSrvName);
            this.pnlSrv.Controls.Add(this.txtSrvName);
            this.pnlSrv.Controls.Add(this.btnDel);
            this.pnlSrv.Controls.Add(this.btnInst);
            this.pnlSrv.Controls.Add(this.btnStop);
            this.pnlSrv.Controls.Add(this.btnStart);
            this.pnlSrv.Location = new System.Drawing.Point(4, 52);
            this.pnlSrv.Margin = new System.Windows.Forms.Padding(4);
            this.pnlSrv.Name = "pnlSrv";
            this.pnlSrv.Size = new System.Drawing.Size(707, 42);
            this.pnlSrv.TabIndex = 1;
            // 
            // btnLookup
            // 
            this.btnLookup.AutoSize = true;
            this.btnLookup.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnLookup.Enabled = false;
            this.btnLookup.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnLookup.Location = new System.Drawing.Point(455, 4);
            this.btnLookup.Margin = new System.Windows.Forms.Padding(4);
            this.btnLookup.Name = "btnLookup";
            this.btnLookup.Size = new System.Drawing.Size(56, 34);
            this.btnLookup.TabIndex = 9;
            this.btnLookup.Text = "查询";
            this.btnLookup.UseVisualStyleBackColor = true;
            this.btnLookup.Click += new System.EventHandler(this.btnLookup_Click);
            // 
            // pnlLog
            // 
            this.pnlLog.AutoSize = true;
            this.pnlLog.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.pnlLog.Controls.Add(this.txtLog);
            this.pnlLog.Location = new System.Drawing.Point(4, 102);
            this.pnlLog.Margin = new System.Windows.Forms.Padding(4);
            this.pnlLog.Name = "pnlLog";
            this.pnlLog.Size = new System.Drawing.Size(707, 276);
            this.pnlLog.TabIndex = 2;
            // 
            // txtLog
            // 
            this.txtLog.AcceptsReturn = true;
            this.txtLog.AcceptsTab = true;
            this.txtLog.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtLog.Location = new System.Drawing.Point(4, 4);
            this.txtLog.Margin = new System.Windows.Forms.Padding(4);
            this.txtLog.Multiline = true;
            this.txtLog.Name = "txtLog";
            this.txtLog.ReadOnly = true;
            this.txtLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtLog.Size = new System.Drawing.Size(699, 268);
            this.txtLog.TabIndex = 9;
            // 
            // chkAutoUnload
            // 
            this.chkAutoUnload.AutoSize = true;
            this.chkAutoUnload.Checked = true;
            this.chkAutoUnload.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkAutoUnload.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.chkAutoUnload.Location = new System.Drawing.Point(9, 3);
            this.chkAutoUnload.Name = "chkAutoUnload";
            this.chkAutoUnload.Size = new System.Drawing.Size(262, 29);
            this.chkAutoUnload.TabIndex = 5;
            this.chkAutoUnload.Text = "退出时自动卸载安装的驱动";
            this.chkAutoUnload.UseVisualStyleBackColor = true;
            // 
            // pnlChk
            // 
            this.pnlChk.AutoSize = true;
            this.pnlChk.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.pnlChk.Controls.Add(this.chkAutoUnload);
            this.pnlChk.Location = new System.Drawing.Point(3, 385);
            this.pnlChk.Name = "pnlChk";
            this.pnlChk.Size = new System.Drawing.Size(274, 35);
            this.pnlChk.TabIndex = 3;
            // 
            // MainForm
            // 
            this.AcceptButton = this.btnLookup;
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(120F, 120F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(760, 450);
            this.Controls.Add(this.tlpMain);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.Text = "DrvLoader";
            this.TopMost = true;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.DragDrop += new System.Windows.Forms.DragEventHandler(this.MainForm_DragDrop);
            this.DragEnter += new System.Windows.Forms.DragEventHandler(this.MainForm_DragEnter);
            this.tlpMain.ResumeLayout(false);
            this.tlpMain.PerformLayout();
            this.pnlDrv.ResumeLayout(false);
            this.pnlDrv.PerformLayout();
            this.pnlSrv.ResumeLayout(false);
            this.pnlSrv.PerformLayout();
            this.pnlLog.ResumeLayout(false);
            this.pnlLog.PerformLayout();
            this.pnlChk.ResumeLayout(false);
            this.pnlChk.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label lblDrvPath;
        private System.Windows.Forms.Button btnBrow;
        private System.Windows.Forms.Button btnInst;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Button btnStop;
        private System.Windows.Forms.Button btnDel;
        private System.Windows.Forms.Label lblSrvName;
        private System.Windows.Forms.TextBox txtSrvName;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.TableLayoutPanel tlpMain;
        private System.Windows.Forms.Panel pnlDrv;
        private System.Windows.Forms.TextBox txtDrvPath;
        private System.Windows.Forms.Panel pnlSrv;
        private System.Windows.Forms.Panel pnlLog;
        private System.Windows.Forms.TextBox txtLog;
        private System.Windows.Forms.Button btnLookup;
        private System.Windows.Forms.Panel pnlChk;
        private System.Windows.Forms.CheckBox chkAutoUnload;
    }
}

