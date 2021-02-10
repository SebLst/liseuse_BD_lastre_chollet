#include "imagepanel.h"
#include "algorithm"

#include <param.h>

BEGIN_EVENT_TABLE(ImagePanel, wxPanel)
EVT_PAINT(ImagePanel::paintEvent)
END_EVENT_TABLE()

ImagePanel::ImagePanel(wxFrame *parent)
    : wxPanel(parent)
{
}

void ImagePanel::paintEvent(wxPaintEvent &WXUNUSED(event))
{
    if (imageExists)
    {
        wxPaintDC dc(this);
        render(dc);
    }
}

void ImagePanel::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

void ImagePanel::render(wxDC &dc)
{
    int imageWidth = image.GetWidth();
    wxSize imagePanelSize = GetSize();
    int imagePanelWidth = imagePanelSize.GetWidth();
    drawXPos = std::max(static_cast<int>((imagePanelWidth - imageWidth * scale) / 2), 0); // TODO fix the zoom
    dc.SetUserScale(scale, scale);
    dc.DrawBitmap(image, drawXPos, drawYPos, false);
}

void ImagePanel::loadImage(wxString file, wxBitmapType format)
{
    image.LoadFile(file, format); // image file should be checked by the calling function
    imageExists = true;
}

void ImagePanel::setScale(double scale)
{
    this->scale = scale;
}

void ImagePanel::zoomIn()
{
    setScale(scale + param::zoomStep);
}

void ImagePanel::zoomOut()
{
    if (scale - param::zoomStep >= param::minScale)
    {
        setScale(scale - param::zoomStep);
    }
}

ImagePanel::~ImagePanel()
{
}