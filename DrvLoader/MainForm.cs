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
            DialogResult dialogResult =
                MessageBox.Show(
                    "是否卸载已安装的驱动？",
                    "提示",
                    MessageBoxButtons.YesNoCancel,
                    MessageBoxIcon.Question);
            if (dialogResult == DialogResult.Cancel)
            {
                e.Cancel = true;
                return;
            }
            txtLog.AppendText("正在结束程序……");
            try
            {
                if (dialogResult == DialogResult.Yes)
                {
                    SrvRunner.CLear();
                }
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                txtLog.AppendText(ex.Message);
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
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                txtLog.AppendText(ex.Message + "安装已取消。\r\n");
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
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                txtLog.AppendText(ex.Message);
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
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                txtLog.AppendText(ex.Message);
            }
        }

        private void btnDel_Click(object sender, EventArgs e)
        {
            try
            {
                txtLog.AppendText(string.Format("正在删除服务 {0} ……\r\n", srvName));
                SrvRunner.Delete(srvName);
                txtLog.AppendText(string.Format("服务 {0} 已删除。\r\n", srvName));
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                txtLog.AppendText(ex.Message);
            }

        }

    }
}
