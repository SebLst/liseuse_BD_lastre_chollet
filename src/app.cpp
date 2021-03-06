#include "app.h"
#include "mainwindow.h"
#include "id.h"
#include "extract.cpp"

IMPLEMENT_APP(App); // Main

App::App()
{
}

App::~App()
{
}

/**
 * Method called when the app is executed
*/
bool App::OnInit()
{
    if (!wxApp::OnInit())
    {
        return false;
    }
	
	
    wxInitAllImageHandlers(); // allows the manipulation of all supported image file extensions by wxWigets

    /*MainWindow *main = new MainWindow(NULL,
                                      window::id::MAINWINDOW,
                                      _("Comic Book Reader"),
                                      wxDefaultPosition,
                                      wxSize(800, 600));
    main->Show();*/

    return true;
}

DECLARE_APP(App); // wxGetApp()
