#include "fileio.h"
#include "sync.h"
#include "adler32.h"
#include "mybaseclass.h"
#include <cstdint>
#include <stdio.h>
#include <math.h>
#include <memory>

std::shared_ptr<Adler32Class> MyFactory::CreateAdlerInstance(std::string name)
{
    Adler32Class * instance = nullptr;

    if(name == "adler") {
        instance = new Adler32Class();
        return std::shared_ptr<Adler32Class>(instance);
    } 
    else
        return nullptr;
}

std::shared_ptr<FileIOClass> MyFactory::CreateFileIOInstance(std::string name)
{
    FileIOClass * instance = nullptr;

    if(name == "fileio") {
        instance = new FileIOClass();
        return std::shared_ptr<FileIOClass>(instance);
    } 
    else
        return nullptr;
}

std::shared_ptr<SyncClass> MyFactory::CreateSyncInstance(std::string name)
{
    SyncClass * instance = nullptr;

    if(name == "sync") {
        instance = new SyncClass();
        return std::shared_ptr<SyncClass>(instance);
    } 
    else
        return nullptr;
}



