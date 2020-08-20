using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.ExceptionServices;
using System.Runtime.InteropServices;
using System.Security.Permissions;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SrvRunnerCLR;

namespace DrvLoader
{
    public partial class MainForm : Form
    {
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        private void DisplayException(Exception ex, string ExMsg = "")
        {
            MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            txtLog.AppendText(ex.Message + ExMsg);
        }

        string drvPath, srvName;

        public MainForm(string[] args)
        {
            try
            {
                SrvRunner.OpenSCM();
            }
            catch (System.Exception ex)
            {
                DisplayException(ex);
            }

            ActiveControl = txtSrvName;

            InitializeComponent();

            txtLog.AppendText("欢迎使用DrvLoader");
            drvPath = "";
            srvName = "";
            if (args.Length > 0)
            {
                txtDrvPath.Text = args[0];
                txtLog.AppendText("。\r\n");
            }
            else
            {
                txtLog.AppendText("，请选择驱动程序文件/输入服务名。\r\n");
            }
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            txtLog.AppendText("正在结束程序……");
            try
            {
                if (chkAutoUnload.Checked)
                {
                    SrvRunner.CLear();
                }
            }
            catch (System.Exception ex)
            {
                DisplayException(ex);
            }
        }

        private void MainForm_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                e.Effect = DragDropEffects.Link;
            }
            else
            {
                e.Effect = DragDropEffects.None;
            }
        }

        private void MainForm_DragDrop(object sender, DragEventArgs e)
        {
            txtDrvPath.Text = ((Array)e.Data.GetData(DataFormats.FileDrop)).GetValue(0).ToString();
        }

        private void btnBrow_Click(object sender, EventArgs e)
        {
            openFileDialog.InitialDirectory = @"C:\";
            openFileDialog.Filter = "所有文件|*.*";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                txtDrvPath.Text = openFileDialog.FileName;
            }
        }

        private void txtDrvPath_TextChanged(object sender, EventArgs e)
        {
            drvPath = txtDrvPath.Text;
            txtSrvName.Text = Path.GetFileNameWithoutExtension(drvPath);
        }

        private void txtSrvName_TextChanged(object sender, EventArgs e)
        {
            srvName = txtSrvName.Text;
            btnInst.Enabled = drvPath.Length != 0 && srvName.Length != 0;
            btnLookup.Enabled = btnStart.Enabled = btnStop.Enabled = btnDel.Enabled = srvName.Length != 0;
        }

        private void btnInst_Click(object sender, EventArgs e)
        {
            try
            {
                txtLog.AppendText("正在安装驱动……\r\n");
                SrvRunner.Create(drvPath, srvName);
                txtLog.AppendText(string.Format("安装成功。服务名：{0}\r\n", srvName));
            }
            catch (System.Exception ex)
            {
                DisplayException(ex, "安装已取消。\r\n");
            }
        }

        private void btnLookup_Click(object sender, EventArgs e)
        {
            try
            {
                txtLog.AppendText("正在查询……\r\n");
                SrvRunner.Lookup(srvName);
            }
            catch (System.ApplicationException aex)
            {
                txtLog.AppendText(aex.Message);
            }
            catch (System.Exception ex)
            {
                DisplayException(ex);
            }
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            try
            {
                txtLog.AppendText(string.Format("正在启动服务 {0} ……\r\n", srvName));
                SrvRunner.Start(srvName);
                txtLog.AppendText(string.Format("服务 {0} 已启动。\r\n", srvName));
            }
            catch (System.Exception ex)
            {
                DisplayException(ex);
            }
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            try
            {
                txtLog.AppendText(string.Format("正在停止服务 {0} ……\r\n", srvName));
                SrvRunner.Stop(srvName);
                txtLog.AppendText(string.Format("服务 {0} 已停止。\r\n", srvName));
            }
            catch (System.Exception ex)
            {
                DisplayException(ex);
            }
        }

        private void btnDel_Click(object sender, EventArgs e)
        {
            try
            {
                txtLog.AppendText(string.Format("正在删除服务 {0} ……\r\n", srvName));
                SrvRunner.Delete(srvName, false);
                txtLog.AppendText(string.Format("服务 {0} 已删除。\r\n", srvName));
            }
            catch (System.Exception ex)
            {
                if (string.Equals(ex.Message, "删除操作需要确认。"))
                {
                    DialogResult dialogResult =
                    MessageBox.Show(
                        string.Format("指定的服务({0})似乎不是由本程序创建的。确定要删除吗？", srvName),
                        "提示",
                        MessageBoxButtons.OKCancel,
                        MessageBoxIcon.Question);
                    if (dialogResult == DialogResult.OK)
                    {
                        try
                        {
                            SrvRunner.Delete(srvName, true);
                            txtLog.AppendText(string.Format("服务 {0} 已删除。\r\n", srvName));
                        }
                        catch (System.Exception exce)
                        {
                            DisplayException(exce);
                        }
                    }
                    else
                    {
                        txtLog.AppendText("删除取消。\r\n");
                    }
                }
                else
                {
                    DisplayException(ex);
                }
            }

        }

    }
}
