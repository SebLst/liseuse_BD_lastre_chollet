#ifndef DISPLAYPANEL_HPP
#define DISPLAYPANEL_HPP

#include <wx/wx.h>

class DisplayPanel : public wxFrame
{
public:
    DisplayPanel(wxWindow *parent, const wxString &title);

    wxTextCtrl *textctrl;
};

#endif