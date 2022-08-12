#include <gtest/gtest.h>
#include "sync.h"
#include "mybaseclass.h"
#include "signature.h"
#include <istream>
#include <fstream>
#include <string>
#include <tuple>

TEST(SignatureTest, TestSignatureReadWrite) {
    Table table;
    std::tie(table.Weak, table.Strong) = std::make_tuple(uint32_t(0000), std::string("abc123"));
    std::string signatures[2];
    signatures[0] = table.Weak;
    signatures[1] = table.Strong;
    SignatureClass::WriteSignature("signature.bin", signatures);
    cout << "Error";
    auto out = SignatureClass::ReadSignature("signature.bin");
    ASSERT_EQ(signatures[0], std::get<1>(out));
    ASSERT_TRUE(true) << "Expected written signatures equal to out signatures[0]";
    ASSERT_EQ(signatures[1], std::get<1>(out));
    ASSERT_TRUE(true) << "Expected written signatures equal to out signatures[1]";


}

TEST(SignatureTest, TestSignatureBadWrite) {
    Table table;
    std::string signatures[2];
    signatures[0] = table.Weak;
    signatures[1] = table.Strong;
    
    auto error = SignatureClass::WriteSignature("signature.bin", signatures);

    ASSERT_EQ(std::get<1>(error), 1);
    ASSERT_TRUE(true) << "Expected error with empty signatures to write";

}

TEST(SignatureTest, TestSignatureBadFileWrite) {
    Table table;
    std::string signatures[2];
    signatures[0] = table.Weak;
    signatures[1] = table.Strong;

    auto error = SignatureClass::WriteSignature("notexists.bin", signatures);
    
    ASSERT_EQ(std::get<1>(error), 1);
    ASSERT_TRUE(true) << "Expected error with invalid file to write";
    
}

TEST(SignatureTest, TestSignatureBadFileRead) {
    auto error = SignatureClass::ReadSignature("notexists.bin");

    ASSERT_EQ(std::get<2>(error), 1);
    ASSERT_TRUE(true) << "Expected error with invalid file to read"; 
}

TEST(SignatureTest, TestSignatureBadDataRead) {
    std::string file = "invalid.bin";

    // Performed writing operations
    std::fstream f (file, std::ios::binary);
    f.write("I am an invalid file", 22);
    auto error = SignatureClass::ReadSignature(file);
    
    ASSERT_EQ(std::get<2>(error), 1);
    ASSERT_TRUE(true) << "Expected error with invalid file content";
}