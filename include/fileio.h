#ifndef FILEIO_H
#define FILEIO_H

#include <fstream>
#include <tuple>
#include "mybaseclass.h"

class FileIOClass
{
    public:
        FileIOClass(){};
        virtual ~FileIOClass(){};
        static std::tuple<std::ifstream&, std::string, int> Open(std::string input);
        static int Chunks(uint64_t fileSize);
};

#endif