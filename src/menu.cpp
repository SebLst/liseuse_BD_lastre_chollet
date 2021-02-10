#include "menu.h"

#include <wx/artprov.h>

void makeMenuBar(wxMenuBar *menuBar)
{
    wxMenu *fileMenu = new wxMenu();
    menuBar->Append(fileMenu, _("&File"));

    // new menu item
    wxMenuItem *openItem = new wxMenuItem(fileMenu, wxID_OPEN);
    openItem->SetBitmap(wxArtProvider::GetBitmap(wxART_FILE_OPEN)); // créé une icone pour le menu, apparement ne fonctionne pas sur linux
    fileMenu->Append(openItem);

    // help menu item
    wxMenuItem *helpItem = new wxMenuItem(fileMenu, wxID_HELP, _("Help"), _("Need some help?"));
    helpItem->SetBitmap(wxArtProvider::GetBitmap(wxART_HELP));
    fileMenu->Append(helpItem);

    fileMenu->AppendSeparator();
    // sous menu "Exporter..."
    wxMenu *exportMenu = new wxMenu();
    // zip menu item
    wxMenuItem *zipItem = exportMenu->Append(wxID_ANY, _("&ZIP"), _("Export as a .cbz file"));
    // rar menu item
    wxMenuItem *rarItem = exportMenu->Append(wxID_ANY, _("&RAR"), _("Export as a .cbr file"));
    fileMenu->AppendSubMenu(exportMenu, _("&Export as"), _("Export your collection of images as..."));

    fileMenu->AppendSeparator();
    // quit menu item
    wxMenuItem *quitItem = new wxMenuItem(fileMenu, wxID_EXIT);
    quitItem->SetBitmap(wxArtProvider::GetBitmap(wxART_QUIT));
    fileMenu->Append(quitItem);
}
