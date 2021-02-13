#ifndef IMAGE_PANEL_H
#define IMAGE_PANEL_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class ImagePanel : public wxPanel
{
private:
    wxBitmap baseImage;       // the base image
    wxBitmap displayImage;    // this one will be scaled for zooming
    bool imageExists = false; // prevents operations on an image if it is not yet loaded
    int drawXPos = 0;         // x position of the image anchor
    int drawYPos = 0;         // y position of the image anchor
    double scale = 1;         // scale of the image

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
    void OnMouseWheelEvent(wxMouseEvent &event);
    void resetScale() { scale = 1.0; }
    void resetYPos() { drawYPos = 0; }
    void centerImage();
    void rescale();
    void makeImageFitPanel();
    void checkPosition();

    DECLARE_EVENT_TABLE()
};

#endif