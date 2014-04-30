#ifndef FILE_HPP
#define FILE_HPP

#include <vector>
#include <string>

namespace mugg {
    class File {
        private:
            std::string filepath;
            std::vector<char> data;
        public:
            void SetFilepath(std::string filepath);
            std::string GetFilepath();

            std::size_t GetSize();
            
            void SetData(std::vector<char> data);
            std::vector<char> GetData();
    };
}

#endif
