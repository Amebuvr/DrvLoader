#pragma once
#include "SrvUtils.h"
#include "binded_str.h"

// 最大路径长度
#define __MAX_PATH__ 32768L
// 最大服务名长度
#define __MAX_NAME__ 256L

#define ThrowIfFailed(x)                         \
    do{                                          \
        RSTATUS^ CONCAT(__ret_, __LINE__) = (gcnew RSTATUS(x));   \
        if (!CONCAT(__ret_, __LINE__)->Success) \
        {                                        \
            throw CONCAT(__ret_, __LINE__);      \
        }                                        \
    delete CONCAT(__ret_, __LINE__);            \
    CONCAT(__ret_, __LINE__) = nullptr;         \
    }while(0)

#define CatchDisplay(...)  \
  catch (RSTATUS^ ret)     \
  {                        \
    DisplayException(ret); \
    __VA_ARGS__            \
    delete ret;            \
    ret = nullptr;         \
  }                        \
  do                       \
  {                        \
  } while (0) // 保证末尾需要分号

#define __LEFT_BRACKET (
#define __RIGHT_BRACKET )

#define __DEL_COMMA(...) , ##__VA_ARGS__

#define __SELECT_ARG32(                     \
    _0, _1, _2, _3, _4, _5, _6, _7,         \
    _8, _9, _10, _11, _12, _13, _14, _15,   \
    _16, _17, _18, _19, _20, _21, _22, _23, \
    _24, _25, _26, _27, _28, _29, _30, _31, ...) _31

#define __SELECT_FUN(_0, _1, ...)       \
    __SELECT_ARG32 __LEFT_BRACKET       \
        __DEL_COMMA(__VA_ARGS__),       \
        _1, _1, _1, _1, _1, _1, _1, _1, \
        _1, _1, _1, _1, _1, _1, _1, _1, \
        _1, _1, _1, _1, _1, _1, _1, _1, \
        _1, _1, _1, _1, _1, _1, _0,     \
        __RIGHT_BRACKET

#define __LogTo0(x, msg) (x->AppendText(msg))
#define __LogTo1(x, msg, ...) (x->AppendText(System::String::Format(msg, __VA_ARGS__)))
#define Log(msg, ...)                             \
    __SELECT_FUN(__LogTo0, __LogTo1, __VA_ARGS__) \
    (txtLog, msg, __VA_ARGS__)

namespace DrvLoader
{

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public
    ref class RSTATUS
    {
    public:
        RSTATUS(STATUS& source)
        {
            exitCode = source.exitCode;
            msg = gcnew String(source.Msg);
            DebugLog("--------------------------------------------------------------\n");
            DebugLog("RSTATUS constructed by: 0x%p. Loaction: 0x%p\n", &source, this);
            DebugLog("--------------------------------------------------------------\n");
        }
        ~RSTATUS()
        {
            DebugLog("--------------------------------------------------------------\n");
            DebugLog("RSTATUS destructed. Location: 0x%p\n", this);
            DebugLog("--------------------------------------------------------------\n");
            delete msg;
        }
        property bool Success
        {
            bool get()
            {
                return exitCode == SUCCESS;
            }
        }
        property DWORD ExitCode
        {
            DWORD get()
            {
                return exitCode;
            }
        }
        operator String ^ ()
        {
            return msg;
        }
    private:
        DWORD exitCode;
        String^ msg;
    };

    /// <summary>
    /// MainForm 摘要
    /// </summary>
    public
    ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm(array<String^>^ args);

    protected:
        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        ~MainForm();

