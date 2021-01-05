#ifndef EXTRACT_HPP
#define EXTRACT_HPP
#include <string>


// This function unzip a full document (filename) from the place source_path and put it in the place directory_path
void extract_zip(std::string source_path, std::string filename, std::string directory_path="NULL");



#endif
