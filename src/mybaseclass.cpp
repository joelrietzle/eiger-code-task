#include "eigercodetask/fileio.h"
#include "eigercodetask/sync.h"
#include "eigercodetask/adler32.h"
#include "eigercodetask/myfactory.h"
#include <cstdint>
#include <stdio.h>
#include <math.h>

shared_ptr<MyBaseClass> MyFactory::CreateInstance(std::string name)
{
    Adler32Class * Adler32ClassInstance = nullptr;
    FileIOClass * FileIOClassInstance = nullptr;
    SyncClass * SyncClassInstance = nullptr;

    if(name == "fileio")
        FileIOClassInstance = new FileIOClass();
    if (name == "adler")
        Adler32ClassInstance = new Adler32Class();
    if (name == "sync")
        SyncClassInstance = new SyncClass();
    else
        return nullptr;
}