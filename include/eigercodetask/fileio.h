#ifndef FILEIO_H
#define FILEIO_H

#include <fstream>
#include <tuple>

class FileIOClass
{
    public:
        FileIOClass(){};
        virtual ~FileIOClass(){};
        std::tuple<std::ifstream&, std::string, int> Open(std::string input);
        int Chunks(uint64_t fileSize);
};

#endif