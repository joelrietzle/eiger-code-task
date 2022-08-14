#include "mybaseclass.h"
#include "sha1.h"
#include "sync.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using std::ifstream;

bool strongCalc = false;

std::string Strong(char* block) {
    SHA1 sha1;
    auto strong = sha1;
    strong.update(block);
    strongCalc = true;
    return strong.final();
}


// Calc and return weak adler32 checksum
uint32_t weak(char* block) {
    auto weak = MyFactory::CreateAdlerInstance("adler");
    auto write = weak->Write(block).Sum();
    
}

// Return new calculated range position in block diffs
Bytes SyncClass::block(int index, char literalMatches[256]) {
    auto s = MyFactory::CreateSyncInstance("sync");
    Bytes bytes;
    bytes.Start = index * s->sync.blockSize;
    bytes.Offset = (index * s->sync.blockSize) + s->sync.blockSize;
    memcpy(bytes.Lit, literalMatches, sizeof(literalMatches));
    return {bytes};
}

// Fil signature from blocks uing
// Weak + Strong hash table

vector<Table> SyncClass::BuildSigTable(std::ifstream& infile) {


    Table table;
    auto s = MyFactory::CreateSyncInstance("sync");
    char * block = {}; 
    vector<Table> signatures = {};
    
    infile.seekg(0, infile.end);
    long size = infile.tellg();
    infile.seekg(0);

    if (infile) {
        infile.read(block, size);

        if (infile)
        {
            // Weak and strong checksum
            auto Weak = weak(block);
            auto Strong = SyncClass::Strong(block);

            // Keep signatures while it's getting written
            Table table;
            std::memcpy(&table.Weak, &Weak, sizeof(Weak));
            std::memcpy(&table.Strong, &Strong, sizeof(Strong));
            memcpy(&signatures, &table, sizeof(table));
            cout << "all chunks read successfully";
        }
        else {
            cout << "error: only" << infile.gcount() << "could be read";
            infile.close();
        }

    }

    return signatures;
}

// Fill table's indexes to match block position and return indexes:
// {weak strong} = 0, {weak, strong} = 1
Indexes SyncClass::BuildIndexes(vector<Table> signatures) {
    Indexes indexes;
    Table table;
    auto weak = table.Weak;
    auto strong = table.Strong;
    map<uint32_t ,string> strongMap;
    map<int, string>::iterator it;
    // Keep signatures in memory while getting processed
    for (const auto& [key, val] : signatures) {
        auto keyValue = indexes.index.find(key);
        auto value = it->second;
        if (key == weak)
        {
            auto strongValue = strongMap.emplace(std::make_pair(key, value));
            
        }

    }

    return indexes;
}

int SyncClass::SearchByValue(std::string name, Indexes index) {
     map <uint32_t, map <string, int> >::iterator outerit;
     for (outerit = index.index.begin(); outerit != index.index.end(); outerit++)
     {
        auto nameFound = outerit->second.find(name);
        auto keyFound = outerit->first;
        return keyFound;
     }
}

// Based on weak + string map searching for block position
// in  indexes and return block number or -1 if not found

int SyncClass::Seek(Indexes idx, uint32_t wk, char b[1024]) {
    Indexes subfield;
    int key = 0;
    std::string value = 0;
    
    auto s = MyFactory::CreateSyncInstance("sync");
    auto found = idx.index.contains(wk);
    if (found) {
        auto st = SyncClass::Strong(b); // Calculate strong hash until weak found
        strongCalc = true;
        if (strongCalc)
        {
            strongCalc = false;
            int keyFound = SyncClass::SearchByValue(st, subfield);
            return keyFound; //TODO FIX ADD subFieldArr
        }
    }
    return -1;
}

SyncClass::Delta SyncClass::IntegrityCheck(std::vector<Table> sig, SyncClass::Delta matches) {
    auto sync = MyFactory::CreateSyncInstance("sync");
    int i = 0;
    for (auto it = std::begin(sig);it != std::end(sig); it++) {
        auto contains = matches.contains(i);
        if (contains) {
            matches[i] = Bytes{.Missing = true, .Start = i * sync->sync.blockSize, .Offset = (i * sync->sync.blockSize) + sync->sync.blockSize};
        }
        i++;
    }
    return matches;
}


SyncClass::Delta SyncClass::DeltaFunc(std::vector<Table> sig, std::ifstream& reader) {
    // Weak checksum adler32
    auto weak = MyFactory::CreateAdlerInstance("adler");
    
    // Delta matches. Initializing an empty delta map
    SyncClass::Delta delta;

    auto s = MyFactory::CreateSyncInstance("sync");
    // Indexes for block position
    auto indexes = s->BuildIndexes(sig);

    char tmpLitMatches[1024];
    char byte = 0;
    // Keep tracking the changes
    bool stop = false;
    while(stop)
    {
        reader.get(byte);

        if (reader.eof()) {
            break;
        }

        // Add new character to checksum;
        weak->Adler32.Rollin(&byte);
        // We keep moving forward if data is not ready
        if (weak->Adler32.Count() < s->sync.blockSize) {
            continue;
        }

        // Start moving window over data
        // If written bytes overflow current size and no match found
        if (weak->Adler32.Count() > s->sync.blockSize) {
            // Subtract initial byte to shift << the bytes left
            weak->Adler32.Rollout();
            auto removed = weak->Adler32.Removed();
            // Store literal matches
            memcpy(tmpLitMatches, removed, sizeof(removed));
        }

        // Calculate checksum based on rolling hash
        // Check if the weak and strong match in checksum's position based signatures
        int index = s->Seek(indexes, weak->Adler32.Sum(), weak->Adler32.Window());
        std::map<std::string, int>::iterator it;
        if (index != 0) {
                // Generate new block with calculated range positions for diffing 
                auto newBlock = s->block(index, tmpLitMatches);
                
                delta.emplace(index, newBlock);
        }


        
    }

    delta = s->IntegrityCheck(sig, delta);
    return delta;

}