#include "toolbar.h"
#include <wx/artprov.h>

#include <icons/zoom-in.xpm>
#include <icons/zoom-out.xpm>

void makeToolBar(wxToolBar *toolBar)
{
    toolBar->AddTool(wxID_OPEN, _("Open"), wxArtProvider::GetBitmap(wxART_FILE_OPEN));
    toolBar->SetToolShortHelp(wxID_OPEN, _("Open document"));            // display some text when the mouse hovers the tool for a few seconds
    toolBar->SetToolLongHelp(wxID_OPEN, _("Open an existing document")); // display text in the status bar

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

    toolBar->AddStretchableSpace();

    // help tool
    toolBar->AddTool(wxID_HELP, _("Help"), wxArtProvider::GetBitmap(wxART_HELP));
    toolBar->SetToolShortHelp(wxID_HELP, _("Help"));
    toolBar->SetToolLongHelp(wxID_HELP, _("Click here to get some help!"));
}
