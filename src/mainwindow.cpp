#include "mainwindow.h"
#include "toolbar.h"
#include "menu.h"
#include "id.h"
#include "shortcuts.h"
#include "param.h"
#include "cbarchive.h"

#include <wx/filedlg.h>
#include <wx/wfstream.h>
#include <wx/accel.h>
#include <sstream>

#include "./../res/icons/cbreader_icon.xpm"

// static event binding
BEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_MENU(window::id::OPEN_FILE, MainWindow::OnOpenFile)
EVT_MENU(window::id::OPEN_DIRECTORY, MainWindow::OnOpenDir)
EVT_MENU(window::id::OPEN_ARCHIVE, MainWindow::OnOpenArchive)
EVT_MENU(wxID_HELP, MainWindow::OnHelp)
EVT_MENU(wxID_EXIT, MainWindow::OnQuit)
EVT_MENU(wxID_ZOOM_IN, MainWindow::OnZoomIn)
EVT_MENU(wxID_ZOOM_OUT, MainWindow::OnZoomOut)
EVT_MENU(window::id::PREVIOUS_PAGE, MainWindow::OnArrowLeft)
EVT_MENU(window::id::NEXT_PAGE, MainWindow::OnArrowRight)
EVT_MENU(window::id::FIRST_PAGE, MainWindow::OnFirstPage)
EVT_MENU(window::id::LAST_PAGE, MainWindow::OnLastPage)
EVT_MENU(window::id::HIDE_BOOKMARK_PANEL, MainWindow::OnShowBookmarks)
EVT_MENU(window::id::EXPORT_CBZ, MainWindow::OnExportCbz)
EVT_IDLE(MainWindow::OnIdle)
END_EVENT_TABLE()



void OnClose(wxCloseEvent &event);

/**
 * Constructor of the MainWindow class
 * @param parent Parent frame
 * @param id Window ID
 * @param title Text displayed on the window's title bar
 * @param pos The window position
 * @param size The window size
 * @param style The window style (see wxFrame class for more description)
 * @param name The name of the window, used to associate the name with the item
*/
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

    // main sizer
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    // bookmark panel
    bookmarkPanel = new BookmarkPanel(this);
    sizer->Add(bookmarkPanel, 1, wxEXPAND);
    bookmarkPanel->Hide(); // hidden by default

    // main display
    imagePanel = new ImagePanel(this);
    sizer->Add(imagePanel, 1, wxEXPAND);

    // status bar
    int STATUS_BAR_SIZE = 2;
    CreateStatusBar(STATUS_BAR_SIZE);
    SetStatusText(_("Welcome to CBReader!"));
    SetStatusText(_("Open a file or document to read!"), 1);
    statusBar = GetStatusBar();

    SetSizer(sizer);

    // dynamic binding of events
    Bind(wxEVT_CLOSE_WINDOW, &OnClose);

    // other
    SetMinSize(wxSize(param::WINDOW_MIN_SIZE_X, param::WINDOW_MIN_SIZE_Y));
    wxIcon *appIcon = new wxIcon(cbreader_icon); // image from https://www.freepik.com
    SetIcon(*appIcon);
}

/**
 * Opens a file dialog to open an image
*/
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

    imagePanel->resetScale();
    imagePanel->loadImage(filePath, wxBITMAP_TYPE_ANY);
    imagePanel->makeImageFitPanel();
    imagePanel->setMode(window::modes::FILE);
    SetStatusText(openFileDialog.GetFilename(), 1);
    Refresh();
}

/**
 * Opens a directory dialog to open a directory containing image files
*/
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

    imagePanel->resetScale();
    imagePanel->loadImage(files[0], wxBITMAP_TYPE_ANY);
    imagePanel->makeImageFitPanel();
    imagePanel->setMode(window::modes::FOLDER);
    SetStatusText(_("Page 1 / " + std::to_string(pageTotal)), 1);
    Refresh();

    bookmarkPanel->setCurrentPage(pageCurrent);
}

/**
 * Opens a file dialog to open an archive 
*/
void MainWindow::OnOpenArchive(wxCommandEvent &WXUNUSED(event))
{
    wxFileDialog openFileDialog(this, _("Open CBZ or CBR file"), "", "",
                                "CBZ or CBR files (*.cbz;*.cbr)|*.cbz;*cbr",
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

    wxString dirPath = openFileDialog.GetDirectory();
    const char *destination = dirPath.Append(_("/")).Append("extracted/");
    CBArchive cbz(filePath);
    pageCurrent = 0;
    pageTotal = cbz.extractNumberPages();
    files.clear();

    // the first page of the archive is extracted first and opened
    wxString firstImagePath;
    if (cbz.extract(destination, 1, &firstImagePath) != 0)
        return;

    imagePanel->resetScale();
    imagePanel->loadImage(firstImagePath, wxBITMAP_TYPE_ANY);
    imagePanel->makeImageFitPanel();
    imagePanel->setMode(window::modes::FOLDER);

    SetStatusText(_("Page 1 / " + std::to_string(pageTotal)), 1);
    Refresh();

    bookmarkPanel->setCurrentPage(pageCurrent);

    // extraction of the rest of the archive
    files = cbz.extractAll(destination);
}

/**
 * Zooms in and refreshes the window
*/
void MainWindow::OnZoomIn(wxCommandEvent &WXUNUSED(event))
{
    imagePanel->zoomIn();
    Refresh();
}

/**
 * Zooms out and refreshes the window
*/
void MainWindow::OnZoomOut(wxCommandEvent &WXUNUSED(event))
{
    imagePanel->zoomOut();
    Refresh();
}

/**
 * Opens the previous page when the left arrow key is pressed
*/
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
        SetStatusText(_("Page " + std::to_string(pageCurrent + 1) + " / " + std::to_string(pageTotal)), 1);
        Refresh();
    }

    bookmarkPanel->setCurrentPage(pageCurrent);
}

