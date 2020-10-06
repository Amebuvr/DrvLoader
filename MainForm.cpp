#include "MainForm.h"
#include "sstream"

using namespace System;
using namespace System::IO;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

using namespace DrvLoader;

inline Void MainForm::DisplayException(STATUS& ex)
{
    DisplayException(ex, TEXT(""));
}

inline Void MainForm::DisplayException(STATUS& ex, String^ log)
{
    String^ Message = (gcnew String(ex.Msg));
    MessageBox::Show(
        Message,
        TEXT("错误"),
        MessageBoxButtons::OK,
        MessageBoxIcon::Error);
    txtLog->AppendText(Message + log);
}

MainForm::MainForm(array<String^>^ args)
{
    InitializeComponent();

    try
    {
        STATUS ret = SrvUtils::OpenSCM();
        if (!ret.Success())
        {
            throw ret;
        }
    }
    catch (STATUS ret)
    {
        DisplayException(ret);
        System::Environment::Exit(0);
    }

    ActiveControl = txtSrvName;

    txtLog->AppendText("欢迎使用DrvLoader");

    if (args->Length > 0)
    {
        txtDrvPath->Text = args[0];
        txtLog->AppendText("。\r\n");
    }
    else
    {
        txtLog->AppendText("，请选择驱动程序文件/输入服务名。\r\n");
    }
}

MainForm::~MainForm()
{
    if (components)
    {
        delete components;
    }
}

System::Void MainForm::MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
{
    txtLog->AppendText("正在结束程序……");
    if (chkAutoUnload->Checked)
    {
        SrvUtils::Clear();
    }
}

System::Void MainForm::MainForm_DragEnter(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e)
{
    if (e->Data->GetDataPresent(DataFormats::FileDrop))
    {
        e->Effect = DragDropEffects::Link;
    }
    else
    {
        e->Effect = DragDropEffects::None;
    }
}

System::Void MainForm::MainForm_DragDrop(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e)
{
    txtDrvPath->Text = cli::safe_cast<Array^>(e->Data->GetData(DataFormats::FileDrop))->GetValue(0)->ToString();
}

System::Void MainForm::btnBrow_Click(System::Object^ sender, System::EventArgs^ e)
{
    openFileDialog->InitialDirectory = "C:\\";
    openFileDialog->Filter = "所有文件|*.*";
    if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        txtDrvPath->Text = openFileDialog->FileName;
    }
}

System::Void MainForm::btnInst_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        txtLog->AppendText("正在安装驱动……\r\n");
        STATUS ret = SrvUtils::Create(drvPath, srvName);
        if (!ret.Success())
        {
            throw ret;
        }
        txtLog->AppendText(String::Format("安装成功。服务名：{0}\r\n", srvName));
    }
    catch (STATUS ret)
    {
        DisplayException(ret);
    }
}

System::Void MainForm::btnStart_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        txtLog->AppendText(String::Format("正在启动服务 {0} ……\r\n", srvName));
        STATUS ret = SrvUtils::Start(srvName);
        if (!ret.Success())
        {
            throw ret;
        }
        txtLog->AppendText(String::Format("服务 {0} 已启动。\r\n", srvName));
    }
    catch (STATUS ret)
    {
        DisplayException(ret);
    }
}

System::Void MainForm::btnStop_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        txtLog->AppendText(String::Format("正在停止服务 {0} ……\r\n", srvName));
        STATUS ret = SrvUtils::Stop(srvName);
        if (!ret.Success())
        {
            throw ret;
        }
        txtLog->AppendText(String::Format("服务 {0} 已停止。\r\n", srvName));
    }
    catch (STATUS ret)
    {
        DisplayException(ret);
    }
}

System::Void MainForm::btnDel_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        txtLog->AppendText(String::Format("正在删除服务 {0} ……\r\n", srvName));
        STATUS ret = SrvUtils::Delete(srvName);
        if (!ret.Success())
        {
            if (ret.exitCode == ERROR_NEED_CONFIRM)
            {
                System::Windows::Forms::DialogResult dialogResult =
                    MessageBox::Show(
                        String::Format("指定的服务({0})似乎不是由本程序创建的。确定要删除吗？", srvName),
                        "提示",
                        MessageBoxButtons::OKCancel,
                        MessageBoxIcon::Question);
                if (dialogResult == System::Windows::Forms::DialogResult::OK)
                {
                    try
                    {
                        STATUS ret = SrvUtils::Delete(srvName, true);
                        if (!ret.Success())
                        {
                            throw ret;
                        }
                        txtLog->AppendText(String::Format("服务 {0} 已删除。\r\n", srvName));
                    }
                    catch (STATUS ret)
                    {
                        DisplayException(ret);
                    }
                }
                else
                {
                    txtLog->AppendText("删除取消。\r\n");
                }
            }
            else
            {
                throw ret;
            }
        }
        txtLog->AppendText(String::Format("服务 {0} 已删除。\r\n", srvName));
    }
    catch (STATUS ret)
    {
        DisplayException(ret);
    }
}

System::Void MainForm::txtSrvName_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
    srvName = txtSrvName->Text;
    btnInst->Enabled = drvPath.Length != 0 && srvName.Length != 0;
    // 我也不知道为什么不可以连续赋值
    // 可能是因为编译器把属性的set当做函数调用
    btnLookup->Enabled = srvName.Length != 0;
    btnStart->Enabled = srvName.Length != 0;
    btnStop->Enabled = srvName.Length != 0;
    btnDel->Enabled = srvName.Length != 0;
}

System::Void MainForm::txtDrvPath_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
    drvPath = txtDrvPath->Text;
    txtSrvName->Text = Path::GetFileNameWithoutExtension(drvPath);
}

System::Void MainForm::btnLookup_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        txtLog->AppendText("正在查询……\r\n");
        STATUS ret = SrvUtils::Lookup(srvName);
        if (!ret.Success())
        {
            throw ret;
        }
        else
        {
            txtLog->AppendText(gcnew String(ret.Msg));
        }
    }
    catch (STATUS ret)
    {
        DisplayException(ret);
    }
}