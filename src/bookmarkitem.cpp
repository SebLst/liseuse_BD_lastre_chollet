#include "bookmarkitem.h"

BookmarkItem::BookmarkItem(wxWindow *parent, wxString bookmarkName, int page)
    : wxBoxSizer(wxHORIZONTAL)
{
    this->page = page;
    bookmarkButton = new wxButton(parent, -1, bookmarkName);
    deleteButton = new wxButton(parent, -1, wxString::Format(wxT("Page %i"), page));
    Add(bookmarkButton, wxALIGN_LEFT);
    Add(deleteButton, wxALIGN_RIGHT);
}

BookmarkItem::~BookmarkItem()
{
}