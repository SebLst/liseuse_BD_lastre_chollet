#ifndef MENU_HPP
#define MENU_HPP

#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>

class Menu : public wxFrame
{
public:
    Menu(const wxString &title);

    void OnExit(wxCommandEvent &event);
    void OnHelp(wxCommandEvent &event);
    void OnOpen(wxCommandEvent &event);

    wxMenuBar *menuBar;
    wxMenu *menuFile;
    wxMenu *menuHelp;
};

#endif