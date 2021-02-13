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
    SetBackgroundColour(wxColor(*wxBLACK));
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
    checkPosition();
    dc.DrawBitmap(displayImage, drawXPos, drawYPos, false);
}

void ImagePanel::loadImage(wxString file, wxBitmapType format)
{
    baseImage.LoadFile(file, format); // image file should be checked by the calling function
    displayImage = baseImage;
    imageExists = true;

    // initially the image is centered at the top
    centerImage();
    rescale();
}

/**
 * Setter of scale
 * @param scale scale of the image (> 0, 1 = original size)
*/
void ImagePanel::setScale(double scale)
{
    this->scale = scale;
}

/**
 * Scales the image up one step and refreshes the panel
*/
void ImagePanel::zoomIn()
{
    setScale(scale + param::ZOOM_STEP);
    rescale();
    Refresh();
}

/**
 * Scales the image down one step and refreshes the panel
*/
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
        rotation > 0 ? zoomIn() : zoomOut();
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

    displayImage = wxBitmap(toScaleImage.Scale(baseImage.GetWidth() * scale,
                                               baseImage.GetHeight() * scale,
                                               wxIMAGE_QUALITY_BICUBIC));

    Refresh();
}

void ImagePanel::makeImageFitPanel()
{
    int width, height;
    width = std::max(GetParent()->GetSize().GetWidth(), baseImage.GetWidth());
    height = GetParent()->GetSize().GetHeight() - GetSize().GetHeight() + baseImage.GetHeight();
    GetParent()->SetSize(wxSize(width, height));
}

/**
 * Checks and updates if needed the position of the image anchor to prevent the displayed image from leaving the panel
*/
void ImagePanel::checkPosition()
{
    wxSize panelSize = GetSize();
    int imageWidth = displayImage.GetWidth();
    int imageHeight = displayImage.GetHeight();
    int drawXPosMin, drawYPosMin; // min position of the image anchor
    int drawXPosMax, drawYPosMax; // max position of the image anchor

    drawXPosMin = std::min(panelSize.GetWidth() - imageWidth, 0);
    drawYPosMin = std::min(panelSize.GetHeight() - imageHeight, 0);
    drawXPosMax = std::max(panelSize.GetWidth() - imageWidth, 0);
    drawYPosMax = std::max(panelSize.GetHeight() - imageHeight, 0);

    if (drawXPos < drawXPosMin)
        drawXPos = drawXPosMin;
    if (drawYPos < drawYPosMin)
        drawYPos = drawYPosMin;
    if (drawXPos > drawXPosMax)
        drawXPos = drawXPosMax;
    if (drawYPos > drawYPosMax)
        drawYPos = drawYPosMax;
}

ImagePanel::~ImagePanel()
{
}