#ifndef BOOKMARK_H
#define BOOKMARK_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

/**
 * Panel used for bookmarks
*/
class BookmarkPanel : public wxPanel
{
private:
public:
    BookmarkPanel(wxFrame *parent);
    ~BookmarkPanel();

    DECLARE_EVENT_TABLE();
};

#endif