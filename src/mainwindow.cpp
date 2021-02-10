#include "mainwindow.h"
#include "toolbar.h"
#include "menu.h"
#include "id.h"
#include <wx/filedlg.h>
#include <wx/wfstream.h>

BEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_MENU(wxID_OPEN, MainWindow::OnOpen)
EVT_MENU(wxID_HELP, MainWindow::OnHelp)
EVT_MENU(wxID_EXIT, MainWindow::OnQuit)
EVT_MENU(wxID_ZOOM_IN, MainWindow::OnZoomIn)
EVT_MENU(wxID_ZOOM_OUT, MainWindow::OnZoomOut)
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
    // menu bar
    wxMenuBar *menuBar = new wxMenuBar();
    makeMenuBar(menuBar);
    SetMenuBar(menuBar);

    // toolbar
    wxToolBar *toolBar = CreateToolBar();
    makeToolBar(toolBar);
    toolBar->Realize();

    // main display
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    imagePanel = new ImagePanel(this);
    sizer->Add(imagePanel, 1, wxEXPAND);

    // status bar
    CreateStatusBar();
    SetStatusText(_("Welcome to CBReader!"));

    SetSizer(sizer);

    // dynamic binding
    Bind(wxEVT_CLOSE_WINDOW, &OnClose);

    // other
    SetMinSize(wxSize(300, 300));
}

void MainWindow::OnOpen(wxCommandEvent &WXUNUSED(event))
{
    wxFileDialog openFileDialog(this, _("Open Image file"), "", "",
                                "All image files (*.jpeg;*.png;*.bmp;*.jpg)|*.jpeg;*.png;*.bmp;*.jpg",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed idea...

    // proceed loading the file chosen by the user
    wxString path = openFileDialog.GetPath();
    wxFileInputStream input_stream(path);
    if (!input_stream.IsOk())
    {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
        return;
    }

    imagePanel->loadImage(path, wxBITMAP_TYPE_ANY);
    Refresh();
}

void MainWindow::OnZoomIn(wxCommandEvent &WXUNUSED(event))
{
    imagePanel->zoomIn();
    Refresh();
}

void MainWindow::OnZoomOut(wxCommandEvent &WXUNUSED(event))
{
    imagePanel->zoomOut();
    Refresh();
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