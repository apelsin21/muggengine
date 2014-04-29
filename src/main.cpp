#include <iostream>

#include "filehandler.hpp"
#include "compressionhandler.hpp"

#include "tcpclient.hpp"
#include "tcphost.hpp"

#include "scriptengine.hpp"

#include "udpclient.hpp"

#include <lua.hpp>
#include <string>

UDPClient client;

static int doubleTrouble(lua_State* L) {
    double d = luaL_checknumber(L, 1);
    lua_pushnumber(L, d*2);
    return 1;
}

static int SendMessage(lua_State* L) {
    if(lua_gettop(L) != 1) {
        std::cout << "send_message function got " << lua_gettop(L) << " arguments, expected 1\n";
    }

    std::string message = luaL_checkstring(L, 1);
    
    client.SendMessage("127.0.0.1", 54000, message);

    std::cout << "Sent message " << message << std::endl;

    return 0;
}
static int RecieveMessage(lua_State* L) {
    if(lua_gettop(L) != 0) {
        std::cout << "recieve_message got parameter, expected none\n";
    }

    std::string address;
    unsigned short port;
    std::size_t size;

    std::string message = client.RecieveMessage(200, address, port, size);

    lua_pushstring(L, message.c_str());
    return 1;
}

int main() {
    FileHandler filehandler;

    client.SetBlocking(false);
    client.BindToPort(54001);

    ScriptEngine engine;
    engine.RegisterFunction(SendMessage, "send_message");
    engine.RegisterFunction(RecieveMessage, "recieve_message");

    int size;
    Script* script;
    
    std::string file = (const char*)filehandler.ReadDataFromFile("main.lua", size);
    script->SetContent((char*)file.c_str());
    /*
    std::string address;
    unsigned short port;
    std::size_t size;

    std::string message;

    do {
        std::cout << "Send:\n";
        std::cin >> message;
        client.SendMessage("127.0.0.1", 54000, message);
        message = client.RecieveMessage(200, address, port, size);
        if(message != "")
            std::cout << "Recieved \"" << message << "\" from " << address << ":" << port << " with size: " << size << std::endl;
    } while(message != "/quit");
    
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
