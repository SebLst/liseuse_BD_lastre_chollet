// #include "helloworld.hpp"

#include "main.hpp"
#include "menu.hpp"
#include "frame.hpp"

IMPLEMENT_APP(CBReaderApp);

bool CBReaderApp::OnInit()
{
    Menu *menu = new Menu("CBReader");
    menu->Show(true);

    return true;
}
