#include "zip.h"

/**
 * Zip class constructor
 * 
 * @param filePath Path to the CBZ file
*/
Zip::Zip(wxString filePath)
{
    this->filePath = filePath;

    // open the zip
    in = new wxFFileInputStream(filePath);
    zip = new wxZipInputStream(*in);

    // load the zip catalog
    while ((entry = zip->GetNextEntry()) != NULL)
    {
        wxZipEntry *&current = catalog[entry->GetInternalName()];
        // some archive formats can have multiple entries with the same name
        // (e.g. tar) though it is an error in the case of zip
        delete current;
        current = entry;
    }
}

Zip::~Zip()
{
}

/**
 * Opens a specific page of the archive
 * 
 * @param page Page number (begins at 1)
 * @return Image as a wxBitmap type
*/
wxBitmap Zip::openPage(int page)
{
    it = catalog.begin();
    for (int i = 0; i < page; i++)
    {
        if (it != catalog.end())
            it++;
    }
    entry = it->second;
    // wxString text = entry->GetInternalName();
    // std::cout << text << std::endl;
    zip->OpenEntry(*entry);
    wxImage image(*zip, wxBITMAP_TYPE_JPEG);
    return wxBitmap(image);
}