#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "imagepanel.h"

class MainWindow : public wxFrame
{
public:
    MainWindow(wxWindow *parent,
               wxWindowID id,
               const wxString &title,
               const wxPoint &pos = wxDefaultPosition,
               const wxSize &size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE,
               const wxString &name = wxFrameNameStr);
    ~MainWindow();

    void OnOpen(wxCommandEvent &event);
    void OnHelp(wxCommandEvent &event);
    void OnZip(wxCommandEvent &event); // TODO
    void OnRar(wxCommandEvent &event); // TODO
    void OnQuit(wxCommandEvent &event);
    void OnZoomIn(wxCommandEvent &event);
    void OnZoomOut(wxCommandEvent &event);

    ImagePanel *imagePanel;

    DECLARE_EVENT_TABLE();
};

#endif