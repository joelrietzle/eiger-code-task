#include "gtest/gtest.h"
#include "eigercodetask/mybaseclass.h"
#include <tuple>

TEST(FileIOTest, TestInvalidChunkSize)
{
    auto IO = MyFactory::CreateInstance("fileio");
    IO->io.blockSize = 1 << 8;

    auto openFile = IO->Open("../test.txt");
    
    auto getError = std::get<1>(openFile);
    ASSERT_EQ(getError, "At least 2 chunks are required");
    EXPECT_TRUE(true) << "At least 2 chunks are required";


}

TEST(FileIOTest, TestFileOpen)
{
    auto IO = MyFactory::CreateInstance("fileio");
    IO->io.blockSize = 1 << 4;

    auto openFile = IO->Open("invalid.txt");

    auto getError = std::get<1>(openFile);


    ASSERT_EQ(getError, "File failed to open");
    EXPECT_TRUE(true) << "File failed to open";
}

TEST(FileIOTest, TestFileChunks)
{
    auto IO = MyFactory::CreateInstance("fileio");
    IO->io.blockSize = 1 << 8;

    IO->Open("test.txt");
    auto chunks = IO->Chunks(87);

    ASSERT_EQ(chunks, 6);
    EXPECT_FALSE(true) << "Expected 6 as result for int(math.Ceil(float64(87) / float64(16)))";

}