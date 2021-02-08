#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

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
    void OnZip(wxCommandEvent &event);
    void OnRar(wxCommandEvent &event);
    void OnQuit(wxCommandEvent &event);

    DECLARE_EVENT_TABLE();
};

#endif