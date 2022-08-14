#ifndef MYBASECLASS_H
#define MYBASECLASS_H

#include "fileio.h"
#include "sync.h"
#include "adler32.h"
#include "myfactory.h"
#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <math.h>
#include <vector>
#include <tuple>
#include <memory>

class MyBaseClass 
{
    public:
        
};

class MyFactory {
    public:
        
        static std::shared_ptr<Adler32Class> CreateAdlerInstance(std::string name);
        static std::shared_ptr<FileIOClass> CreateFileIOInstance(std::string name);
        static std::shared_ptr<SyncClass> CreateSyncInstance(std::string name);        

};

#endif // MYBASECLASS_H