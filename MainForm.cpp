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

inline Void MainForm::DisplayException(RSTATUS^ ex)
{
    MessageBox::Show(
        ex,
        TEXT("错误"),
        MessageBoxButtons::OK,
        MessageBoxIcon::Error);
    Log(ex);
}

MainForm::MainForm(array<String^>^ args)
{
    InitializeComponent();

    try
    {
        ThrowIfFailed(SrvUtils::OpenSCM());
    } CatchDisplay(
        delete ret; \
        ret = nullptr; \
        // 防止内存泄露
        System::Environment::Exit(0););

    ActiveControl = txtSrvName;

    Log("欢迎使用DrvLoader");

    if (args->Length > 0)
    {
        txtDrvPath->Text = args[0];
        Log("。\r\n");
    }
    else
    {
        Log("，请选择驱动程序文件/输入服务名。\r\n");
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
    Log("正在结束程序……");
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
        Log("正在安装驱动……\r\n");
        ThrowIfFailed(SrvUtils::Create(drvPath, srvName));
        Log("安装成功。服务名：{0}\r\n", srvName);
    } CatchDisplay();
}

System::Void MainForm::btnStart_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        Log("正在启动服务 {0} ……\r\n", srvName);
        ThrowIfFailed(SrvUtils::Start(srvName));
        Log("服务 {0} 已启动。\r\n", srvName);
    } CatchDisplay();
}

System::Void MainForm::btnStop_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        Log("正在停止服务 {0} ……\r\n", srvName);
        ThrowIfFailed(SrvUtils::Stop(srvName));
        Log("服务 {0} 已停止。\r\n", srvName);
    } CatchDisplay();
}

System::Void MainForm::btnDel_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        Log("正在删除服务 {0} ……\r\n", srvName);
        RSTATUS^ ret = (gcnew RSTATUS(SrvUtils::Delete(srvName)));
        switch (ret->ExitCode)
        {
        case SUCCESS:
            Log("服务 {0} 已删除。\r\n", srvName);
            break;
        case ERROR_NEED_CONFIRM:
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
                    ThrowIfFailed(SrvUtils::Delete(srvName, true));
                    Log("服务 {0} 已删除。\r\n", srvName);
                    break;
                } CatchDisplay();
            }
            else
            {
                Log("删除取消。\r\n");
                break;
            }
        }
        default:
            throw ret;
            break;
        }
        delete ret;
        ret = nullptr;
    } CatchDisplay();
}

System::Void MainForm::txtSrvName_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
    srvName = txtSrvName->Text;
    btnInst->Enabled = drvPath.Length != 0 && srvName.Length != 0;
    // 我也不知道为什么不可以连续赋值
    // 可能是因为编译器把属性的set当做函数调用
    // 而set没有返回值
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
        Log("正在查询……\r\n");
        RSTATUS^ ret = (gcnew RSTATUS(SrvUtils::Lookup(srvName)));
        if (!ret->Success)
        {
            throw ret;
        }
        else
        {
            Log(ret);
            delete ret;
            ret = nullptr;
        }
    } CatchDisplay();
}