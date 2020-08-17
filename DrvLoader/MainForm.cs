using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DrvLoader
{
    public partial class MainForm : Form
    {
        [DllImport("dllSrvRunner.dll", EntryPoint = "Create", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, SetLastError = true)]
        private extern static void Create(string drvPath, string srvName);

        [DllImport("dllSrvRunner.dll", EntryPoint = "Start", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, SetLastError = true)]
        private extern static void Start();

        [DllImport("dllSrvRunner.dll", EntryPoint = "Stop", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, SetLastError = true)]
        private extern static void Stop();

        [DllImport("dllSrvRunner.dll", EntryPoint = "Delete", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode, SetLastError = true)]
        private extern static void Delete();

        string drvPath, srvName;

        public MainForm(string[] args)
        {
            InitializeComponent();
            drvPath = "";
            srvName = "";
            if (args.Length > 0)
            {
                txtDrvPath.Text = args[0];
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
            try
            {
                Create(drvPath, srvName);
                MessageBox.Show("安装成功。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                btnBrow.Enabled = btnInst.Enabled = txtSrvName.Enabled = false;
                btnStart.Enabled = btnDel.Enabled = true;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            try
            {
                Start();
                MessageBox.Show("服务已启动。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                btnStart.Enabled = btnDel.Enabled = false;
                btnStop.Enabled = true;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            try
            {
                Stop();
                MessageBox.Show("服务停止。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                btnStart.Enabled = btnDel.Enabled = true;
                btnStop.Enabled = false;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void btnDel_Click(object sender, EventArgs e)
        {
            try
            {
                Delete();
                MessageBox.Show("卸载成功。", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                btnStart.Enabled = btnStop.Enabled = btnDel.Enabled = false;
                btnBrow.Enabled = btnInst.Enabled = txtSrvName.Enabled = true;
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }

        }

    }
}
