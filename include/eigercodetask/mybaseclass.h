#ifndef MYBASECLASS_H
#define MYBASECLASS_H

#include "eigercodetask/fileio.h"
#include "eigercodetask/sync.h"
#include "eigercodetask/adler32.h"
#include "eigercodetask/myfactory.h"
#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <vector>
#include <tuple>


struct sync {
    int blockSize;
};

struct IO {
    int blockSize;
};

class MyBaseClass 
{
    public:
        MyBaseClass(){};
        virtual ~MyBaseClass(){};
        //Declaring FileIO and Sync structs
        IO io;
        struct sync Sync;
        Table table;

        // Declaring Adler32 Functions and Struct
        adler32 Adler32;
        uint32_t Sum(){};
        int Count(){};
        char* Window(){};
        uint8_t* Removed(){};
        adler32 Write(char *){};
        adler32 Rollin(char *){};
        adler32 Rollout(){};

        // Declaring IO File IO Functions
        virtual std::tuple<std::ifstream&, std::string, int> Open(std::string input) = 0;
        virtual int Chunks(uint64_t filesize) = 0;

        virtual vector<Table> BuildSigTable(std::ifstream& infile) = 0;
        virtual Indexes BuildIndexes(vector<Table> signatures) = 0;
        virtual int Seek(Indexes idx, uint32_t wk, char b[1024]) = 0;
        virtual Bytes block(int index, char literalMatches[256]) = 0;
        virtual SyncClass::Delta IntegrityCheck(vector<Table> sig, SyncClass::Delta matches) = 0;
        virtual void Add(int index, Bytes b) = 0;
        virtual SyncClass::Delta DeltaFunc(vector<Table> sig, std::ifstream& reader) = 0;
        std::string Strong(char* block){};
        typedef map<int, Bytes> Delta;
        
};

class MyFactory {
    public:
        
        static shared_ptr<MyBaseClass> CreateInstance(std::string name);
};

#endif // MYBASECLASS_H