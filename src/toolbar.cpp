#include "toolbar.h"
#include <wx/artprov.h>

#include <./../res/icons/zoom-in.xpm>     // bootstrap zoom in icon
#include <./../res/icons/zoom-out.xpm>    // bootstrap zoom out icon
#include <./../res/icons/arrow_left.xpm>  // bootstrap left arrow icon
#include <./../res/icons/arrow_right.xpm> // bootstrap right arrow icon

void makeToolBar(wxToolBar *toolBar)
{
    // open files/directory tools
    toolBar->AddTool(window::id::OPEN_FILE, _("Open file"), wxArtProvider::GetBitmap(wxART_FILE_OPEN));
    toolBar->SetToolShortHelp(window::id::OPEN_FILE, _("Open document"));            // display some text when the mouse hovers the tool for a few seconds
    toolBar->SetToolLongHelp(window::id::OPEN_FILE, _("Open an existing document")); // display text in the status bar

    toolBar->AddTool(window::id::OPEN_DIRECTORY, _("Open directory"), wxArtProvider::GetBitmap(wxART_FOLDER_OPEN));
    toolBar->SetToolShortHelp(window::id::OPEN_DIRECTORY, _("Open a directory"));
    toolBar->SetToolLongHelp(window::id::OPEN_DIRECTORY, _("Open a directory containing your files"));

    toolBar->AddSeparator();
    // zoom tools
    wxBitmap zoomIn(zoom_in);
    wxBitmap zoomOut(zoom_out);
    toolBar->AddTool(wxID_ZOOM_IN, _("Zoom in"), zoomIn);
    toolBar->SetToolShortHelp(wxID_ZOOM_IN, _("Zoom in"));
    toolBar->SetToolLongHelp(wxID_ZOOM_IN, _("Zoom in"));
    toolBar->AddTool(wxID_ZOOM_OUT, _("Zoom out"), zoomOut);
    toolBar->SetToolShortHelp(wxID_ZOOM_OUT, _("Zoom out"));
    toolBar->SetToolLongHelp(wxID_ZOOM_OUT, _("Zoom out"));

    // navigation tools
    wxBitmap leftArrow(arrow_left);
    wxBitmap rightArrow(arrow_right);
    toolBar->AddTool(window::id::PREVIOUS_PAGE, _("Previous page"), leftArrow);
    toolBar->SetToolShortHelp(window::id::PREVIOUS_PAGE, _("Previous page"));
    toolBar->SetToolLongHelp(window::id::PREVIOUS_PAGE, _("Go to the previous page"));
    toolBar->AddTool(window::id::NEXT_PAGE, _("Next page"), rightArrow);
    toolBar->SetToolShortHelp(window::id::NEXT_PAGE, _("Next page"));
    toolBar->SetToolLongHelp(window::id::NEXT_PAGE, _("Go to the next page"));

    toolBar->AddStretchableSpace();

    // help tool
    toolBar->AddTool(wxID_HELP, _("Help"), wxArtProvider::GetBitmap(wxART_HELP));
    toolBar->SetToolShortHelp(wxID_HELP, _("Help"));
    toolBar->SetToolLongHelp(wxID_HELP, _("Click here to get some help!"));
}
