#include "filehandler.hpp"

std::vector<char> mugg::Filehandler::ReadFile(std::string filepath) {
    this->in_stream.open(filepath.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
    std::ifstream::pos_type position = this->in_stream.tellg();

    std::vector<char> data(position);

    this->in_stream.seekg(0, std::ios::beg);
    this->in_stream.read(&data[0], position);

    this->in_stream.close();
    return data;
}

void mugg::Filehandler::WriteDataToFile(std::string filepath, std::vector<char> data) {
    this->out_stream.open(filepath.c_str(), std::ios::out | std::ios::binary);

    if(this->out_stream.is_open()) { 
        for(int i = 0; i <= data.size(); i++) {
            this->out_stream.put(data[i]);
        }
    }

    this->out_stream.close();
}

void mugg::Filehandler::AppendStringToFile(std::string filepath, std::string what) {
    this->out_stream.open(filepath.c_str(), std::ios::out | std::ios::app);

    if(this->out_stream.is_open()) {
        this->out_stream << what;
    }

    this->out_stream.close();
}
