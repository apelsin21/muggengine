#include "compressionhandler.hpp"

//Returns true on success, false on failure
bool CompressionHandler::CompressData(unsigned char* what, int size, unsigned char* &output_data, long unsigned int &out_size) {
	unsigned char* working_memory = new unsigned char[LZO1X_MEM_COMPRESS];
	
	if(lzo1x_1_compress(what, size, output_data, &out_size, working_memory) >= 0) {
		delete working_memory;
		
		return true;
	} else {
		delete working_memory;
		
		return false;
	}
}

//Returns true on success, false on failure
bool CompressionHandler::DecompressData(unsigned char* what, int size, unsigned char* &output_data, long unsigned int &out_size) {	
	if(lzo1x_decompress(what, size, output_data, &out_size, NULL) >= 0) {
		return true;
	} else {
		return false;
	}
}
