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
            this.pnlLog = new System.Windows.Forms.Panel();
            this.txtLog = new System.Windows.Forms.TextBox();
            this.tlpMain.SuspendLayout();
            this.pnlDrv.SuspendLayout();
            this.pnlSrv.SuspendLayout();
            this.pnlLog.SuspendLayout();
            this.SuspendLayout();
            // 
            // lblDrvPath
            // 
            this.lblDrvPath.AutoSize = true;
            this.lblDrvPath.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblDrvPath.Location = new System.Drawing.Point(10, 6);
            this.lblDrvPath.Name = "lblDrvPath";
            this.lblDrvPath.Size = new System.Drawing.Size(68, 20);
            this.lblDrvPath.TabIndex = 0;
            this.lblDrvPath.Text = "驱动文件:";
            // 
            // btnBrow
            // 
            this.btnBrow.AutoSize = true;
            this.btnBrow.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnBrow.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnBrow.Location = new System.Drawing.Point(441, 1);
            this.btnBrow.Name = "btnBrow";
            this.btnBrow.Size = new System.Drawing.Size(58, 30);
            this.btnBrow.TabIndex = 2;
            this.btnBrow.Text = "浏览…";
            this.btnBrow.UseVisualStyleBackColor = true;
            this.btnBrow.Click += new System.EventHandler(this.btnBrow_Click);
            // 
            // btnInst
            // 
            this.btnInst.AutoSize = true;
            this.btnInst.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnInst.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnInst.Location = new System.Drawing.Point(293, 3);
            this.btnInst.Name = "btnInst";
            this.btnInst.Size = new System.Drawing.Size(47, 30);
            this.btnInst.TabIndex = 3;
            this.btnInst.Text = "安装";
            this.btnInst.UseVisualStyleBackColor = true;
            this.btnInst.Click += new System.EventHandler(this.btnInst_Click);
            // 
            // btnStart
            // 
            this.btnStart.AutoSize = true;
            this.btnStart.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnStart.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnStart.Location = new System.Drawing.Point(346, 3);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(47, 30);
            this.btnStart.TabIndex = 4;
            this.btnStart.Text = "启动";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // btnStop
            // 
            this.btnStop.AutoSize = true;
            this.btnStop.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnStop.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnStop.Location = new System.Drawing.Point(399, 3);
            this.btnStop.Name = "btnStop";
            this.btnStop.Size = new System.Drawing.Size(47, 30);
            this.btnStop.TabIndex = 5;
            this.btnStop.Text = "停止";
            this.btnStop.UseVisualStyleBackColor = true;
            this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
            // 
            // btnDel
            // 
            this.btnDel.AutoSize = true;
            this.btnDel.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.btnDel.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnDel.Location = new System.Drawing.Point(452, 3);
            this.btnDel.Name = "btnDel";
            this.btnDel.Size = new System.Drawing.Size(47, 30);
            this.btnDel.TabIndex = 6;
            this.btnDel.Text = "卸载";
            this.btnDel.UseVisualStyleBackColor = true;
            this.btnDel.Click += new System.EventHandler(this.btnDel_Click);
            // 
            // lblSrvName
            // 
            this.lblSrvName.AutoSize = true;
            this.lblSrvName.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lblSrvName.Location = new System.Drawing.Point(26, 8);
            this.lblSrvName.Name = "lblSrvName";
            this.lblSrvName.Size = new System.Drawing.Size(54, 20);
            this.lblSrvName.TabIndex = 7;
            this.lblSrvName.Text = "服务名:";
            // 
            // txtSrvName
            // 
            this.txtSrvName.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtSrvName.Location = new System.Drawing.Point(84, 5);
            this.txtSrvName.Name = "txtSrvName";
            this.txtSrvName.Size = new System.Drawing.Size(203, 25);
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
            this.tlpMain.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tlpMain.Location = new System.Drawing.Point(0, 0);
            this.tlpMain.Name = "tlpMain";
            this.tlpMain.RowCount = 3;
            this.tlpMain.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tlpMain.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tlpMain.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tlpMain.Size = new System.Drawing.Size(570, 277);
            this.tlpMain.TabIndex = 10;
            // 
            // pnlDrv
            // 
            this.pnlDrv.AutoSize = true;
            this.pnlDrv.Controls.Add(this.lblDrvPath);
            this.pnlDrv.Controls.Add(this.txtDrvPath);
            this.pnlDrv.Controls.Add(this.btnBrow);
            this.pnlDrv.Location = new System.Drawing.Point(3, 3);
            this.pnlDrv.Name = "pnlDrv";
            this.pnlDrv.Size = new System.Drawing.Size(502, 34);
            this.pnlDrv.TabIndex = 0;
            // 
            // txtDrvPath
            // 
            this.txtDrvPath.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtDrvPath.Location = new System.Drawing.Point(84, 3);
            this.txtDrvPath.Name = "txtDrvPath";
            this.txtDrvPath.ReadOnly = true;
            this.txtDrvPath.Size = new System.Drawing.Size(351, 25);
            this.txtDrvPath.TabIndex = 1;
            this.txtDrvPath.TextChanged += new System.EventHandler(this.txtDrvPath_TextChanged);
            // 
            // pnlSrv
            // 
            this.pnlSrv.AutoSize = true;
            this.pnlSrv.Controls.Add(this.lblSrvName);
            this.pnlSrv.Controls.Add(this.txtSrvName);
            this.pnlSrv.Controls.Add(this.btnDel);
            this.pnlSrv.Controls.Add(this.btnInst);
            this.pnlSrv.Controls.Add(this.btnStop);
            this.pnlSrv.Controls.Add(this.btnStart);
            this.pnlSrv.Location = new System.Drawing.Point(3, 43);
            this.pnlSrv.Name = "pnlSrv";
            this.pnlSrv.Size = new System.Drawing.Size(502, 36);
            this.pnlSrv.TabIndex = 1;
            // 
            // pnlLog
            // 
            this.pnlLog.AutoSize = true;
            this.pnlLog.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.pnlLog.Controls.Add(this.txtLog);
            this.pnlLog.Location = new System.Drawing.Point(3, 85);
            this.pnlLog.Name = "pnlLog";
            this.pnlLog.Size = new System.Drawing.Size(502, 142);
            this.pnlLog.TabIndex = 2;
            // 
            // txtLog
            // 
            this.txtLog.AcceptsReturn = true;
            this.txtLog.AcceptsTab = true;
            this.txtLog.Font = new System.Drawing.Font("Microsoft YaHei UI", 10.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txtLog.Location = new System.Drawing.Point(3, 3);
            this.txtLog.Multiline = true;
            this.txtLog.Name = "txtLog";
            this.txtLog.ReadOnly = true;
            this.txtLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtLog.Size = new System.Drawing.Size(496, 136);
            this.txtLog.TabIndex = 9;
            // 
            // MainForm
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.ClientSize = new System.Drawing.Size(570, 277);
            this.Controls.Add(this.tlpMain);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
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
    }
}

