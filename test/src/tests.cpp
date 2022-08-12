#include <gtest/gtest.h>
#include "fileio.h"
#include "sync.h"
#include "adler32.h"
#include "signature.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
