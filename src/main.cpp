#include "main.hpp"


IMPLEMENT_APP(CBReaderApp);

bool CBReaderApp::OnInit()
{
	extract_zip("../res", "test_doc.cbz");
    MainFrame *mainFrame = new MainFrame("CBReader");
    mainFrame->Show();

    return true;
}
