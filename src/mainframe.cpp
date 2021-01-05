#include "mainframe.hpp"

MainFrame::MainFrame(const wxString &title)
    : wxFrame(NULL, -1, title, wxDefaultPosition, wxSize(800, 600))
{
    ///////////////////////////////////////////////////////////////////

    // Setting the menu
    menuBar = new wxMenuBar;
    /*
     * Here is the layout of the menu:
     * File
     *  - Open... CTRL+O / TODO
     *  - Export as CTRL+E / TODO
     *  - Quit
     * Bookmarks / TODO (pas tout de suite)
     *  - Open Bookmarks
     *  - Set Bookmark
     * Help
     *  - About
     */
    menuFile = new wxMenu;
    menuHelp = new wxMenu;

    // File Menu
    menuFile->Append(wxID_OPEN, "&Open",
                     "Open an image or a book!");
    menuFile->Append(wxID_EXIT, "&Quit",
                     "Close CBReader"); // the third argument updates the Status Bar text (see below)

    // Help Menu
    menuHelp->Append(wxID_HELP, "&About",
                     "Give you more information about CBReader");

    // Append to Menu Bar
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    // Binding events and methods called
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainFrame::OnHelp, this, wxID_HELP);
    Bind(wxEVT_MENU, &MainFrame::OnOpen, this, wxID_OPEN);

    SetMenuBar(menuBar);

    ///////////////////////////////////////////////////////////////////

    display = new DisplayPanel(this);

    CreateStatusBar();
    SetStatusText("Welcome to CBReader!");

    ///////////////////////////////////////////////////////////////////

    SetMinSize(wxSize(500, 500)); // sets a minimum size to the window
    Centre();                     // puts the window in the center of the screen
}

/*
 * Close the app
 */
void MainFrame::OnExit(wxCommandEvent &WXUNUSED(event))
{
    Close(true);
}

/*
 * Display some help
*/
void MainFrame::OnHelp(wxCommandEvent &WXUNUSED(event))
{
    wxMessageBox("This is a great app",
                 "About CBReader", wxOK | wxICON_INFORMATION);
}

/*
 * Open a file selector 
*/
void MainFrame::OnOpen(wxCommandEvent &WXUNUSED(event))
{
    wxFileDialog openFileDialog(this, _("Open Image file"), "", "",
                                "All image files (*.jpeg;*.png;*.bmp)|*.jpeg;*.png;*.bmp",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed idea...

    // proceed loading the file chosen by the user
    wxFileInputStream input_stream(openFileDialog.GetPath());
    if (!input_stream.IsOk())
    {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
        return;
    }
}