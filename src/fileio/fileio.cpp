#include "fileio.h"
#include "mybaseclass.h"
#include <tuple>
#include <istream>
#include <string.h>
#include <math.h>

using namespace std;

std::tuple<std::ifstream&, std::string, int> FileIOClass::Open(std::string input, uint64_t blockSize)
{
    std::streampos begin, end;
    std::ifstream ifs;
    std::streamoff fileSize;
    std::string line;
    
    ifs.open(input, ios::in);

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
        fileSize = end-begin;
        ifs.close();
    }

    uint64_t fileChunks = FileIOClass::Chunks(fileSize, blockSize);

    if (fileChunks <= 1)
    {
        line = "At least 2 chunks are required";
        std::tuple<std::ifstream&, std::string, int> fileChunk(ifs, line, 0);
        return fileChunk;
    }

    line = "Everything went fine";
    std::tuple<std::ifstream&, std::string, int> fileChunk(ifs, line, 1);
    return fileChunk;
}

int FileIOClass::Chunks(uint64_t fileSize, uint64_t blockSize) {
    auto io = MyFactory::CreateFileIOInstance("fileio");
    return{int(ceil(float(fileSize) / float(blockSize)))};
}

