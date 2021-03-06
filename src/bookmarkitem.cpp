#include "bookmarkitem.h"

BookmarkItem::BookmarkItem(wxWindow *parent,
                           wxWindowID id,
                           const wxString &label,
                           const wxPoint &pos,
                           const wxSize &size,
                           long style,
                           const wxValidator &validator,
                           const wxString &name)
    : wxButton(parent, id, label, pos, size, style, validator, name)
{
}

BookmarkItem::~BookmarkItem()
{
}