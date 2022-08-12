#include <string>
#include <cstdint>
#include <fstream>
#include "spencoding.h"
#include "mybaseclass.h"
#include "myfactory.h"
#include "sync.h"
#include "signature.h"
#include <tuple>

using namespace std;
using namespace sp;


std::tuple<std::string, int> SignatureClass::WriteSignature(std::string file, std::string signatures[1024]) {

    std::string error;
    if (sizeof(signatures == 0)) {
        printf("No signatures to write");
        error = "No signatures to write";
        std::tuple<string, int> tuple(error, 1);
        return tuple;
    }

        //Create file 
        ofstream f(file);

        if (!f)
        {
            error = "error opening or creating file";
            std::tuple<string, int> tuple(error, 1);
            return tuple;
        }

        // Close file
        f.close();

        // Encode
        Base64Encoding encoder;
        string enc = encoder.encode(signatures);


        std::tuple<string, int> tuple(enc, 0);
        return tuple;
    
}

std::tuple<Table, std::string, int> SignatureClass::ReadSignature(string file) {
    ifstream f;
    f.open(file);
    string error;
    Table table;

    if (!f)
    {
        cout << "error opening file" << endl;
        error = "error opening file";
        std::tuple<Table, std::string, int> tuple(table, error, 1);
        return tuple;
    }

    f.close();
    string signatures;
    string read[2] = {signatures};
    

    // Decode
    Base64Encoding decoder;
    string dec = decoder.decode(signatures);

    if (dec == "0")
    {
        error = "decoding failed";
        std::tuple<Table, std::string, int> tuple(table, error, 1);
        return tuple;
    }

    std::tuple<Table, std::string, int> tuple(table, dec, 1);
    return tuple;

}


//THIS FILE WAS DIFFICULT TO WRITE AS THERE'S NO SUITABLE ENCODER AND DECODER FOR THIS PURPOSE. Encoding and decoding strings only are obviously not the correct solution.