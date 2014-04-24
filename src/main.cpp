#include <iostream>

#include "filehandler.hpp"
#include "compressionhandler.hpp"

#include "tcpclient.hpp"
#include "tcphost.hpp"

#include "scriptengine.hpp"

#include <lua.hpp>

static int doubleTrouble(lua_State* L) {
    double d = luaL_checknumber(L, 1);
    lua_pushnumber(L, d*2);
    return 1;
}

int main() {

    ScriptEngine engine;
    Script* script = new Script();
    script->LoadFromFile("main.lua");
    engine.RunScript(script);

    /*
    const char* string = "";
	int size = strlen(string);
	
	CompressionHandler compress;
	
	unsigned char* outputData = new unsigned char[size + ((size/16) + 64 + 3)];
	long unsigned int outsize;
	
	std::cout << "Raw size: " << strlen(string) << std::endl;
	
	if(compress.CompressData((unsigned char*)string, strlen(string), outputData, outsize)) {
		std::cout << "Compression successful! Data:\n" << outputData << " Size: " << outsize << std::endl;
	} else {
		std::cout << "Compression failed!\n";
	}
	
	unsigned char* decompressedData = new unsigned char[size + ((size/16) + 64 + 3)];
	long unsigned int decompressedSize;
	
	if(compress.DecompressData(outputData, outsize, decompressedData, decompressedSize)) {
		std::cout << "Decompression successful! Data:\n" << decompressedData << " Size: " << decompressedSize << std::endl;
	} else {
		std::cout << "Decompression failed!\n";
	}
    */
	
    delete script;

	return 0;
}
