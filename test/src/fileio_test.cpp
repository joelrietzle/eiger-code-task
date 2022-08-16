#include <gtest/gtest.h>
#include "mybaseclass.h"
#include "fileio.h"
#include <tuple>

TEST(FileIOTest, TestInvalidChunkSize)
{
    auto IO = MyFactory::CreateFileIOInstance("fileio");
    uint64_t blockSize = 1 << 8;
    auto openFile = IO->Open("/Users/joelrietz/eiger-code-task/test.txt", blockSize);
    auto getError = std::get<1>(openFile);

    ASSERT_EQ(getError, "At least 2 chunks are required");
    EXPECT_TRUE(true) << "At least 2 chunks are required";
}

TEST(FileIOTest, TestFileOpen)
{
    auto IO = MyFactory::CreateFileIOInstance("fileio");
    uint64_t blockSize = 1 << 4;
    auto openFile = IO->Open("invalid.txt", blockSize);
    auto getError = std::get<1>(openFile);

    ASSERT_EQ(getError, "File failed to open");
    EXPECT_TRUE(true) << "File failed to open";
}

TEST(FileIOTest, TestFileChunks)
{
    auto IO = MyFactory::CreateFileIOInstance("fileio");
    uint64_t blockSize = 1 << 4;
    auto openFile = IO->Open("/Users/joelrietz/eiger-code-task/test.txt", blockSize);
    auto chunks = FileIOClass::Chunks(uint64_t(87), uint64_t(16));

    ASSERT_EQ(chunks, 6);
    EXPECT_TRUE(true) << "Expected 6 as result for int(math.Ceil(float64(87) / float64(16)))";
} 