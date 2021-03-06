#ifndef BOOKMARK_ITEM_H
#define BOOKMARK_ITEM_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "bookmark.h"

/**
 * Class for bookmark buttons.
 * For now, its just here for displaying the bookmarks created but the buttons don't work.
 */
class BookmarkItem : public wxBoxSizer
{
private:
    int page;
    wxButton *bookmarkButton;
    wxButton *deleteButton;

public:
    BookmarkItem(wxWindow *parent, wxString bookmarkName, int page);
    ~BookmarkItem();

    void setPage(int page) { this->page = page; }
    int getPage() { return page; }
};

#endif