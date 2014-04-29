#ifndef COMPRESSIONHANDLER_HPP
#define COMPRESSIONHANDLER_HPP

#include "minilzo.h"

class CompressionHandler {
private:
	int size;
public:
	CompressionHandler();
	~CompressionHandler();
	
	bool CompressData(unsigned char* what, int size, unsigned char* &output_data, long unsigned int &out_size);
	bool DecompressData(unsigned char* what, int size, unsigned char* &output_data, long unsigned int &out_size);
};

#endif
