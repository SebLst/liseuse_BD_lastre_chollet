#include "imagepanel.h"
#include "id.h"

#include <param.h>

BEGIN_EVENT_TABLE(ImagePanel, wxPanel)
EVT_PAINT(ImagePanel::paintEvent)
EVT_MOUSEWHEEL(ImagePanel::OnMouseWheelEvent)
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
    dc.DrawBitmap(displayImage, drawXPos, drawYPos, false);
}

void ImagePanel::loadImage(wxString file, wxBitmapType format)
{
    baseImage.LoadFile(file, format); // image file should be checked by the calling function
    displayImage = baseImage;
    imageExists = true;

    // initially the image is centered at the top
    centerImage();
}

void ImagePanel::setScale(double scale)
{
    this->scale = scale;
}

void ImagePanel::zoomIn()
{
    setScale(scale + param::ZOOM_STEP);
    rescale();
    Refresh();
}

void ImagePanel::zoomOut()
{
    if (scale - param::ZOOM_STEP >= param::MIN_SCALE)
    {
        setScale(scale - param::ZOOM_STEP);
        rescale();
        Refresh();
    }
}

void ImagePanel::OnMouseWheelEvent(wxMouseEvent &event)
{
    int rotation;
    event.GetWheelRotation() > 0 ? rotation = 1 : rotation = -1;

    if (event.ShiftDown() && !event.ControlDown())
    {
        drawXPos += rotation * param::SCROLL_STEP;
    }
    else if (!event.ShiftDown() && event.ControlDown())
    {
        rotation > 0 ? zoomIn() : zoomOut();
    }
    else
    {
        drawYPos += rotation * param::SCROLL_STEP;
    }

    Refresh();
}

void ImagePanel::centerImage()
{
    if (imageExists)
    {
        int imageWidth = displayImage.GetWidth();
        wxSize imagePanelSize = GetSize();
        int imagePanelWidth = imagePanelSize.GetWidth();
        drawXPos = std::max((imagePanelWidth - imageWidth) / 2, 0);
    }
    Refresh();
}

void ImagePanel::rescale()
{
    wxImage toScaleImage = baseImage.ConvertToImage();

    // toScaleImage.Rescale(image.GetWidth() * (1 + param::ZOOM_STEP * direction),
    //                      image.GetHeight() * (1 + param::ZOOM_STEP * direction),
    //                      wxIMAGE_QUALITY_BICUBIC);
    // image = toScaleImage;

    displayImage = wxBitmap(toScaleImage.Scale(baseImage.GetWidth() * scale,
                                               baseImage.GetHeight() * scale,
                                               wxIMAGE_QUALITY_BICUBIC));

    Refresh();
}

ImagePanel::~ImagePanel()
{
}