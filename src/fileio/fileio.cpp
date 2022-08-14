#include "fileio.h"
#include "mybaseclass.h"
#include <tuple>
#include <fstream>
#include <istream>
#include <string.h>
#include <math.h>

using namespace std;

std::tuple<std::ifstream&, std::string, int> FileIOClass::Open(std::string input)
{
    std::streampos begin, end;
    std::ifstream ifs (input, std::ios::binary);
    std::streamoff fileSize = end-begin;
    std::string line;
    


    ifs.open(input, std::ifstream::in);

    if (ifs.fail())
    {
        line = "File failed to open";
        std::tuple<std::ifstream&, std::string, int> fileChunk(ifs, line, 0);
        return fileChunk;
    }


    else 
    {    
        begin = ifs.tellg();
        ifs.seekg(0, std::ios::end);
        end = ifs.tellg();
        ifs.close();
    }


    uint64_t fileChunks = FileIOClass::Chunks(fileSize);

    if (fileChunks <= 1)
    {
        printf("At least 2 chunks are required");
        line = "At least 2 chunks are required";
        std::tuple<std::ifstream&, std::string, int> fileChunk(ifs, line, 0);
        return fileChunk;
    }
    line = "Everything went fine";
    std::tuple<std::ifstream&, std::string, int> fileChunk(ifs, line, 0);
    return fileChunk;
}

int FileIOClass::Chunks(uint64_t fileSize) {
    auto io = MyFactory::CreateFileIOInstance("fileio");
    return{int(ceil(float(fileSize) / float(io->io.blockSize)))};
}

