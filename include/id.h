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
        OPEN_ARCHIVE,
        HIDE_BOOKMARK_PANEL,
        NEW_BOOKMARK,
        DELETE_BOOKMARK
    };

    /**
     * Refers to the differents file reading modes
    */
    enum modes
    {
        NONE,
        FILE,
        FOLDER
    };
}

#endif