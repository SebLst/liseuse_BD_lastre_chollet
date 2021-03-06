#include "cbarchive.h"

/**
 * Sort a list of char* give the size of the list
 * @param tableau List that will be sorted
 * @param size Size of the list
*/
void tri_iteratif(const char *tableau[], int size)
{
	const char *temp;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (strcmp(tableau[i], tableau[j]) < 0)
			{
				temp = tableau[i];
				tableau[i] = tableau[j];
				tableau[j] = temp;
			}
		}
	}
}

/**
 * Copy a given archived file into a repository
 * @param ar Archive readed
 * @param aw Archive writed
 * @return Return the status of the copy
*/
static int copy_data(struct archive *ar, struct archive *aw)
{
	int r;
	const void *buff;
	size_t size;
	off_t offset;
	for (;;)
	{
		r = archive_read_data_block(ar, &buff, &size, &offset);
		if (r == ARCHIVE_EOF)
			return (ARCHIVE_OK);
		if (r < ARCHIVE_OK)
			return (r);
		r = archive_write_data_block(aw, buff, size, offset);
		if (r < ARCHIVE_OK)
		{
			fprintf(stderr, "%s\n", archive_error_string(aw));
			return (r);
		}
	}
}

/**
 * Extract a single page from an archive
 * @param destination Destination folder
 * @param page The number of the page needed
 * @param pathPage Path to the extracted page
 * @return Return the status of the extraction (0 = ok)
*/
int CBArchive::extract(const char *destination, int page, wxString *pathPage)
{
	struct archive *a;
	struct archive *aTri;
	struct archive *ext;
	struct archive_entry *entry;
	int flags;
	int r;

	// Select which attributes we want to restore.
	flags = ARCHIVE_EXTRACT_TIME;
	flags |= ARCHIVE_EXTRACT_PERM;
	flags |= ARCHIVE_EXTRACT_ACL;
	flags |= ARCHIVE_EXTRACT_FFLAGS;

	// we will read the archive twice, first to get the name of the pages and order them, then to extract the proper page
	a = archive_read_new();
	archive_read_support_format_all(a);
	aTri = archive_read_new();
	archive_read_support_format_all(aTri);

	// this is where we will write the page we want to extract
	ext = archive_write_disk_new();
	archive_write_disk_set_options(ext, flags);
	archive_write_disk_set_standard_lookup(ext);

	if ((r = archive_read_open_filename(aTri, filename, 10240)))
		return 1;

	const char *names[200];
	const char *name;
	int i = 0;
	for (;; i++)
	{
		r = archive_read_next_header(aTri, &entry);
		if (r == ARCHIVE_EOF)
			break;
		if (r < ARCHIVE_OK)
			fprintf(stderr, "%s\n", archive_error_string(aTri));
		if (r < ARCHIVE_WARN)
			return 1;

		// get the name of the page and copy it into names
		name = archive_entry_pathname(entry);

		size_t len = strlen(name) + 1;
		char *name_cp = new char[len];
		strcpy(name_cp, name);
		names[i] = name_cp;
	}

	// sort names
	tri_iteratif(names, i);

	if ((r = archive_read_open_filename(a, filename, 10240)))
		return 1;

	for (;;)
	{
		r = archive_read_next_header(a, &entry);
		if (r == ARCHIVE_EOF)
			break;
		if (r < ARCHIVE_OK)
			fprintf(stderr, "%s\n", archive_error_string(a));
		if (r < ARCHIVE_WARN)
			return 1;
		name = archive_entry_pathname(entry);

		// check if the page we have is the page to extract
		if (strcmp(names[page - 1], name) == 0)
		{
			// if so we set the destination file
			const std::string fullOutputPath = destination + std::string(name);
			archive_entry_set_pathname(entry, fullOutputPath.c_str());
			*pathPage = wxString(fullOutputPath.c_str());
			r = archive_write_header(ext, entry);

			if (r < ARCHIVE_OK)
				fprintf(stderr, "%s\n", archive_error_string(ext));
			else if (archive_entry_size(entry) > 0)
			{
				// we copy the data
				r = copy_data(a, ext);
				if (r < ARCHIVE_OK)
					fprintf(stderr, "%s\n", archive_error_string(ext));
				if (r < ARCHIVE_WARN)
					return 1;
			}
		}
		r = archive_write_finish_entry(ext);
		if (r < ARCHIVE_OK)
			fprintf(stderr, "%s\n", archive_error_string(ext));
		if (r < ARCHIVE_WARN)
			return 1;
	}
	// close everything
	archive_read_close(a);
	archive_read_free(a);
	archive_read_close(aTri);
	archive_read_free(aTri);
	archive_write_close(ext);
	archive_write_free(ext);
	return 0;
}

/**
 * Give the number of pages within an archive
 * @return Return the number of pages or -1 if there was an error
*/
int CBArchive::extractNumberPages()
{
	struct archive *a;
	struct archive_entry *entry;
	int r;

	a = archive_read_new();
	archive_read_support_format_all(a);

	if ((r = archive_read_open_filename(a, filename, 10240)))
		return -1;

	// Read the archive while we have not found the last page
	int i = 0;
	for (;; i++)
	{
		r = archive_read_next_header(a, &entry);
		if (r == ARCHIVE_EOF)
			break;
		if (r < ARCHIVE_OK)
			fprintf(stderr, "%s\n", archive_error_string(a));
		if (r < ARCHIVE_WARN)
			return -1;
	}

	// close everything
	archive_read_close(a);
	archive_read_free(a);

	return i;
}

/**
 * Extract all pages from an archive
 * @param destination Destination folder
 * @return Return a wxArrayString of the paths of the extracted images in order, or an empty wxArrayString if something went wrong
*/
wxArrayString CBArchive::extractAll(const char *destination)
{
	wxArrayString paths;
	wxArrayString wxNull;
	wxString path;
	int numberPages = this->extractNumberPages();
	if (numberPages == -1)
		return wxNull;

	for (int i = 1; i <= numberPages; i++)
	{
		if (this->extract(destination, i, &path))
			return wxNull;
		paths.Add(path);
	}
	paths.Sort();
	return paths;
}

/**
 * Create a cbz archive
 * @param images List of paths to the images
 * @param archiveName Path and Name of the archive
*/
void CBArchive::createCbz(wxArrayString images, wxString archiveName)
{
	wxZipOutputStream zip(new wxFileOutputStream(archiveName));

	for (int i = 0; i < images.GetCount(); i++)
	{
		// get the full path to the image
		wxFileName fullPath(images[i]);
		fullPath.Normalize();
		wxString temp = fullPath.GetFullPath();

		// load the image as a wxImage
		wxImage image;
		image.LoadFile(temp, wxBITMAP_TYPE_ANY);

		// save the image in the archive
		wxFileInputStream fis(images[i]);
		zip.PutNextEntry(temp);
		image.SaveFile(zip, wxBITMAP_TYPE_JPEG); // ideally, we would ask the image format to the user
	}
}

/**
 * Extract images from a cbz as a new cbz archive
 * @param archiveName Path and name of the new archive
 * @param pages List of the pages to extract
 * @param size Size of the list pages
 * @param destination Destination directory path
 * @return Return 1 if something went wrong
*/
int CBArchive::extractPages(wxString archiveName, int *pages, int size, const char *destination)
{
	wxArrayString images;
	wxString path;
	for (int i = 0; i < size; i++)
	{
		if (this->extract(destination, pages[i], &path))
			return 1;
		images.Add(path);
	}
	createCbz(images, archiveName);
	return 0;
}