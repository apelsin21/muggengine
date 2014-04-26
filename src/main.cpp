#include <iostream>

#include "filehandler.hpp"
#include "compressionhandler.hpp"

#include "tcpclient.hpp"
#include "tcphost.hpp"

#include "scriptengine.hpp"

#include "udpclient.hpp"

#include <lua.hpp>
#include <string>

static int doubleTrouble(lua_State* L) {
    double d = luaL_checknumber(L, 1);
    lua_pushnumber(L, d*2);
    return 1;
}

std::string GetFromInput() {
    std::cout << "Send message:\n";
    std::string message;
    std::cin >> message;

    return message;
}

int main() {
    UDPClient client;
    client.SetBlocking(false);
    client.BindToPort(54000);

    std::string address;
    unsigned short port;
    std::size_t size;

    std::string message;

    while(true) {
        client.SendMessage("127.0.0.1", 54000, GetFromInput());
        message = (const char*)client.RecieveMessage(address, port, size);
        std::cout << "Recieved \"" << message << "\" from " << address << " on port " << port << " with a size of " << size << std::endl;
    }

    /*
    ScriptEngine engine;
    engine.RegisterFunction(SendMessage, "send_message");
    engine.RegisterFunction(RecieveMessage, "receive_message");

    Script* script;
    script->LoadFromFile("main.lua");
    engine.RunScript(script);

    client.SendMessage("127.0.0.1", 54000, "fungerar det?");
    std::string address;
    unsigned short port;
    std::size_t size;
	const char* message = (const char*)client.RecieveMessage(address, port, size);
    std::cout << "Recieved \"" << message << "\" from " << address << " on port " << port << " with a size of " << size << std::endl;
    
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

	return 0;
}
