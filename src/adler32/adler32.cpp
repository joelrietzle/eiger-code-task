#include "eigercodetask/mybaseclass.h"
#include "eigercodetask/myfactory.h"
#include "eigercodetask/adler32.h"
#include <cstdint>
#include <cstring>
#include <stdio.h>
#include <string>
#include <memory>
#include <valarray>


// Calculate initial checksum from byte slice
adler32 Write(std::byte data) {

    auto Adler32 = MyFactory::CreateInstance("adler");
    for (int index = 0, character = 0; index < sizeof(data) &&  character < sizeof(data); index++, character++)
    {

        Adler32->Adler32.a += uint16_t(character);
        Adler32->Adler32.b += uint16_t(sizeof(data) - index) * uint16_t(character);
        Adler32->Adler32.count++;
    }

    Adler32->Adler32.a %= M;
    Adler32->Adler32.b%= M;
    return Adler32->Adler32;
}

// Calculate and return checksum
uint32_t Sum() {
    auto Adler32 = MyFactory::CreateInstance("adler");
    // Enforece 16 bits
    // a = 920 = 0x398 (written in base 16)
    // b = 4582 = 0x11E6
    // Output = 0x11E6 << 16 + 0x398 = 0x11E60398
    return uint32_t(Adler32->Adler32.b) << 16 | uint32_t(Adler32->Adler32.a)&0xFFFFF;
}

uint8_t* Window() {auto Adler32 = MyFactory::CreateInstance("adler"); return Adler32->Adler32.window;}
int Count() {auto Adler32 = MyFactory::CreateInstance("adler"); return Adler32->Adler32.count;}
uint8_t Removed() {auto Adler32 = MyFactory::CreateInstance("adler"); return Adler32->Adler32.old;}

// Add byte to rolling checksum
adler32 Rollin(char* input)
{
    auto Adler32 = MyFactory::CreateInstance("adler");
    Adler32->Adler32.a = (Adler32->Adler32.a + uint16_t(*input)) % M;
    Adler32->Adler32.b = (Adler32->Adler32.b + Adler32->Adler32.a) %M;

    // Keep stored windows bytes while getting processed
    memcpy(Adler32->Adler32.window, input, sizeof(input));
    Adler32->Adler32.count++;
    return Adler32->Adler32;
}

// Substract byte from checksum
adler32 RollOut()
{
    auto Adler32 = MyFactory::CreateInstance("adler");
    // Checking if window is empty. Then nothing to roll out.
    if (sizeof(Adler32->Adler32.window == 0))
    {
        Adler32->Adler32.count = 0;
        return Adler32->Adler32;
    }

    Adler32->Adler32.old = Adler32->Adler32.window[0];
    Adler32->Adler32.a = (Adler32->Adler32.a - uint16_t(Adler32->Adler32.a)) %M;
    Adler32->Adler32.b = (Adler32->Adler32.b - (uint16_t(sizeof(Adler32->Adler32.window)) * uint16_t(Adler32->Adler32.old))) %M;
    memcpy(Adler32->Adler32.window, Adler32->Adler32.window,  sizeof(Adler32));
    
}