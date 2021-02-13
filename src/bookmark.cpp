#include "bookmark.h"
#include "param.h"
#include "id.h"

BEGIN_EVENT_TABLE(BookmarkPanel, wxPanel)
END_EVENT_TABLE()

BookmarkPanel::BookmarkPanel(wxFrame *parent)
    : wxPanel(parent)
{
    SetBackgroundColour(wxColor(*wxWHITE));
    SetMaxSize(wxSize(param::BOOKMARK_PANEL_MAX_SIZE_X, 1000000));
}

BookmarkPanel::~BookmarkPanel()
{
}