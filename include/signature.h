#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <fstream>
#include <tuple>
#include <string>

class SignatureClass
{
    public:
        SignatureClass (){};
        virtual ~SignatureClass(){};
        static std::tuple<std::string, int> WriteSignature(std::string file, std::string signatures[1024]);
        static std::tuple<Table, std::string, int>  ReadSignature(std::string file);
};

#endif