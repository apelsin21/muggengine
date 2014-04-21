#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <lua.hpp>
#include "filehandler.hpp"

class Script {
private:
	char* content, filepath;
    int size;
    FileHandler filehandler;
public:
	Script();
	~Script();

    bool LoadFromFile(const char* filepath);

    char* GetContent();
    void SetContent(char* what);
};

#endif
