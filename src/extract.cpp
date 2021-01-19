#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "extract.hpp"

void extract_zip(std::string source_path, std::string filename, std::string directory_path)
{
	if (directory_path=="NULL") directory_path = source_path;
	
	std::string shell = "../include/extract.sh";
	system((shell + " " + "extract_zip" + " " + source_path + " " + directory_path + " " + filename).c_str());
}


/*
void extract_file_names_zip(std::string source_path, std::string filename, std::string directory_file)
{
	std::string shell = "../include/extract.sh";
	system((shell + " " + "extract_file_names_zip" + " " + source_path + " " + filename + " " + directory_file).c_str());
}
	
*/
