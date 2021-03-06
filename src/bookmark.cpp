#include "bookmark.h"
#include "param.h"
#include "id.h"

BEGIN_EVENT_TABLE(BookmarkPanel, wxPanel)
EVT_BUTTON(window::NEW_BOOKMARK, BookmarkPanel::addBookmark)
END_EVENT_TABLE()

/**
 * Bookmarks constructor
 * @param parent wxFrame parent
*/
BookmarkPanel::BookmarkPanel(wxFrame *parent)
    : wxPanel(parent)
{
    SetBackgroundColour(wxColor(*wxLIGHT_GREY));
    SetMaxSize(wxSize(param::BOOKMARK_PANEL_MAX_SIZE_X, 1000000));

    sizer = new wxBoxSizer(wxVERTICAL);
    bookmarkSizer = new wxBoxSizer(wxVERTICAL);
    bookmarkList = new wxScrolledWindow(this, -1, wxDefaultPosition, wxSize(GetSize()));

    wxStaticText *bookmarkPanelTitle = new wxStaticText(this,
                                                        -1,
                                                        _("Bookmarks"),
                                                        wxDefaultPosition,
                                                        wxSize(200, 50),
                                                        wxALIGN_CENTER_HORIZONTAL);
    wxFont titleFont = bookmarkPanelTitle->GetFont();
    titleFont.SetPointSize(22);
    bookmarkPanelTitle->SetFont(titleFont);

    // bookmark panel buttons
    wxButton *newBookmarkButton = new wxButton(this,
                                               window::NEW_BOOKMARK,
                                               _("Add Bookmark"));

    sizer->Add(bookmarkPanelTitle, 0, wxALIGN_CENTER);
    sizer->Add(bookmarkList, 1, wxEXPAND);
    sizer->Add(newBookmarkButton, 0, wxBOTTOM | wxALIGN_CENTER);

    bookmarkList->SetBackgroundColour(wxColor(*wxLIGHT_GREY));
    bookmarkList->SetScrollRate(5, 5);
    bookmarkList->SetSizer(bookmarkSizer);
    SetSizer(sizer);
    Layout();
}

/**
 * Adds a bookmark in the bookmark list. The bookmark is a button that loads a desired page when clicked.
*/
void BookmarkPanel::addBookmark(wxCommandEvent &WXUNUSED(event))
{
    if (currentPage < 0)
        return;

    wxTextEntryDialog *dialog = new wxTextEntryDialog(this, _("Name your bookmark:"));

    int state = dialog->ShowModal();
    if (state != wxID_OK)
        return;

    wxString bookmarkName = dialog->GetValue();
    if (bookmarkName == _(""))
        return;

    BookmarkItem *bookmarkItem = new BookmarkItem(bookmarkList, bookmarkName, currentPage + 1);
    bookmarkSizer->Add(bookmarkItem, 0, wxALIGN_LEFT);
    Layout();
}

BookmarkPanel::~BookmarkPanel()
{
}