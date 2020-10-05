#include "MainForm.h"

namespace DrvLoaderCLR
{
    /// <summary>
    /// 应用程序的主入口点。
    /// </summary>
    [STAThread]
    void main(array<String^>^ args)
    {
        Application::EnableVisualStyles();
        Application::SetCompatibleTextRenderingDefault(false);
        Application::Run(gcnew MainForm(args));
    }
}