#include <string>
#include <cstdint>
#include <istream>
#include "spencoding.h"
#include "mybaseclass.h"
#include "sync.h"
#include "signature.h"
#include <tuple>

using namespace std;
using namespace sp;


std::tuple<std::string, int> SignatureClass::WriteSignature(std::string file, std::string signatures[]) {

    std::string error;
    
    if ((signatures->length() == 0)) {
        error = "No signatures to write";
        std::tuple<string, int> tuple(error, 1);
        return tuple;
    }

        //Open file
        ofstream f;
        f.open(file, std::ifstream::in);

        if (!f)
        {
            error = "error opening or creating file";
            std::tuple<string, int> tuple(error, 1);
            return tuple;
        }

        // Encode
        Base64Encoding encoder;
        string enc = encoder.encode(signatures);

        //Write to file
        f << enc;

         // Close file
        f.close();
        std::tuple<string, int> tuple(enc, 0);
        return tuple;    
}

std::tuple<Table, std::string, std::string, int> SignatureClass::ReadSignature(string file) {
    ifstream f;
    f.open(file, std::ifstream::in);
    string error;
    Table table;

    if (!f)
    {
        cout << "error opening file" << endl;
        error = "error opening file";
        std::tuple<Table, std::string, std::string, int> tuple(table, error, error, 1);
        return tuple;
    }

    f.close();
    string signatures[2];
    
    // Decode
    Base64Encoding decoder;
    string dec0 = decoder.decode(signatures[0]);
    string dec1 = decoder.decode(signatures[1]);

    if (dec0 == "0")
    {
        error = "decoding failed";
        std::tuple<Table, std::string, std::string, int> tuple(table, error, error,  1);
        return tuple;
    }

    if (dec1 == "0")
    {
        error = "decoding failed";
        std::tuple<Table, std::string, std::string, int> tuple(table, error, error,  1);
        return tuple;
    }
    
    std::tuple<Table, std::string, std::string, int> tuple(table, dec0, dec1, 1);
    return tuple;
}


//THIS FILE WAS DIFFICULT TO WRITE AS THERE'S NO SUITABLE ENCODER AND DECODER FOR THIS PURPOSE. Encoding and decoding strings only are obviously not the correct solution.