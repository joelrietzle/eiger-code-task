#include "sync.h"
#include "mybaseclass.h"
#include "fileio.h"
#include <tuple>
#include <cstdint>


int main()
{
    uint64_t blockSize = 1 << 4;

    auto io = MyFactory::CreateFileIOInstance("fileio");
    auto sync = MyFactory::CreateSyncInstance("sync");
    auto adler = MyFactory::CreateAdlerInstance("adler");
    SyncClass::Delta delta;

    auto v1 = io->Open("/Users/joelrietz/eiger-code-task/test.txt", blockSize);
    auto getError1 = std::get<2>(v1);

    if (getError1 == 0) {
        cout << "Failed opening test.txt" << endl;
    }

    auto v2 = io->Open("/Users/joelrietz/eiger-code-task/test2.txt", blockSize);
    auto getError2 = std::get<2>(v2);

    if (getError2 == 0) {
        cout << "Failed opening test2.txt" << endl;
    }

    auto &v3 = std::get<0>(v1);
    if (v3.fail())
    {
        cout << "FILE FAILED" << endl;
    }

    auto sig = SyncClass::BuildSigTable(std::get<0>(v1)); // Error in this function when supplying it with the tuple from v1 (ifstream& infile). Causes segmentation fault.
    sync->DeltaFunc(sig, std::get<0>(v2));

    return 0;
}
