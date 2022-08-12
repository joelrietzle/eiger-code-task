#ifndef SYNC_H
#define SYNC_H
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct Table {
    uint32_t Weak;
    string Strong;
};

struct Bytes {
    int Offset;
    int Start;
    bool Missing;
    char Lit[256];
    std::string keyValue;
};

struct Indexes { map<uint32_t, map<string, int> > index;};

class SyncClass {
    public:
        SyncClass(){};
        virtual ~SyncClass(){};
        static vector<Table> BuildSigTable(std::ifstream& infile);
        static Indexes BuildIndexes(vector<Table> signatures);
        static int Seek(Indexes idx, uint32_t wk, char b[1024]);
        Bytes block(int index, char literalMatches[256]);
        typedef map<int, Bytes> Delta;
        static SyncClass::Delta IntegrityCheck(vector<Table> sig, SyncClass::Delta matches);
        static SyncClass::Delta DeltaFunc(vector<Table> sig, std::ifstream& reader);
        void Add(int index, Bytes b);
        static string Strong(char* block){};
        Table table;

};

#endif