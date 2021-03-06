#include <stdio.h>
#include <stdlib.h>
#include "extract.hpp"
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

/**
 * Sort a list of char* give the size of the list
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
 * Extract a page from an archive give the archive, a target directory and the page
*/

static int extract(const char *filename, const char *destination, const int page)
{
	struct archive *a;
	struct archive *aTri;
	struct archive *ext;
	struct archive_entry *entry;
	int flags;
	int r;

	/* Select which attributes we want to restore. */
	flags = ARCHIVE_EXTRACT_TIME;
	flags |= ARCHIVE_EXTRACT_PERM;
	flags |= ARCHIVE_EXTRACT_ACL;
	flags |= ARCHIVE_EXTRACT_FFLAGS;

	/* we will read the archive twice, first to get the name of the pages and order them, then to extract the proper page */
	a = archive_read_new();
	archive_read_support_format_all(a);
	aTri = archive_read_new();
	archive_read_support_format_all(aTri);

	/* this is where we will write the page we want to extract */
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

		/* get the name of the page and copy it into names */
		name = archive_entry_pathname(entry);

		size_t len = strlen(name) + 1;
		char *name_cp = new char[len];
		strcpy(name_cp, name);
		names[i] = name_cp;
	}

	/* sort names */
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

		/* check if the page we have is the page to extract */
		if (strcmp(names[page - 1], name) == 0)
		{
			/* if so we set the destination folder */
			const std::string fullOutputPath = destination + std::string(name);
			archive_entry_set_pathname(entry, fullOutputPath.c_str());
			r = archive_write_header(ext, entry);

			if (r < ARCHIVE_OK)
				fprintf(stderr, "%s\n", archive_error_string(ext));
			else if (archive_entry_size(entry) > 0)
			{
				/* we copy the data */
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
	/* close everything */
	archive_read_close(a);
	archive_read_free(a);
	archive_read_close(aTri);
	archive_read_free(aTri);
	archive_write_close(ext);
	archive_write_free(ext);
	return 0;
}
