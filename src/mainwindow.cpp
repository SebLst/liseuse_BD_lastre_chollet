#include "mainwindow.h"
#include "toolbar.h"
#include "menu.h"
#include "id.h"
#include "shortcuts.h"
#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/accel.h>

#include "./../res/icons/cbreader_icon.xpm"

// static event binding
BEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_MENU(window::id::OPEN_FILE, MainWindow::OnOpenFile)
EVT_MENU(window::id::OPEN_DIRECTORY, MainWindow::OnOpenDir)
EVT_MENU(wxID_HELP, MainWindow::OnHelp)
EVT_MENU(wxID_EXIT, MainWindow::OnQuit)
EVT_MENU(wxID_ZOOM_IN, MainWindow::OnZoomIn)
EVT_MENU(wxID_ZOOM_OUT, MainWindow::OnZoomOut)
EVT_MENU(window::id::PREVIOUS_PAGE, MainWindow::OnArrowLeft)
EVT_MENU(window::id::NEXT_PAGE, MainWindow::OnArrowRight)
EVT_MENU(window::id::FIRST_PAGE, MainWindow::OnFirstPage)
EVT_MENU(window::id::LAST_PAGE, MainWindow::OnLastPage)
EVT_IDLE(MainWindow::OnIdle)
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
    wxAcceleratorTable *accel = GetAcceleratorTable();
    addShortcuts(accel);

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

    // dynamic binding of events
    Bind(wxEVT_CLOSE_WINDOW, &OnClose);

    // other
    SetMinSize(wxSize(300, 300));
    wxIcon *appIcon = new wxIcon(cbreader_icon); // image from https://www.freepik.com
    SetIcon(*appIcon);
}

void MainWindow::OnOpenFile(wxCommandEvent &WXUNUSED(event))
{
    wxFileDialog openFileDialog(this, _("Open Image file"), "", "",
                                "All image files (*.jpeg;*.png;*.bmp;*.jpg)|*.jpeg;*.png;*.bmp;*.jpg",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed his mind

    // proceed loading the file chosen by the user
    wxString filePath = openFileDialog.GetPath();
    wxFileInputStream input_stream(filePath);
    if (!input_stream.IsOk())
    {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
        return;
    }

    imagePanel->loadImage(filePath, wxBITMAP_TYPE_ANY);
    Refresh();
}

void MainWindow::OnOpenDir(wxCommandEvent &WXUNUSED(event))
{
    wxDirDialog openDirDialog(this, _("Choose directory"), cwd,
                              wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

    if (openDirDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed his mind

    cwd = openDirDialog.GetPath();
    dir = new wxDir(cwd);
    if (!dir->IsOpened())
    {
        wxLogError(_("Cannot open folder '%s'."), dir->GetName());
        return;
    }

    if (!dir->HasFiles())
    {
        return;
    }

    files.clear();
    // not very pretty, but you have to enumerate all the file types one by one
    wxDir::GetAllFiles(cwd, &files, _("*.jpeg"));
    wxDir::GetAllFiles(cwd, &files, _("*.png"));
    wxDir::GetAllFiles(cwd, &files, _("*.bmp"));
    wxDir::GetAllFiles(cwd, &files, _("*.jpg"));
    if (files.size() == 0)
        return;
    files.Sort(); // by default files are added randomly

    pageCurrent = 0;
    pageTotal = files.size();

    imagePanel->loadImage(files[0], wxBITMAP_TYPE_ANY);
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

void MainWindow::OnArrowLeft(wxCommandEvent &WXUNUSED(event))
{
    if (files.size() == 0) // if there are no files
    {
        return;
    }

    if (pageCurrent > 0)
    {
        pageCurrent--;
        imagePanel->loadImage(files[pageCurrent], wxBITMAP_TYPE_ANY);
        Refresh();
    }
}

void MainWindow::OnArrowRight(wxCommandEvent &WXUNUSED(event))
{
    if (files.size() == 0) // if there are no files
    {
        return;
    }

    if (pageCurrent < pageTotal - 1)
    {
        pageCurrent++;
        imagePanel->loadImage(files[pageCurrent], wxBITMAP_TYPE_ANY);
        Refresh();
    }
}

void MainWindow::OnFirstPage(wxCommandEvent &WXUNUSED(event))
{
    if (files.size() == 0)
    {
        return;
    }

    pageCurrent = 0;
    imagePanel->loadImage(files[pageCurrent], wxBITMAP_TYPE_ANY);
    Refresh();
}

void MainWindow::OnLastPage(wxCommandEvent &WXUNUSED(event))
{
    if (files.size() == 0)
    {
        return;
    }

    pageCurrent = pageTotal - 1;
    imagePanel->loadImage(files[pageCurrent], wxBITMAP_TYPE_ANY);
    Refresh();
}

void MainWindow::OnHelp(wxCommandEvent &WXUNUSED(event))
{
    wxMessageBox("If you don't understand what a button does, you should have an indication of what it does in the bottom bar !");
}

void MainWindow::OnQuit(wxCommandEvent &WXUNUSED(event))
{
    Close();
}

void MainWindow::OnIdle(wxIdleEvent &WXUNUSED(event))
{
}

void OnClose(wxCloseEvent &event)
{
    if (event.CanVeto())
    {
        // the following makes a message box popup and gives the opportunity to cancel the close event (in case of a missclick or alt+F4)
        int answer = wxMessageBox(_("Do you want to leave?"), _("Confirm?"), wxYES_NO);
        if (answer != wxYES)
        {
            event.Veto();
            return;
        }
    }
    event.Skip(); // the event wiil be handled by the default event handler of wxWidgets (destroys the window)
}

MainWindow::~MainWindow()
{
}