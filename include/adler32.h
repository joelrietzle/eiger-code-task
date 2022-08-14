#ifndef ADLER32_H
#define ADLER32_H
#include <cstdint>
#include <fstream>

struct adler32 {
    char window[256];
    int count;
    uint8_t old;
    uint16_t a,b;
    uint32_t Sum(adler32 Adler32){};
    int Count(){};
    char* Window(){};
    uint8_t Removed(){};
    adler32 Write(char*){};
    adler32 Rollin(char *){};
    adler32 RollOut(){};
};

class Adler32Class
{
    public:
        // Declaring Adler32 Functions and Struct
        Adler32Class(){};
        virtual ~Adler32Class(){};
        adler32 Adler32;
        static uint32_t Sum(adler32 Adler32);
        static int Count();
        static char* Window();
        static uint8_t Removed();
        static adler32 Write(char*);
        static adler32 Rollin(char *);
        static adler32 Rollout();
};

#endif