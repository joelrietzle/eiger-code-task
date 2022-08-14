#ifndef FILEIO_H
#define FILEIO_H

#include <istream>

#include <tuple>


struct IO {
    int blockSize;
};

class FileIOClass
{
    public:
        FileIOClass(){};
        virtual ~FileIOClass(){};
        static std::tuple<std::ifstream&, std::string, int> Open(std::string input, uint64_t blockSize);
        static int Chunks(uint64_t fileSize, uint64_t blockSize);
        IO io;
};

#endif