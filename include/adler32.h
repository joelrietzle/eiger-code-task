#ifndef ADLER32_H
#define ADLER32_H
#include <cstdint>

const int M = 65521;


struct adler32 {
    uint8_t window[256];
    int count;
    uint8_t old;
    uint16_t a,b;
    uint32_t Sum(){};
    int Count(){};
    char* Window(){};
    uint8_t* Removed(){};
    adler32 Write(char *){};
    adler32 Rollin(char *){};
    adler32 Rollout(){};
};

class Adler32Class
{
    public:
        // Declaring Adler32 Functions and Struct
        Adler32Class(){};
        virtual ~Adler32Class(){};
        adler32 Adler32;
};

#endif