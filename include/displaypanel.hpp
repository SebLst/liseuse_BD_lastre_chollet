#ifndef DISPLAYPANEL_HPP
#define DISPLAYPANEL_HPP

#include <wx/wx.h>
#include <wx/panel.h>

class DisplayPanel : public wxPanel
{
public:
    DisplayPanel(wxWindow *parent);

    bool loadImage(wxString path, wxBitmapType format);

    wxStaticBitmap *image;
};

#endif