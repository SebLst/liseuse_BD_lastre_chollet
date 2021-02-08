#include "main.hpp"

IMPLEMENT_APP(CBReaderApp);

bool CBReaderApp::OnInit()
{

    // extract_zip("../res", "test.zip");

    wxInitAllImageHandlers();

    MainFrame *mainFrame = new MainFrame("CBReader");
    mainFrame->Show(true);

    // extract_zip("../res", "test_doc.cbz");

    return true;
}
