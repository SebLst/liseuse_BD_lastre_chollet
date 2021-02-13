#ifndef APP_H
#define APP_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class App : public wxApp
{
public:
    App();
    bool OnInit();
    ~App();
};

#endif
