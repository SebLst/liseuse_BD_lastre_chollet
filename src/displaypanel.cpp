/*
#include "displaypanel.hpp"

// Stolen shamelessly on zetcode.com/gui/wxwidgets/layoutmanagement for testing purposes
// For now, this is only display and does nothing

DisplayPanel::DisplayPanel(wxWindow *parent)
    : wxPanel(parent, wxID_ANY)
{
    // pass
}

bool DisplayPanel::loadImage(wxString path, wxBitmapType format)
{
    wxBitmap file;

    if (image) // if an image is already being displayed
    {
        image->Destroy(); // it is destroyed
    }

    if (file.LoadFile(path, format))
    {
        this->image = new wxStaticBitmap(this, wxID_ANY, file);
        return true;
    }

    std::cout << "something went wrong" << std::endl;
    return false;
}
*/