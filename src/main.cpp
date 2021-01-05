#include "main.hpp"

IMPLEMENT_APP(CBReaderApp);

bool CBReaderApp::OnInit()
{
    MainFrame *mainFrame = new MainFrame("CBReader");
    mainFrame->Show();

    return true;
}
