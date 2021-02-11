#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/dir.h>
#include "imagepanel.h"

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

    void setPageCurrent(unsigned int pageCurrent) { this->pageCurrent = pageCurrent; }
    void setPageTotal(unsigned int pageTotal) { this->pageTotal = pageTotal; }
    void setPages(unsigned int pageCurrent, unsigned int pageTotal)
    {
        setPageCurrent(pageCurrent);
        setPageTotal(pageTotal);
    }
    unsigned int getPageCurrent() { return pageCurrent; }
    unsigned int getPageTotal() { return pageTotal; }

    void OnOpenFile(wxCommandEvent &event);
    void OnOpenDir(wxCommandEvent &event);
    void OnHelp(wxCommandEvent &event);
    void OnZip(wxCommandEvent &event); // TODO
    void OnRar(wxCommandEvent &event); // TODO
    void OnQuit(wxCommandEvent &event);
    void OnZoomIn(wxCommandEvent &event);
    void OnZoomOut(wxCommandEvent &event);
    void OnArrowLeft(wxCommandEvent &event);
    void OnArrowRight(wxCommandEvent &event);
    void OnFirstPage(wxCommandEvent &event);
    void OnLastPage(wxCommandEvent &event);
    void OnIdle(wxIdleEvent &event);

    ImagePanel *imagePanel;
    wxArrayString files;
    wxString cwd = wxGetCwd();
    wxDir *dir;

    DECLARE_EVENT_TABLE();
};

#endif