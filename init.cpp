#include "MainForm.h"

namespace DrvLoader
{
    /// <summary>
    /// Ӧ�ó��������ڵ㡣
    /// </summary>
    [STAThread]
    void main(array<String^>^ args)
    {
        Application::EnableVisualStyles();
        Application::SetCompatibleTextRenderingDefault(false);
        Application::Run(gcnew MainForm(args));
    }
}