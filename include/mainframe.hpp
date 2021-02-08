/*
#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/filedlg.h>
#include <wx/wfstream.h>

#include "displaypanel.hpp"

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title);

    // button handlers
    void OnExit(wxCommandEvent &event);
    void OnHelp(wxCommandEvent &event);
    void OnOpen(wxCommandEvent &event);

    wxMenuBar *menuBar; // menu bar
    wxMenu *menuFile;   // "File" button
    wxMenu *menuHelp;   // "Help" button

    DisplayPanel *display; // main frame
};

#endif
*/