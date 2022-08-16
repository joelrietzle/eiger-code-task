#include <gtest/gtest.h>
#include "mybaseclass.h"
#include "sync.h"
#include <istream>

/**
Test for matching differences
a test.txt
b test2.txt
a= i am here guys how are you doing this is a small test for chunk split and rolling hash
b= i here guys how are you doing this is a small test chunk split and rolling hash
0 = i am here guys h
1 = ow are you doing
2 = this is a small
3 =  test for chunk
4 = split and rollin
5 = g hash
Signatures:
[
	0: {768804235 5d7b9b82d3dd8c4d13a576f004318130},
	1: {828311020 eb535617e82301559e56a18993cdbe39},
	2: {763037070 f38bd8f1d59e45f4a7bdaa6311064573},
	3: {800720288 6f2fcd27d23f5e98f486ff34ad580d09},
	4: {880805423 5f19d42bfb610b9861ec0704b6467910},
	5: {489488949 3024133c176e89ed84401db125a62ed0}
]
**/

typedef map<int, Bytes> CalcDelta;

SyncClass::Delta CalculateDelta(std::string a, std::string b) {
    auto sync = MyFactory::CreateSyncInstance("sync");
    sync->sync.blockSize = 1 << 4;

    std::ifstream ifsBufferA (a, std::ifstream::in);
    std::ifstream ifsBufferB (b, std::ifstream::in);
    
    auto sig = sync->BuildSigTable(ifsBufferA);
    return sync->DeltaFunc(sig, ifsBufferB);
}

void CheckMath(CalcDelta calcdelta, map<int, std::string> expected) {
    map<int, std::string>::iterator it;
    map<int, Bytes>::iterator calcit;
    int i = 0;
    for (it = expected.begin(); it != expected.end(); it++) {
        auto expectedKeyValue = expected[it->first];
        auto deltaKeyValue = calcdelta[it->first];

        ASSERT_EQ(expectedKeyValue, deltaKeyValue.keyValue);
        EXPECT_TRUE(false);

        auto literal = calcdelta.at(i).Lit;
        auto expect = expected[i];

        ASSERT_EQ(std::string(literal), std::string(expect));
        EXPECT_TRUE(false);
        i++;
    }
}

TEST(SyncTest, TestDetectChunkChange) {
    std::string a = "i am here guys how are you doing this is a small test for chunk split and rolling hash";
    std::string b = "i here guys how are you doing this is a small test chunk split and rolling hash";
    std::string firstLine = "i here guys h";
    std::string secondLine = " this is a small test chunk ";
    map<int, std::string> expect;
    expect.emplace(std::make_pair(1, firstLine));
    expect.emplace(std::make_pair(4, secondLine));

    auto delta = CalculateDelta(a,b);
    CheckMath(delta, expect);
}

TEST(SynctTest, TestDetectChunkRemoval) {
    std::string a = "i am here guys how are you doing this is a small test for chunk split and rolling hash";
    std::string b = "ow are you doing this is a small split and rolling hash";
    auto delta = CalculateDelta(a,b);

    // Check for block 1 and block 3 removal
    ASSERT_EQ(delta[0].Missing, true);
    EXPECT_TRUE(true) << "Expected delta first and third block missing";
    ASSERT_EQ(delta[3].Missing, true);
    EXPECT_TRUE(true) << "Expected delta first and third block missing";

    // Match block missing position should be equal to expected based on block bytes size
    auto matchPositionForBlock1 = delta[0].Start == 0 && delta[0].Offset == 16;
    auto matchPositionForBlock3 = delta[3].Start == 0 && delta[3].Offset == 64;

    ASSERT_EQ(matchPositionForBlock1, true);
    EXPECT_TRUE(true) << "Expected delta range for missing block 1=0-16";

    ASSERT_EQ(matchPositionForBlock3, true);
    EXPECT_TRUE(true) << "Expected delta range for missing block 3 = 48-64";
}

TEST(SyncTest, TestDetectChunkShifted) {
    std::string o= "i am here guys how are you doing this is a small test for chunk split and rolling hash";
    std::string c = "i am here guys   how are you doing     test for chunk split and rolling hash";
    map<int, std::string> expect;
    std::string firstLine = "i am here guys  h";
    std::string secondLine = "  ";

    expect.emplace(std::make_pair(1, firstLine));
    expect.emplace(std::make_pair(3, secondLine));

    auto delta = CalculateDelta(o,c);
    CheckMath(delta, expect);
}