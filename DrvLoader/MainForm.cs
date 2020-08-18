using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
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
        //[DllImport("dllSrvRunner.dll", EntryPoint = "OpenSCM", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, SetLastError = true)]
        //private extern static void OpenSCM();

        //[DllImport("dllSrvRunner.dll", EntryPoint = "Create", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, SetLastError = true)]
        //private extern static void Create(string drvPath, string srvName);

        //[DllImport("dllSrvRunner.dll", EntryPoint = "Start", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, SetLastError = true)]
        //private extern static void Start(string srvName);

        //[DllImport("dllSrvRunner.dll", EntryPoint = "Stop", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, SetLastError = true)]
        //private extern static void Stop(string srvName);

        //[DllImport("dllSrvRunner.dll", EntryPoint = "Delete", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, SetLastError = true)]
        //private extern static void Delete(string srvName);

        //[DllImport("dllSrvRunner.dll", EntryPoint = "End", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, SetLastError = true)]
        //private extern static void End();

        string drvPath, srvName;

        public MainForm(string[] args)
        {
            InitializeComponent();

            try
            {
                SrvRunner.OpenSCM();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            drvPath = "";
            srvName = "";
            txtLog.AppendText("欢迎使用DrvLoader.\r\n");
            if (args.Length > 0)
            {
                txtDrvPath.Text = args[0];
            }
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            txtLog.AppendText("正在结束程序……");
            SrvRunner.End();
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
        }

        private void btnInst_Click(object sender, EventArgs e)
        {
            if (drvPath.Length == 0)
            {
                txtLog.AppendText("请输入驱动文件地址。\r\n");
                return;
            }
            else if (srvName.Length == 0)
            {
                txtLog.AppendText("请输入服务名。\r\n");
                return;
            }

            try
            {
                txtLog.AppendText("正在安装驱动……\r\n");
                SrvRunner.Create(drvPath, srvName);
                txtLog.AppendText(string.Format("安装成功。服务名：{0}\r\n", srvName));
            }
            catch (System.Exception ex)
            {
                txtLog.AppendText("安装失败。原因：" + ex.Message + "\r\n");
            }
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            try
            {
                txtLog.AppendText("正在启动服务……\r\n");
                SrvRunner.Start(srvName);
                txtLog.AppendText(string.Format("服务{0}已启动。\r\n", srvName));
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            try
            {
                SrvRunner.Stop(srvName);
                MessageBox.Show("服务停止。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                btnStart.Enabled = btnDel.Enabled = true;
                btnStop.Enabled = false;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnDel_Click(object sender, EventArgs e)
        {
            try
            {
                SrvRunner.Delete(srvName);
                MessageBox.Show("卸载成功。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                btnStart.Enabled = btnStop.Enabled = btnDel.Enabled = false;
                btnBrow.Enabled = btnInst.Enabled = txtSrvName.Enabled = true;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

        }

    }
}
