#include "script.hpp"

Script::Script() {
	//TODO: Do something clever
}
Script::~Script() {
	//TODO: Do something clever
}

char* Script::GetContent() {
    return this->content;
}
void Script::SetContent(char* what) {
    this->content = what;
}

bool Script::LoadFromFile(const char* filepath) {
    int data_size;
    this->content = this->filehandler.ReadDataFromFile(filepath, data_size);
    if(data_size != 0) {
        return true;
    } else {
        return false;
    }
}
