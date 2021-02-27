#ifndef IMAGE_PANEL_H
#define IMAGE_PANEL_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "id.h"
#include "zip.h"

/**
 * Panel used to display images
*/
class ImagePanel : public wxPanel
{
private:
    wxBitmap baseImage;                                                                                       // the base image
    wxBitmap displayImage;                                                                                    // this one will be scaled for zooming
    Zip *zip = new Zip(_("/home/sebastien/Documents/2A/IN204/liseuse_BD_lastre_chollet/res/Blackhawkz.cbz")); // zip file (cbz) currently open (if any)
    bool imageExists = false;                                                                                 // prevents operations on an image if it is not yet loaded
    int drawXPos = 0;                                                                                         // x position of the image anchor
    int drawYPos = 0;                                                                                         // y position of the image anchor
    double scale = 1;                                                                                         // scale of the image
    window::modes currentMode = window::modes::NONE;

public:
    ImagePanel(wxFrame *parent);
    ~ImagePanel();

    /**
     * Sets the current mode
     * @param mode NONE, FILE or BOOK
    */
    void setMode(window::modes mode)
    {
        currentMode = mode;
    }

    /**
     * Gets the current mode
     * @return Current mode (NONE, FILE or BOOK)
    */
    window::modes getMode()
    {
        return currentMode;
    }

    void paintEvent(wxPaintEvent &evt);
    void paintNow();
    void loadImage(wxString file, wxBitmapType format);
    void loadZipImage(int page);
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