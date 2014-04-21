#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <ostream>

class FileHandler {
private:
	std::ifstream in_stream;
	std::ofstream out_stream;
public:
	FileHandler();
	~FileHandler();

	int GetFileSize(const char* where);
	
	char* ReadDataFromFile(const char* where, int &out_size);
	void WriteBinaryDataToFile(const char* where, unsigned char* data, int size);
	
	void WriteTextToFile(const char* where, const char* text);
};

#endif