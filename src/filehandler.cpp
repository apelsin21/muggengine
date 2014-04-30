#include "filehandler.hpp"

std::vector<char> mugg::Filehandler::ReadDataFromFilepath(std::string filepath) {
    this->in_stream.open(filepath.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
    std::ifstream::pos_type position = this->in_stream.tellg();

    std::vector<char> data(position);

    this->in_stream.seekg(0, std::ios::beg);
    this->in_stream.read(&data[0], position);

    this->in_stream.close();
    return data;
}

void mugg::Filehandler::WriteDataToFilepath(std::string filepath, std::vector<char> data) {
    this->out_stream.open(filepath.c_str(), std::ios::out | std::ios::binary);

    if(this->out_stream.is_open()) {
        for(int i = 0; i <= data.size(); i++) 
            this->out_stream.put(data[i]);
    } else {
        std::string error_message;
        error_message += "Couldn't open file ";
        error_message += filepath;
        error_message += " for writing, trying to continue...";
        mugg::WriteToLog(mugg::ERROR, error_message);
    }

    this->out_stream.close();
}

void mugg::Filehandler::AppendDataToFilepath(std::string filepath, std::vector<char> data) {
    this->out_stream.open(filepath.c_str(), std::ios::out | std::ios::binary | std::ios::app);

    if(this->out_stream.is_open()) {
        for(int i = 0; i <= data.size(); i++)
            this->out_stream.put(data[i]);
    } else {
        std::string error_message;
        error_message += "Couldn't open file ";
        error_message += filepath;
        error_message += " for writing, trying to continue...";
        mugg::WriteToLog(mugg::ERROR, error_message);
    }

    this->out_stream.close();
}

void mugg::Filehandler::AppendStringToFilepath(std::string filepath, std::string what) {
    this->out_stream.open(filepath.c_str(), std::ios::out | std::ios::app);

    if(this->out_stream.is_open()) {
        this->out_stream << what;
    } else {
        std::string error_message;
        error_message += "Couldn't open file ";
        error_message += filepath;
        error_message += " for writing, trying to continue...";
        mugg::WriteToLog(mugg::ERROR, error_message);
    }

    this->out_stream.close();
}

mugg::File mugg::Filehandler::GetFileFromPath(std::string filepath) {
    File file;
    file.SetFilepath(filepath);

    file.SetData(this->ReadDataFromFilepath(filepath));
    
    return file;
}

void mugg::Filehandler::WriteFileToPath(File file, std::string filepath) {
    this->WriteDataToFilepath(filepath, file.GetData());
}
