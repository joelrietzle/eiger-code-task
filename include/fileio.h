#ifndef FILEIO_H
#define FILEIO_H

#include <fstream>
#include <tuple>


struct IO {
    int blockSize;
};

class FileIOClass
{
    public:
        FileIOClass(){};
        virtual ~FileIOClass(){};
        static std::tuple<std::ifstream&, std::string, int> Open(std::string input);
        static int Chunks(uint64_t fileSize);
        IO io;
};

#endif