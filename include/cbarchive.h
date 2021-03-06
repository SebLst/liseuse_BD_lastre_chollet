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


/*
inline void tri_iteratif(const char *tableau[], int size);

static int copy_data(struct archive *ar, struct archive *aw);

static int extract(const char *filename, const char *destination, const int page);

static int extractNumberPages(const char *filename);
*/

class CBArchive
{
private:
    const char *filename;

public:
    CBArchive(const char *aFilename): filename(aFilename) {}
    ~CBArchive() {}

    int extractNumberPages();

    int extract(const char *destination, int page);

};



#endif

