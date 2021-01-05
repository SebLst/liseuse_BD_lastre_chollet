#include "main.hpp"

IMPLEMENT_APP(CBReaderApp);

bool CBReaderApp::OnInit()
{
    wxInitAllImageHandlers();

    MainFrame *mainFrame = new MainFrame("CBReader");
    mainFrame->Show(true);

    return true;
}
