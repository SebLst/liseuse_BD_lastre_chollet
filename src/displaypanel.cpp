#include "displaypanel.hpp"

DisplayPanel::DisplayPanel(wxWindow *parent, const wxString &title)
    : wxFrame(parent, -1, title)
{
    wxPanel *panel = new wxPanel(this, -1);

    textctrl = new wxTextCtrl(panel, -1, wxT(""), wxDefaultPosition,
                              wxSize(250, 150), wxTE_MULTILINE);
}