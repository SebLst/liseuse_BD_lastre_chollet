#ifndef ID_H
#define ID_H

namespace window
{
    /**
     * Refers to the differents window and event id
    */
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

    /**
     * Refers to the differents file reading modes
    */
    enum modes
    {
        NONE,
        FILE,
        FOLDER,
        ZIP
    };
}

#endif