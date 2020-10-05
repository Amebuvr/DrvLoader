#include "MainForm.h"
#include "sstream"

using namespace System;
using namespace System::IO;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

using namespace DrvLoaderCLR;

inline Void MainForm::DisplayException(Exception^ ex)
{
    DisplayException(ex, TEXT(""));
}

inline Void MainForm::DisplayException(Exception^ ex, String^ ExMsg)
{
    MessageBox::Show(
        ex->Message,
        TEXT("����"),
        MessageBoxButtons::OK,
        MessageBoxIcon::Error);
    txtLog->AppendText(ex->Message + ExMsg);
}

MainForm::MainForm(array<String^>^ args)
{
    InitializeComponent();

    try
    {
        STATUS ret = SrvUtils::OpenSCM();
        if (!ret.Success)
        {
            THROW(ret);
        }
    }
    catch (Exception^ ex)
    {
        DisplayException(ex);
        System::Environment::Exit(0);
    }

    ActiveControl = txtSrvName;

    txtLog->AppendText("��ӭʹ��DrvLoader");

    if (args->Length > 0)
    {
        txtDrvPath->Text = args[0];
        txtLog->AppendText("��\r\n");
    }
    else
    {
        txtLog->AppendText("����ѡ�����������ļ�/�����������\r\n");
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
    txtLog->AppendText("���ڽ������򡭡�");
    try
    {
        if (chkAutoUnload->Checked)
        {
            SrvUtils::Clear();
        }
    }
    catch (Exception^ ex)
    {
        DisplayException(ex);
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
    openFileDialog->Filter = "�����ļ�|*.*";
    if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        txtDrvPath->Text = openFileDialog->FileName;
    }
}

System::Void MainForm::btnInst_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        txtLog->AppendText("���ڰ�װ��������\r\n");
        STATUS ret = SrvUtils::Create(drvPath, srvName);
        if (!ret.Success)
        {
            THROW(ret);
        }
        txtLog->AppendText(String::Format("��װ�ɹ�����������{0}\r\n", srvName));
    }
    catch (Exception^ ex)
    {
        DisplayException(ex, "��װ��ȡ����\r\n");
    }
}

System::Void MainForm::btnStart_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        txtLog->AppendText(String::Format("������������ {0} ����\r\n", srvName));
        STATUS ret = SrvUtils::Start(srvName);
        if (!ret.Success)
        {
            THROW(ret);
        }
        txtLog->AppendText(String::Format("���� {0} ��������\r\n", srvName));
    }
    catch (Exception^ ex)
    {
        DisplayException(ex);
    }
}

System::Void MainForm::btnStop_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        txtLog->AppendText(String::Format("����ֹͣ���� {0} ����\r\n", srvName));
        STATUS ret = SrvUtils::Stop(srvName);
        if (!ret.Success)
        {
            THROW(ret);
        }
        txtLog->AppendText(String::Format("���� {0} ��ֹͣ��\r\n", srvName));
    }
    catch (Exception^ ex)
    {
        DisplayException(ex);
    }
}

System::Void MainForm::btnDel_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        txtLog->AppendText(String::Format("����ɾ������ {0} ����\r\n", srvName));
        STATUS ret = SrvUtils::Delete(srvName, false);
        if (!ret.Success)
        {
            THROW(ret);
        }
        txtLog->AppendText(String::Format("���� {0} ��ɾ����\r\n", srvName));
    }
    catch (Exception^ ex)
    {
        if (String::Equals(ex->Message, "ɾ��������Ҫȷ�ϡ�"))
        {
            System::Windows::Forms::DialogResult dialogResult =
                MessageBox::Show(
                    String::Format("ָ���ķ���({0})�ƺ������ɱ����򴴽��ġ�ȷ��Ҫɾ����", srvName),
                    "��ʾ",
                    MessageBoxButtons::OKCancel,
                    MessageBoxIcon::Question);
            if (dialogResult == System::Windows::Forms::DialogResult::OK)
            {
                try
                {
                    STATUS ret = SrvUtils::Delete(srvName, true);
                    if (!ret.Success)
                    {
                        THROW(ret);
                    }
                    txtLog->AppendText(String::Format("���� {0} ��ɾ����\r\n", srvName));
                }
                catch (Exception^ exce)
                {
                    DisplayException(exce);
                }
            }
            else
            {
                txtLog->AppendText("ɾ��ȡ����\r\n");
            }
        }
        else
        {
            DisplayException(ex);
        }
    }
}

System::Void MainForm::txtSrvName_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
    srvName = txtSrvName->Text;
    btnInst->Enabled = drvPath.Length != 0 && srvName.Length != 0;
    // ��Ҳ��֪��Ϊʲô������������ֵ
    // ��������Ϊ�����������Ե�set������������
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
        txtLog->AppendText("���ڲ�ѯ����\r\n");
        STATUS ret = SrvUtils::Lookup(srvName);
        if (!ret.Success)
        {
            THROW(ret);
        }
        else
        {
            txtLog->AppendText(gcnew String(ret.Msg));
        }
    }
    catch (Exception^ ex)
    {
        DisplayException(ex);
    }
}