#include "app.h"
#include "mainwindow.h"
#include "id.h"

IMPLEMENT_APP(App); // Main

App::App()
{
}

App::~App()
{
}

bool App::OnInit()
{
    if (!wxApp::OnInit())
    {
        return false;
    }

    MainWindow *main = new MainWindow(NULL, window::id::MAINWINDOW, _("Comic Book Reader"), wxDefaultPosition, wxSize(800, 600));
    main->Show();

    return true;
}

DECLARE_APP(App); // wxGetApp()