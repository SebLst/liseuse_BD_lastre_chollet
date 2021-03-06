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
    int currentPage = -1;

public:
    BookmarkPanel(wxFrame *parent);
    ~BookmarkPanel();

    wxBoxSizer *sizer;
    wxBoxSizer *bookmarkSizer;
    wxScrolledWindow *bookmarkList;

    int getCurrentPage() { return currentPage; }
    void setCurrentPage(int currentPage) { this->currentPage = currentPage; }

    void addBookmark(wxCommandEvent &event);
    void deleteBookmark(wxCommandEvent &event);

    DECLARE_EVENT_TABLE();
};

#endif