    private:System::Windows::Forms::Label^ lblDrvPath;
    private:System::Windows::Forms::Button^ btnBrow;
    private:System::Windows::Forms::Button^ btnInst;
    private:System::Windows::Forms::Button^ btnStart;
    private:System::Windows::Forms::Button^ btnStop;
    private:System::Windows::Forms::Button^ btnDel;
    private:System::Windows::Forms::Label^ lblSrvName;
    private:System::Windows::Forms::TextBox^ txtSrvName;
    private:System::Windows::Forms::OpenFileDialog^ openFileDialog;
    private:System::Windows::Forms::TableLayoutPanel^ tlpMain;
    private:System::Windows::Forms::Panel^ pnlDrv;
    private:System::Windows::Forms::TextBox^ txtDrvPath;
    private:System::Windows::Forms::Panel^ pnlSrv;
    private:System::Windows::Forms::Panel^ pnlLog;
    private:System::Windows::Forms::TextBox^ txtLog;
    private:System::Windows::Forms::Button^ btnLookup;
    private:System::Windows::Forms::Panel^ pnlChk;
    private:System::Windows::Forms::CheckBox^ chkAutoUnload;
    private:
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        void InitializeComponent(void)
        {
            System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
            this->lblDrvPath = (gcnew System::Windows::Forms::Label());
            this->btnBrow = (gcnew System::Windows::Forms::Button());
            this->btnInst = (gcnew System::Windows::Forms::Button());
            this->btnStart = (gcnew System::Windows::Forms::Button());
            this->btnStop = (gcnew System::Windows::Forms::Button());
            this->btnDel = (gcnew System::Windows::Forms::Button());
            this->lblSrvName = (gcnew System::Windows::Forms::Label());
            this->txtSrvName = (gcnew System::Windows::Forms::TextBox());
            this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
            this->tlpMain = (gcnew System::Windows::Forms::TableLayoutPanel());
            this->pnlDrv = (gcnew System::Windows::Forms::Panel());
            this->txtDrvPath = (gcnew System::Windows::Forms::TextBox());
            this->pnlSrv = (gcnew System::Windows::Forms::Panel());
            this->btnLookup = (gcnew System::Windows::Forms::Button());
            this->pnlLog = (gcnew System::Windows::Forms::Panel());
            this->txtLog = (gcnew System::Windows::Forms::TextBox());
            this->pnlChk = (gcnew System::Windows::Forms::Panel());
            this->chkAutoUnload = (gcnew System::Windows::Forms::CheckBox());
            this->tlpMain->SuspendLayout();
            this->pnlDrv->SuspendLayout();
            this->pnlSrv->SuspendLayout();
            this->pnlLog->SuspendLayout();
            this->pnlChk->SuspendLayout();
            this->SuspendLayout();
            //
            // lblDrvPath
            //
            this->lblDrvPath->AutoSize = true;
            this->lblDrvPath->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(134)));
            this->lblDrvPath->Location = System::Drawing::Point(13, 8);
            this->lblDrvPath->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->lblDrvPath->Name = L"lblDrvPath";
            this->lblDrvPath->Size = System::Drawing::Size(86, 24);
            this->lblDrvPath->TabIndex = 0;
            this->lblDrvPath->Text = L"驱动文件:";
            //
            // btnBrow
            //
            this->btnBrow->AutoSize = true;
            this->btnBrow->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
            this->btnBrow->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(134)));
            this->btnBrow->Location = System::Drawing::Point(632, 2);
            this->btnBrow->Margin = System::Windows::Forms::Padding(4);
            this->btnBrow->Name = L"btnBrow";
            this->btnBrow->Size = System::Drawing::Size(71, 34);
            this->btnBrow->TabIndex = 2;
            this->btnBrow->Text = L"浏览…";
            this->btnBrow->UseVisualStyleBackColor = true;
            this->btnBrow->Click += gcnew System::EventHandler(this, &MainForm::btnBrow_Click);
            //
            // btnInst
            //
            this->btnInst->AutoSize = true;
            this->btnInst->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
            this->btnInst->Enabled = false;
            this->btnInst->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(134)));
            this->btnInst->Location = System::Drawing::Point(391, 4);
            this->btnInst->Margin = System::Windows::Forms::Padding(4);
            this->btnInst->Name = L"btnInst";
            this->btnInst->Size = System::Drawing::Size(56, 34);
            this->btnInst->TabIndex = 3;
            this->btnInst->Text = L"安装";
            this->btnInst->UseVisualStyleBackColor = true;
            this->btnInst->Click += gcnew System::EventHandler(this, &MainForm::btnInst_Click);
            //
            // btnStart
            //
            this->btnStart->AutoSize = true;
            this->btnStart->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
            this->btnStart->Enabled = false;
            this->btnStart->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(134)));
            this->btnStart->Location = System::Drawing::Point(519, 4);
            this->btnStart->Margin = System::Windows::Forms::Padding(4);
            this->btnStart->Name = L"btnStart";
            this->btnStart->Size = System::Drawing::Size(56, 34);
            this->btnStart->TabIndex = 4;
            this->btnStart->Text = L"启动";
            this->btnStart->UseVisualStyleBackColor = true;
            this->btnStart->Click += gcnew System::EventHandler(this, &MainForm::btnStart_Click);
            //
            // btnStop
            //
            this->btnStop->AutoSize = true;
            this->btnStop->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
            this->btnStop->Enabled = false;
            this->btnStop->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(134)));
            this->btnStop->Location = System::Drawing::Point(583, 4);
            this->btnStop->Margin = System::Windows::Forms::Padding(4);
            this->btnStop->Name = L"btnStop";
            this->btnStop->Size = System::Drawing::Size(56, 34);
            this->btnStop->TabIndex = 5;
            this->btnStop->Text = L"停止";
            this->btnStop->UseVisualStyleBackColor = true;
            this->btnStop->Click += gcnew System::EventHandler(this, &MainForm::btnStop_Click);
            //
            // btnDel
            //
            this->btnDel->AutoSize = true;
            this->btnDel->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
            this->btnDel->Enabled = false;
            this->btnDel->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(134)));
            this->btnDel->Location = System::Drawing::Point(647, 4);
            this->btnDel->Margin = System::Windows::Forms::Padding(4);
            this->btnDel->Name = L"btnDel";
            this->btnDel->Size = System::Drawing::Size(56, 34);
            this->btnDel->TabIndex = 6;
            this->btnDel->Text = L"卸载";
            this->btnDel->UseVisualStyleBackColor = true;
            this->btnDel->Click += gcnew System::EventHandler(this, &MainForm::btnDel_Click);
            //
            // lblSrvName
            //
            this->lblSrvName->AutoSize = true;
            this->lblSrvName->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(134)));
            this->lblSrvName->Location = System::Drawing::Point(35, 10);
            this->lblSrvName->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->lblSrvName->Name = L"lblSrvName";
            this->lblSrvName->Size = System::Drawing::Size(68, 24);
            this->lblSrvName->TabIndex = 7;
            this->lblSrvName->Text = L"服务名:";
            //
            // txtSrvName
            //
            this->txtSrvName->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(134)));
            this->txtSrvName->Location = System::Drawing::Point(112, 6);
            this->txtSrvName->Margin = System::Windows::Forms::Padding(4);
            this->txtSrvName->Name = L"txtSrvName";
            this->txtSrvName->Size = System::Drawing::Size(269, 30);
            this->txtSrvName->TabIndex = 8;
            this->txtSrvName->TextChanged += gcnew System::EventHandler(this, &MainForm::txtSrvName_TextChanged);
            //
            // tlpMain
            //
            this->tlpMain->AutoSize = true;
            this->tlpMain->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
            this->tlpMain->ColumnCount = 1;
            this->tlpMain->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
            this->tlpMain->Controls->Add(this->pnlDrv, 0, 0);
            this->tlpMain->Controls->Add(this->pnlSrv, 0, 1);
            this->tlpMain->Controls->Add(this->pnlLog, 0, 2);
            this->tlpMain->Controls->Add(this->pnlChk, 0, 3);
            this->tlpMain->Dock = System::Windows::Forms::DockStyle::Fill;
            this->tlpMain->Location = System::Drawing::Point(0, 0);
            this->tlpMain->Margin = System::Windows::Forms::Padding(4);
            this->tlpMain->Name = L"tlpMain";
            this->tlpMain->RowCount = 4;
            this->tlpMain->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
            this->tlpMain->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
            this->tlpMain->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
            this->tlpMain->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
            this->tlpMain->Size = System::Drawing::Size(760, 450);
            this->tlpMain->TabIndex = 10;
            //
            // pnlDrv
            //
            this->pnlDrv->AutoSize = true;
            this->pnlDrv->Controls->Add(this->lblDrvPath);
            this->pnlDrv->Controls->Add(this->txtDrvPath);
            this->pnlDrv->Controls->Add(this->btnBrow);
            this->pnlDrv->Location = System::Drawing::Point(4, 4);
            this->pnlDrv->Margin = System::Windows::Forms::Padding(4);
            this->pnlDrv->Name = L"pnlDrv";
            this->pnlDrv->Size = System::Drawing::Size(707, 40);
            this->pnlDrv->TabIndex = 0;
            //
            // txtDrvPath
            //
            this->txtDrvPath->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(134)));
            this->txtDrvPath->Location = System::Drawing::Point(112, 4);
            this->txtDrvPath->Margin = System::Windows::Forms::Padding(4);
            this->txtDrvPath->Name = L"txtDrvPath";
            this->txtDrvPath->ReadOnly = true;
            this->txtDrvPath->Size = System::Drawing::Size(512, 30);
            this->txtDrvPath->TabIndex = 1;
            this->txtDrvPath->TextChanged += gcnew System::EventHandler(this, &MainForm::txtDrvPath_TextChanged);
            //
            // pnlSrv
            //
            this->pnlSrv->AutoSize = true;
            this->pnlSrv->Controls->Add(this->btnLookup);
            this->pnlSrv->Controls->Add(this->lblSrvName);
            this->pnlSrv->Controls->Add(this->txtSrvName);
            this->pnlSrv->Controls->Add(this->btnDel);
            this->pnlSrv->Controls->Add(this->btnInst);
            this->pnlSrv->Controls->Add(this->btnStop);
            this->pnlSrv->Controls->Add(this->btnStart);
            this->pnlSrv->Location = System::Drawing::Point(4, 52);
            this->pnlSrv->Margin = System::Windows::Forms::Padding(4);
            this->pnlSrv->Name = L"pnlSrv";
            this->pnlSrv->Size = System::Drawing::Size(707, 42);
            this->pnlSrv->TabIndex = 1;
            //
            // btnLookup
            //
            this->btnLookup->AutoSize = true;
            this->btnLookup->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
            this->btnLookup->Enabled = false;
            this->btnLookup->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(134)));
            this->btnLookup->Location = System::Drawing::Point(455, 4);
            this->btnLookup->Margin = System::Windows::Forms::Padding(4);
            this->btnLookup->Name = L"btnLookup";
            this->btnLookup->Size = System::Drawing::Size(56, 34);
            this->btnLookup->TabIndex = 9;
            this->btnLookup->Text = L"查询";
            this->btnLookup->UseVisualStyleBackColor = true;
            this->btnLookup->Click += gcnew System::EventHandler(this, &MainForm::btnLookup_Click);
            //
            // pnlLog
            //
            this->pnlLog->AutoSize = true;
            this->pnlLog->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
            this->pnlLog->Controls->Add(this->txtLog);
            this->pnlLog->Location = System::Drawing::Point(4, 102);
            this->pnlLog->Margin = System::Windows::Forms::Padding(4);
            this->pnlLog->Name = L"pnlLog";
            this->pnlLog->Size = System::Drawing::Size(707, 276);
            this->pnlLog->TabIndex = 2;
            //
            // txtLog
            //
            this->txtLog->AcceptsReturn = true;
            this->txtLog->AcceptsTab = true;
            this->txtLog->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(134)));
            this->txtLog->Location = System::Drawing::Point(4, 4);
            this->txtLog->Margin = System::Windows::Forms::Padding(4);
            this->txtLog->Multiline = true;
            this->txtLog->Name = L"txtLog";
            this->txtLog->ReadOnly = true;
            this->txtLog->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
            this->txtLog->Size = System::Drawing::Size(699, 268);
            this->txtLog->TabIndex = 9;
            //
            // pnlChk
            //
            this->pnlChk->AutoSize = true;
            this->pnlChk->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
            this->pnlChk->Controls->Add(this->chkAutoUnload);
            this->pnlChk->Location = System::Drawing::Point(3, 385);
            this->pnlChk->Name = L"pnlChk";
            this->pnlChk->Size = System::Drawing::Size(274, 35);
            this->pnlChk->TabIndex = 3;
            //
            // chkAutoUnload
            //
            this->chkAutoUnload->AutoSize = true;
            this->chkAutoUnload->Checked = true;
            this->chkAutoUnload->CheckState = System::Windows::Forms::CheckState::Checked;
            this->chkAutoUnload->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei UI", 10.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(134)));
            this->chkAutoUnload->Location = System::Drawing::Point(9, 3);
            this->chkAutoUnload->Name = L"chkAutoUnload";
            this->chkAutoUnload->Size = System::Drawing::Size(262, 29);
            this->chkAutoUnload->TabIndex = 5;
            this->chkAutoUnload->Text = L"退出时自动卸载安装的驱动";
            this->chkAutoUnload->UseVisualStyleBackColor = true;
            //
            // MainForm
            //
            this->AcceptButton = this->btnLookup;
            this->AllowDrop = true;
            this->AutoScaleDimensions = System::Drawing::SizeF(120, 120);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
            this->AutoSize = true;
            this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
            this->ClientSize = System::Drawing::Size(760, 450);
            this->Controls->Add(this->tlpMain);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
            this->Margin = System::Windows::Forms::Padding(4);
            this->MaximizeBox = false;
            this->Name = L"MainForm";
            this->Text = L"DrvLoader";
            this->TopMost = true;
            this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
            this->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::MainForm_DragDrop);
            this->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::MainForm_DragEnter);
            this->tlpMain->ResumeLayout(false);
            this->tlpMain->PerformLayout();
            this->pnlDrv->ResumeLayout(false);
            this->pnlDrv->PerformLayout();
            this->pnlSrv->ResumeLayout(false);
            this->pnlSrv->PerformLayout();
            this->pnlLog->ResumeLayout(false);
            this->pnlLog->PerformLayout();
            this->pnlChk->ResumeLayout(false);
            this->pnlChk->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private:binded_str drvPath;
    private:binded_str srvName;

    private:System::Void DisplayException(RSTATUS^ ex);

    private:System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
    private:System::Void MainForm_DragDrop(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e);
    private:System::Void MainForm_DragEnter(System::Object^ sender, System::Windows::Forms::DragEventArgs^ e);
    private:System::Void btnBrow_Click(System::Object^ sender, System::EventArgs^ e);
    private:System::Void btnInst_Click(System::Object^ sender, System::EventArgs^ e);
    private:System::Void btnStart_Click(System::Object^ sender, System::EventArgs^ e);
    private:System::Void btnStop_Click(System::Object^ sender, System::EventArgs^ e);
    private:System::Void btnDel_Click(System::Object^ sender, System::EventArgs^ e);
    private:System::Void txtSrvName_TextChanged(System::Object^ sender, System::EventArgs^ e);
    private:System::Void txtDrvPath_TextChanged(System::Object^ sender, System::EventArgs^ e);
    private:System::Void btnLookup_Click(System::Object^ sender, System::EventArgs^ e);
    };
} // namespace DrvLoader
