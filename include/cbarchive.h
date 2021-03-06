#ifndef CBARCHIVE_H
#define CBARCHIVE_H

#include <sys/types.h>
#include <sys/stat.h>
#include <archive.h>
#include <archive_entry.h>
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <wx/arrstr.h>
#include <wx/wfstream.h>
#include <wx/zipstrm.h>
#include <wx/filename.h>
#include <wx/image.h>

class CBArchive
{
private:
    const char *filename;

public:
    CBArchive(const char *aFilename) : filename(aFilename) {}
    ~CBArchive() {}

    int extractNumberPages();
    int extract(const char *destination, int page, wxString *pathPage);
    wxArrayString extractAll(const char *destination);
    int extractPages(wxString archiveName, int *pages, int size, const char *destination);

    const char *getFilename() { return filename; }

    void static createCbz(wxArrayString images, wxString archiveName);
};

#endif
