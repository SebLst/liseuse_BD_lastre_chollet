#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "bookmarkitem.h"

/**
 * Panel used for bookmarks
*/
class BookmarkPanel : public wxPanel
{
private:
public:
    BookmarkPanel(wxFrame *parent);
    ~BookmarkPanel();

    wxBoxSizer *sizer;
    wxBoxSizer *bookmarkSizer;
    wxScrolledWindow *bookmarkList;

    void addBookmark(wxCommandEvent &event);

    DECLARE_EVENT_TABLE();
};

#endif