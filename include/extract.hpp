#ifndef EXTRACT_HPP
#define EXTRACT_HPP
#include <string>


// This function unzip a full document (filename) from the place source_path and put it in the place directory_path
void extract_zip(std::string source_path, std::string filename, std::string directory_path="NULL");

// This function extract the names of the files from a zip archive (filename) placed at source_path and put them in a file 
//void extract_file_names_zip(std::string source_path, std::string filename, std::string directory_file);


#endif
