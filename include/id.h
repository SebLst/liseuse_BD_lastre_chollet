#ifndef ID_H
#define ID_H

namespace window
{
    enum id
    {
        MAINWINDOW = wxID_HIGHEST + 1, // les valeurs entre wxID_LOWEST et wxID_HIGHEST sont réservées à wxWidgets
        IMAGE_PANEL,
        PREVIOUS_PAGE,
        NEXT_PAGE,
        FIRST_PAGE,
        LAST_PAGE,
        OPEN_FILE,
        OPEN_DIRECTORY,
        HIDE_BOOKMARK_PANEL
    };

    enum modes
    {
        NONE,
        FILE,
        BOOK
    };
}

#endif