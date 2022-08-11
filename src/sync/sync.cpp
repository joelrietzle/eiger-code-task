#include "eigercodetask/mybaseclass.h"
#include "eigercodetask/sha1.h"
#include "eigercodetask/sync.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
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
    auto weak = MyFactory::CreateInstance("adler");
    auto write = weak->Write(block).Sum();
    
}

// Return new calculated range position in block diffs
Bytes block(int index, char literalMatches[256]) {
    auto s = MyFactory::CreateInstance("sync");
    Bytes bytes;
    bytes.Start = index * s->Sync.blockSize;
    bytes.Offset = (index * s->Sync.blockSize) + s->Sync.blockSize;
    memcpy(bytes.Lit, literalMatches, sizeof(literalMatches));
    return {bytes};
}

// Fil signature from blocks uing
// Weak + Strong hash table

vector<Table> BuildSigTable(std::ifstream& infile) {


    Table table;
    auto s = MyFactory::CreateInstance("sync");
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
Indexes BuildIndexes(vector<Table> signatures) {
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

// Based on weak + string map searching for block position
// in  indexes and return block number or -1 if not found

auto Seek(Indexes idx, uint32_t wk, char b[1024]) {
    Indexes subfield;
    
    auto s = MyFactory::CreateInstance("sync");
    auto found = idx.index.contains(wk);
    subfield.index.at(wk) = idx.index.at(wk);
    if (found) {
        auto st = SyncClass::Strong(b); // Calculate strong hash until weak found
        strongCalc = true;
        if (strongCalc)
        {
            strongCalc = false;
            return subfield.index.at(wk); //TODO FIX ADD subFieldArr
        }
    }

}

SyncClass::Delta IntegrityCheck(std::vector<Table> sig, SyncClass::Delta matches) {
    auto sync = MyFactory::CreateInstance("sync");
    int i = 0;
    for (auto it = std::begin(sig);it != std::end(sig); it++) {
        auto contains = matches.contains(i);
        if (contains) {
            matches[i] = Bytes{.Missing = true, .Start = i * sync->Sync.blockSize, .Offset = (i * sync->Sync.blockSize) + sync->Sync.blockSize};
        }
        i++;
    }
    return matches;
}


SyncClass::Delta DeltaFunc(std::vector<Table> sig, std::ifstream& reader) {
    // Weak checksum adler32
    auto weak = MyFactory::CreateInstance("adler");
    
    // Delta matches. Initializing an empty delta map
    SyncClass::Delta delta;

    auto s = MyFactory::CreateInstance("sync");
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
        if (weak->Adler32.Count() < s->Sync.blockSize) {
            continue;
        }

        // Start moving window over data
        // If written bytes overflow current size and no match found
        if (weak->Adler32.Count() > s->Sync.blockSize) {
            // Subtract initial byte to shift << the bytes left
            weak->Adler32.Rollout();
            auto removed = weak->Adler32.Removed();
            // Store literal matches
            memcpy(tmpLitMatches, removed, sizeof(removed));
        }

        // Calculate checksum based on rolling hash
        // Check if the weak and strong match in checksum's position based signatures
        auto index = s->Seek(indexes, weak->Adler32.Sum(), weak->Adler32.Window());

        if (index != 0) {
                // Generate new block with calculated range positions for diffing 
                auto newBlock = s->block(index, tmpLitMatches);
                
                delta.emplace(index, newBlock);
        }


        
    }

    delta = s->IntegrityCheck(sig, delta);
    return delta;

}