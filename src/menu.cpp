#include "menu.h"

#include <wx/artprov.h>

void makeMenuBar(wxMenuBar *menuBar)
{
    // file menu
    wxMenu *fileMenu = new wxMenu();
    menuBar->Append(fileMenu, _("&File"));

    // open file item
    wxMenuItem *openItem = new wxMenuItem(fileMenu, window::id::OPEN_FILE, _("Open file\tCTRL+O"), _("Open an image or a compressed comic book"));
    openItem->SetBitmap(wxArtProvider::GetBitmap(wxART_FILE_OPEN)); // créé une icone pour le menu, apparement ne fonctionne pas sur linux
    fileMenu->Append(openItem);

    // open directory item
    wxMenuItem *openFolderItem = new wxMenuItem(fileMenu, window::id::OPEN_DIRECTORY, _("Open directory\tCTRL+D"), _("Open a directory containing your files"));
    openFolderItem->SetBitmap(wxArtProvider::GetBitmap(wxART_FOLDER_OPEN));
    fileMenu->Append(openFolderItem);

    // sous menu "Exporter..."
    wxMenu *exportMenu = new wxMenu();
    // zip menu item
    wxMenuItem *zipItem = exportMenu->Append(wxID_ANY, _("&ZIP"), _("Export as a .cbz file"));
    // rar menu item
    wxMenuItem *rarItem = exportMenu->Append(wxID_ANY, _("&RAR"), _("Export as a .cbr file"));
    fileMenu->AppendSubMenu(exportMenu, _("&Export as"), _("Export your collection of images as..."));

    fileMenu->AppendSeparator();
    // help menu item
    wxMenuItem *helpItem = new wxMenuItem(fileMenu, wxID_HELP, _("Help"), _("Need some help?"));
    helpItem->SetBitmap(wxArtProvider::GetBitmap(wxART_HELP));
    fileMenu->Append(helpItem);

    fileMenu->AppendSeparator();
    // quit menu item
    wxMenuItem *quitItem = new wxMenuItem(fileMenu, wxID_EXIT);
    quitItem->SetBitmap(wxArtProvider::GetBitmap(wxART_QUIT));
    fileMenu->Append(quitItem);

    // navigation menu
    wxMenu *navigationMenu = new wxMenu();
    menuBar->Append(navigationMenu, _("&Navigation"));

    // zoom options
    wxMenuItem *zoomInItem = new wxMenuItem(navigationMenu, wxID_ZOOM_IN);
    navigationMenu->Append(zoomInItem);
    wxMenuItem *zoomOutItem = new wxMenuItem(navigationMenu, wxID_ZOOM_OUT);
    navigationMenu->Append(zoomOutItem);

    navigationMenu->AppendSeparator();
    // page navigation
    wxMenuItem *previousPageItem = new wxMenuItem(navigationMenu, window::id::PREVIOUS_PAGE, _("&Previous page"), _("Go to the previous page"));
    wxMenuItem *nextPageItem = new wxMenuItem(navigationMenu, window::id::NEXT_PAGE, _("&Next page"), _("Go to the next page"));
    wxMenuItem *firstPageItem = new wxMenuItem(navigationMenu, window::id::FIRST_PAGE, _("&First page\tCTRL+A"), _("Go to the first page"));
    wxMenuItem *lastPageItem = new wxMenuItem(navigationMenu, window::id::LAST_PAGE, _("&Last page\tCTRL+E"), _("Go to the last page"));
    navigationMenu->Append(previousPageItem);
    navigationMenu->Append(nextPageItem);
    navigationMenu->Append(firstPageItem);
    navigationMenu->Append(lastPageItem);
}
