#include "mainwindow.h"
#include <wx/artprov.h>

#include <icons/zoom-in.xpm>
#include <icons/zoom-out.xpm>

BEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_MENU(wxID_OPEN, MainWindow::OnOpen)
EVT_MENU(wxID_HELP, MainWindow::OnHelp)
EVT_MENU(wxID_EXIT, MainWindow::OnQuit)
END_EVENT_TABLE()

void OnClose(wxCloseEvent &event);

MainWindow::MainWindow(wxWindow *parent,
                       wxWindowID id,
                       const wxString &title,
                       const wxPoint &pos,
                       const wxSize &size,
                       long style,
                       const wxString &name)
    : wxFrame(parent, id, title, pos, size, style, name)
{
    wxMenuBar *menuBar = new wxMenuBar();
    // file menu
    wxMenu *fileMenu = new wxMenu();
    menuBar->Append(fileMenu, _("&File"));

    // new menu item
    wxMenuItem *openItem = new wxMenuItem(fileMenu, wxID_OPEN);
    openItem->SetBitmap(wxArtProvider::GetBitmap(wxART_FILE_OPEN)); // créé une icone pour le menu, apparement ne fonctionne pas sur linux
    fileMenu->Append(openItem);

    // help menu item
    wxMenuItem *helpItem = new wxMenuItem(fileMenu, wxID_HELP, _("Help"), _("Need some help?"));
    helpItem->SetBitmap(wxArtProvider::GetBitmap(wxART_HELP));
    fileMenu->Append(helpItem);

    fileMenu->AppendSeparator();
    // sous menu "Exporter..."
    wxMenu *exportMenu = new wxMenu();
    // zip menu item
    wxMenuItem *zipItem = exportMenu->Append(wxID_ANY, _("&ZIP"), _("Export as a .cbz file"));
    // rar menu item
    wxMenuItem *rarItem = exportMenu->Append(wxID_ANY, _("&RAR"), _("Export as a .cbr file"));
    fileMenu->AppendSubMenu(exportMenu, _("&Export as"), _("Export your collection of images as..."));

    fileMenu->AppendSeparator();
    // quit menu item
    wxMenuItem *quitItem = new wxMenuItem(fileMenu, wxID_EXIT);
    quitItem->SetBitmap(wxArtProvider::GetBitmap(wxART_QUIT));
    fileMenu->Append(quitItem);

    SetMenuBar(menuBar);

    // dynamic binding
    Bind(wxEVT_CLOSE_WINDOW, &OnClose);

    // toolbar
    wxToolBar *toolBar = CreateToolBar();

    // open file tool
    toolBar->AddTool(wxID_OPEN, _("Open"), wxArtProvider::GetBitmap(wxART_FILE_OPEN));
    toolBar->SetToolShortHelp(wxID_OPEN, _("Open document"));            // display some text when the mouse hovers the tool for a few seconds
    toolBar->SetToolLongHelp(wxID_OPEN, _("Open an existing document")); // display text in the status bar

    toolBar->AddSeparator();
    // zoom tools
    wxBitmap zoomIn(zoom_in);
    wxBitmap zoomOut(zoom_out);
    toolBar->AddTool(wxID_ZOOM_IN, _("Zoom in"), zoomIn);
    toolBar->SetToolShortHelp(wxID_ZOOM_IN, _("Zoom in"));
    toolBar->SetToolLongHelp(wxID_ZOOM_IN, _("Zoom in"));
    toolBar->AddTool(wxID_ZOOM_OUT, _("Zoom out"), zoomOut);
    toolBar->SetToolShortHelp(wxID_ZOOM_OUT, _("Zoom out"));
    toolBar->SetToolLongHelp(wxID_ZOOM_OUT, _("Zoom out"));

    toolBar->AddStretchableSpace();
    // help tool
    toolBar->AddTool(wxID_HELP, _("Help"), wxArtProvider::GetBitmap(wxART_HELP));
    toolBar->SetToolShortHelp(wxID_HELP, _("Help"));
    toolBar->SetToolLongHelp(wxID_HELP, _("Click here to get some help!"));

    toolBar->Realize();

    // status bar
    CreateStatusBar();
    SetStatusText(_("Welcome to CBReader!"));
}

void MainWindow::OnOpen(wxCommandEvent &WXUNUSED(event))
{
    wxMessageBox(_("OnOpen Event"));
}

void MainWindow::OnHelp(wxCommandEvent &WXUNUSED(event))
{
    wxMessageBox("Do you really need help?...");
}

void MainWindow::OnQuit(wxCommandEvent &WXUNUSED(event))
{
    Close();
}

void OnClose(wxCloseEvent &event)
{
    if (event.CanVeto())
    {
        int answer = wxMessageBox(_("Do you want to leave?"), _("Confirm?"), wxYES_NO);
        if (answer != wxYES)
        {
            event.Veto();
            return;
        }
    }
    event.Skip(); // l'événement sera traité par le handler de base de wxWidgets, qui détruit la fenêtre
}

MainWindow::~MainWindow()
{
}