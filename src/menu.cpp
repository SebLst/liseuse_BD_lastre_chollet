#include "menu.hpp"

/*
 * The actual menu of the app
 */
Menu::Menu(const wxString &title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(500, 300))
{
    menuBar = new wxMenuBar;
    /*
     * Here is the layout of the menu:
     * File
     *  - Open... CTRL+O / TODO
     *  - Export as CTRL+E / TODO
     *  - Quit
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
    SetMenuBar(menuBar);

    CreateStatusBar(); // creates a status bar that will display some text when the user hovers the mouse over a menu
    SetStatusText("Welcome to CBReader!");

    // Binding events and methods called
    Bind(wxEVT_MENU, &Menu::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &Menu::OnHelp, this, wxID_HELP);
    Bind(wxEVT_MENU, &Menu::OnOpen, this, wxID_OPEN);
    Centre();
}

/*
 * Closes the app
 */
void Menu::OnExit(wxCommandEvent &WXUNUSED(event))
{
    Close(true);
}

/*
 * Displays some help
*/
void Menu::OnHelp(wxCommandEvent &WXUNUSED(event))
{
    wxMessageBox("This is a great app",
                 "About CBReader", wxOK | wxICON_INFORMATION);
}

/*
 * Open a file selector 
*/
void Menu::OnOpen(wxCommandEvent &WXUNUSED(event))
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