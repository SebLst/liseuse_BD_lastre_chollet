#ifndef BOOKMARK_ITEM_H
#define BOOKMARK_ITEM_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

/**
 * Class for bookmark buttons
 * 
 */
class BookmarkItem : public wxButton
{
private:
    int page;

public:
    BookmarkItem(wxWindow *parent,
                 wxWindowID id,
                 const wxString &label = wxEmptyString,
                 const wxPoint &pos = wxDefaultPosition,
                 const wxSize &size = wxDefaultSize,
                 long style = 0,
                 const wxValidator &validator = wxDefaultValidator,
                 const wxString &name = wxButtonNameStr);
    ~BookmarkItem();

    void setPage(int page) { this->page = page; }
    int getPage() { return page; }
};

#endif