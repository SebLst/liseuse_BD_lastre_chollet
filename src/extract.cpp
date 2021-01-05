#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "extract.hpp"

void extract_zip(std::string source_path, std::string filename, std::string directory_path){
	if (directory_path=="NULL") directory_path = source_path;
	
	std::string shell = "../include/extract.sh";
	system((shell + " "+ source_path + " " + directory_path + " " + filename).c_str());
}


