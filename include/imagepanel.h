#ifndef IMAGE_PANEL_H
#define IMAGE_PANEL_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class ImagePanel : public wxPanel
{
private:
    wxBitmap image;
    bool imageExists = false;
    int drawXPos = 0;
    int drawYPos = 0;
    double scale = 1;

public:
    ImagePanel(wxFrame *parent);
    ~ImagePanel();

    void paintEvent(wxPaintEvent &evt);
    void paintNow();
    void loadImage(wxString file, wxBitmapType format);
    void render(wxDC &dc);

    void setScale(double scale);
    void zoomIn();
    void zoomOut();

    DECLARE_EVENT_TABLE()
};

#endif