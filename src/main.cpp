#include "eigercodetask/sync.h"
#include "eigercodetask/myfactory.h"
#include "eigercodetask/mybaseclass.h"
#include "eigercodetask/fileio.h"
#include <tuple>
#include <cstdint>


int main()
{
    uint8_t blockSize = 1 << 4;

    auto io = MyFactory::CreateInstance("fileio");
    auto sync = MyFactory::CreateInstance("sync");
    auto adler = MyFactory::CreateInstance("adler");
    SyncClass::Delta delta;

    auto v1 = io->Open("test1.txt");
    
    auto getError1 = std::get<2>(v1);

    if (getError1 == 0) {
        cout << "Failed opening test.txt" << endl;
    }

    auto v2 = io->Open("test2.txt");

    auto getError2 = std::get<2>(v2);

    if (getError2 == 0) {
        cout << "Failed opening test2.txt" << endl;
    }

    auto sig = sync->BuildSigTable(std::get<0>(v1));
    sync->DeltaFunc(sig, std::get<0>(v2));
}
