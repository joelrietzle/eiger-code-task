#include <gtest/gtest.h>
#include "mybaseclass.h"

TEST(Adler32Test, TestWriteSum) {
    auto Adler32 = MyFactory::CreateAdlerInstance("adler");
    auto rolling = Adler32Class::Write("how are you doing");

    auto w0 = Adler32Class::Sum(rolling);

    ASSERT_EQ(w0, 944178772);
    EXPECT_TRUE(true);

    auto count = rolling.Count();

    ASSERT_EQ(count, 17);
    EXPECT_TRUE(true);

}

// To improve this testing function and do it correctly. Method chaining needs to be implemented.
TEST(Adler32Test, TestWindowOverFlow) {
    auto Adler32 = MyFactory::CreateAdlerInstance("adler");
    auto rolling = Adler32Class::Write("abcdef").RollOut().RollOut().RollOut().RollOut().RollOut().RollOut().RollOut();

    auto count = Adler32Class::Count();
    EXPECT_EQ(count, 8);
    EXPECT_TRUE(true);   
}

// To improve this testing function and do it correctly. Method chaining needs to be implemented.
TEST(Adler32Test, TestRollIn) {
    auto rolling = MyFactory::CreateAdlerInstance("adler");
    auto w0 = rolling->Write("ow are you doing");
    auto w1 = rolling->Sum(w0);
    auto w2 = rolling->Rollin("o").
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
    RollOut().
    RollOut().
    Sum(w0);


    ASSERT_EQ(w1, w2);
    EXPECT_TRUE(false) << "Expected the same hash for same input after the bytes had been rolled in";
}

// To improve this testing function and do it correctly. Method chaining needs to be implemented.
TEST(Adler32Test, TestRollOut) {
    auto rolling = MyFactory::CreateAdlerInstance("adler");
    auto w0 = rolling->Write("w are you doing");
    auto w1 = rolling->Sum(w0);
    auto w2 = rolling->Rollin("h").
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
    RollOut().
    RollOut().
    Sum(w0);

    ASSERT_EQ(w1, w2);
    EXPECT_TRUE(false) << "Expected same hash for same text after last byte is rolled out";

}


