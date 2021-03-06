#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/dir.h>
#include "imagepanel.h"
#include "bookmark.h"

class MainWindow : public wxFrame
{
private:
    unsigned int pageCurrent, pageTotal;

public:
    MainWindow(wxWindow *parent,
               wxWindowID id,
               const wxString &title,
               const wxPoint &pos = wxDefaultPosition,
               const wxSize &size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE,
               const wxString &name = wxFrameNameStr);
    ~MainWindow();

    /**
     * Sets the current page
     * @param pageCurrent Current page number
    */
    void setPageCurrent(unsigned int pageCurrent) { this->pageCurrent = pageCurrent; }

    /**
     * Sets the page total
     * @param pageTotal Total number of pages
    */
    void setPageTotal(unsigned int pageTotal) { this->pageTotal = pageTotal; }

    /**
     * Sets the current page and the page total
     * @param pageCurrent Current page
     * @param pageTotal Total number of pages
    */
    void setPages(unsigned int pageCurrent, unsigned int pageTotal)
    {
        setPageCurrent(pageCurrent);
        setPageTotal(pageTotal);
    }

    /**
     * Gets the current page
     * @return Current page number
    */
    unsigned int getPageCurrent() { return pageCurrent; }

    /**
     * Gets the page total
     * @return Total number of pages
    */
    unsigned int getPageTotal() { return pageTotal; }

    void OnOpenFile(wxCommandEvent &event);
    void OnOpenDir(wxCommandEvent &event);
    void OnOpenArchive(wxCommandEvent &event);
    void OnHelp(wxCommandEvent &event);
    void OnQuit(wxCommandEvent &event);
    void OnZoomIn(wxCommandEvent &event);
    void OnZoomOut(wxCommandEvent &event);
    void OnArrowLeft(wxCommandEvent &event);
    void OnArrowRight(wxCommandEvent &event);
    void OnFirstPage(wxCommandEvent &event);
    void OnLastPage(wxCommandEvent &event);
    void OnShowBookmarks(wxCommandEvent &event);

    void OnIdle(wxIdleEvent &event);

    ImagePanel *imagePanel;       // the image panel, in which the image is displayed
    BookmarkPanel *bookmarkPanel; // the bookmark panel
    wxArrayString files;          // an array of wxString containing the list of paths to the files of the comic book
    wxString cwd = wxGetCwd();    // current working directory path
    wxDir *dir;                   // current working directory
    wxStatusBar *statusBar;       // The status bar, displays information

    DECLARE_EVENT_TABLE();
};

#endif