/**
 * Opens the next page when the right arrow key is pressed
*/
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
        SetStatusText(_("Page " + std::to_string(pageCurrent + 1) + " / " + std::to_string(pageTotal)), 1);
        Refresh();
    }

    bookmarkPanel->setCurrentPage(pageCurrent);
}

/**
 * Opens the first page
*/
void MainWindow::OnFirstPage(wxCommandEvent &WXUNUSED(event))
{
    if (files.size() == 0)
    {
        return;
    }

    pageCurrent = 0;
    imagePanel->loadImage(files[pageCurrent], wxBITMAP_TYPE_ANY);
    SetStatusText(_("Page " + std::to_string(pageCurrent + 1) + " / " + std::to_string(pageTotal)), 1);
    Refresh();

    bookmarkPanel->setCurrentPage(pageCurrent);
}

/**
 * Opens the last page
*/
void MainWindow::OnLastPage(wxCommandEvent &WXUNUSED(event))
{
    if (files.size() == 0)
    {
        return;
    }

    pageCurrent = pageTotal - 1;
    imagePanel->loadImage(files[pageCurrent], wxBITMAP_TYPE_ANY);
    SetStatusText(_("Page " + std::to_string(pageCurrent + 1) + " / " + std::to_string(pageTotal)), 1);
    Refresh();

    bookmarkPanel->setCurrentPage(pageCurrent);
}

/**
 * Opens the help message box
*/
void MainWindow::OnHelp(wxCommandEvent &WXUNUSED(event))
{
    wxMessageBox("If you don't understand what a button does, you should have an indication of what it does in the bottom bar !");
}

/**
 * Calls the Close fonction
*/
void MainWindow::OnQuit(wxCommandEvent &WXUNUSED(event))
{
    Close();
}

/**
 * Called when the app is doing nothing
*/
void MainWindow::OnIdle(wxIdleEvent &WXUNUSED(event))
{
}

/**
 * Opens the close event, which lets the user choose to close the app
*/
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
    event.Skip(); // the event will be handled by the default event handler of wxWidgets (destroys the window)
}

/**
 * Opens or collapses the bookmarks panel
*/
void MainWindow::OnShowBookmarks(wxCommandEvent &WXUNUSED(event))
{
    if (bookmarkPanel->IsShown())
    {
        bookmarkPanel->Hide();
    }
    else
    {
        bookmarkPanel->Show();
    }
    SendSizeEvent(); // trick to update the window (a size event refreshes the entire window)
}

void MainWindow::OnExportCbz (wxCommandEvent &WXUNUSED(&event))
{
    wxFileDialog openFileDialog(this, _("Choose input CBZ or CBR file"), "", "",
                                "CBZ or CBR files (*.cbz;*.cbr)|*.cbz;*cbr",
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

    CBArchive cbz(filePath);

    wxDirDialog openDirDialog(this, "Choose output folder", "",
                                wxDD_DEFAULT_STYLE| wxDD_DIR_MUST_EXIST);

    if (openDirDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed his mind
    
    wxString destination = openDirDialog.GetPath();
    wxString pagesStr = wxGetTextFromUser("Enter the pages to extract as \"1,2,5,15,23\"");
    
    int i=0;
    std::string page = "";
    int nombrePages = 0;
    int maxPages = cbz.extractNumberPages();
    int pages[maxPages];
    int p;
    while(pagesStr[i] != '\0')
    {
        if (pagesStr[i] == ',')
        {
            std::stringstream ss(page.c_str());
            if (!(ss>>p))
            {
                wxLogError("Incorrect format for the pages to extract");
                return;
            }
            pages[nombrePages] =p;
            page = "";
            nombrePages++;
            i++;
        }
        else 
        {
            page += pagesStr[i];
            i++;
        }
    }
    std::stringstream ss(page);
    if (!(ss>>p))
    {
        wxLogError("Incorrect format for the pages to extract");
        return;
    }
    pages[nombrePages] =p;
    nombrePages++;

    const char *archivePath = destination.Append(_("/")).Append("archive.cbz");
    if (cbz.extractPages(archivePath, pages, nombrePages,destination)) 
    {
        wxLogError("Cannot extract the given pages");
        return;
    }
}


MainWindow::~MainWindow()
{
}