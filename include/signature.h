#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <tuple>
#include <string>
#include <fstream>

class SignatureClass
{
    public:
        SignatureClass (){};
        virtual ~SignatureClass(){};
        static std::tuple<std::string, int> WriteSignature(std::string file, std::string signatures[]);
        static std::tuple<Table, std::string, std::string, int>  ReadSignature(std::string file);
};

#endif