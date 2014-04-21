#include "filehandler.hpp"

FileHandler::FileHandler() {
	//TODO: Do something
}

FileHandler::~FileHandler() {
	//TODO: Do something
}

int FileHandler::GetFileSize(const char* where) {
	FILE *p_file = NULL;
    p_file = fopen(where, "rb");
    fseek(p_file, 0, SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);
    return size;
}

char* FileHandler::ReadDataFromFile(const char* where, int &out_size) {
	this->in_stream.open(where, std::ios::in | std::ios::binary);
	char* buffer = NULL;
	if(this->in_stream.is_open()) {
		out_size = this->GetFileSize(where);
		
		buffer = new char[out_size];
		this->in_stream.read(buffer, out_size);
		
		this->in_stream.close();
	} else {
		std::cout << "Couldn't open " << where << " for reading.\n";
	}
	
	return buffer;
}

void FileHandler::WriteBinaryDataToFile(const char* where, unsigned char* data, int size) {
	this->out_stream.open(where, std::ios::out | std::ios::trunc | std::ios::binary);
	
	if(this->out_stream.is_open()) {
		this->out_stream.write((const char*)data, size);
	} else {
		std::cout << "Couldn't open file " << where << " for writing.\n";
	}
	
	this->out_stream.close();
}
