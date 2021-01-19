#include "main.hpp"


IMPLEMENT_APP(CBReaderApp);

bool CBReaderApp::OnInit()
{
	extract_zip("../res", "test.zip");
    MainFrame *mainFrame = new MainFrame("CBReader");
    mainFrame->Show();

    return true;
}
