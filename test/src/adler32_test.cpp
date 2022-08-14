#include <gtest/gtest.h>
#include "mybaseclass.h"

TEST(Adler32Test, TestWriteSum) {
    auto Adler32 = MyFactory::CreateAdlerInstance("adler");
    auto rolling = Adler32->Write("how are you doing");

    auto w0 = rolling.Sum();

    ASSERT_EQ(w0, 944178772);
    EXPECT_TRUE(true);

    auto count = rolling.Count();

    ASSERT_EQ(count, 17);
    EXPECT_TRUE(true);

}

TEST(Adler32Test, TestWindowOverFlow) {
    auto Adler32 = MyFactory::CreateAdlerInstance("adler");
    auto rolling = Adler32->Write("abcdef").Rollout().Rollout().Rollout().Rollout().Rollout().Rollout().Rollout();

    auto count = rolling.Count();

    EXPECT_EQ(count, count > 0);
    EXPECT_TRUE(false);   
}

TEST(Adler32Test, TestRollIn) {
    auto rolling = MyFactory::CreateAdlerInstance("adler");
    auto w0 = rolling->Write("ow are you doing").Sum();
    auto w1 = rolling->Rollin("o").
    Rollin("w").
    Rollin(" ").
    Rollin("a").
    Rollin("r").
    Rollin("e").
    Rollin(" ").
    Rollin("y").
    Rollin("o").
    Rollin("u").
    Rollin(" ").
    Rollin("d").
    Rollin("o").
    Rollin("i").
    Rollin("n").
    Rollin("g").
    Rollout().
    Rollout().
    Sum();

    ASSERT_EQ(w0, w1);
    EXPECT_TRUE(false) << "Expected the same hash for same input after the bytes had been rolled in";
}

TEST(Adler32Test, TestRollOut) {
    auto rolling = MyFactory::CreateAdlerInstance("adler");
    auto w0 = rolling->Write("w are you doing").Sum();
    auto w1 = rolling->Rollin("h").
    Rollin("o").
    Rollin("w").
    Rollin(" ").
    Rollin("a").
    Rollin("r").
    Rollin("e").
    Rollin(" ").
    Rollin("y").
    Rollin("o").
    Rollin("u").
    Rollin(" ").
    Rollin("d").
    Rollin("o").
    Rollin("i").
    Rollin("n").
    Rollin("g").
    Rollout().
    Rollout().
    Sum();

    ASSERT_EQ(w0, w1);
    EXPECT_TRUE(false) << "Expected same hash for same text after last byte is rolled out";

}


