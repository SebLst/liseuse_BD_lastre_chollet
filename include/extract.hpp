#ifndef EXTRACT_HPP
#define EXTRACT_HPP

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

inline void tri_iteratif(const char *tableau[], int size);

static int copy_data(struct archive *ar, struct archive *aw);

static int extract(const char *filename, const char *destination, const int page);

#endif
