#ifndef ZIP_H
#define ZIP_H

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/zipstrm.h>
#include <wx/wfstream.h>
#include <wx/bitmap.h>

WX_DECLARE_STRING_HASH_MAP(wxZipEntry *, ZipCatalog);

/**
 * Zip class is used to manipulate CBZ files
*/
class Zip
{
private:
    wxString filePath; // path to the zip (cbz) file
    ZipCatalog::iterator it;
    wxZipEntry *entry;      // current zip entry, used to access only one file in the archive
    ZipCatalog catalog;     // stores all the zip entries of the archive
    wxFFileInputStream *in; // input file stream
    wxZipInputStream *zip;  // input zip stream

public:
    Zip(wxString filePath);
    ~Zip();

    wxBitmap openPage(int pageNumber);
};

#endif