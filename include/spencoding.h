#ifndef SP_ENCODING_H
#define SP_ENCODING_H
#include <vector>
#include <string>

namespace sp {

typedef unsigned char byte;
typedef unsigned int uint;
class Base64Encoding {
    private:
        std::string _charset;
        std::vector<int> _invSet;
    public:
        Base64Encoding()
            :_charset("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"),
            _invSet({62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58,
                    59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5,
                    6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                    21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28,
                    29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
                    43, 44, 45, 46, 47, 48, 49, 50, 51})
        {
        }

        std::string encode(std::string text[1024]) 
        {
            std::string out;

            if (text[0] == "")
                return "";
            uint txtLength = text[0].length();
            uint encLength = calcEncodingSize(txtLength);
            out.resize(encLength, ' ');
            uint v;
            for (uint i=0, j=0; i<encLength; i+=3, j+=4) {
                v = text[j][i];
                v = i+1 < txtLength ? v << 8 | text[j+1][i+1] : v << 8;
                v = i+2 < txtLength ? v << 8 | text[j+2][i+2] : v << 8;

                out[j]   = _charset[(v >> 18) & 0x3F];
                out[j+1] = _charset[(v >> 12) & 0x3F];
                if (i+1 < txtLength) {
                    out[j+2] = _charset[(v >> 6) & 0x3F];
                } else {
                    out[j+2] = '=';
                }
                if (i+2 < txtLength) {
                    out[j+3] = _charset[v & 0x3F];
                } else {
                    out[j+3] = '=';
                }
            }
            return out;
        }
        std::string decode(std::string text) {
            std::string out;

            if (text == "")
                return "";
            uint txtLength = text.length();
            uint nEql = 0;
            for (uint i=0; i<txtLength; i++) {
                if (!isValidChar(text[i])) {
                    return 0;
                }
                if(text[i] == '=') nEql++;
            }
            uint encLength = calcDecodingSize(txtLength, nEql);
            out.resize(encLength, ' ');
            uint v;
            for (uint i=0, j=0; i<txtLength; i+=4, j+=3) {
                v = _invSet[text[i]-43];
                v = (v << 6) | _invSet[text[i+1]-43];
                v = text[i+2]=='=' ? v << 6 : (v << 6) | _invSet[text[i+2]-43];
                v = text[i+3]=='=' ? v << 6 : (v << 6) | _invSet[text[i+3]-43];

                out[j] = (v >> 16) & 0xFF;
                if (text[i+2] != '=')
                    out[j+1] = (v >> 8) & 0xFF;
                if (text[i+3] != '=')
                    out[j+2] = v & 0xFF;
            }
            
            return out;
        }
    private:
        uint calcEncodingSize(uint length) 
        {
            if(length % 3 != 0)
                length = ((length/3) + 1) *4;
            else
                length = (length /3) * 4;

            return length;
        }
        uint calcDecodingSize(uint length, uint nEqual) {
            length = (length / 4) * 3;
            length -= nEqual;
            return length;
        }
        bool isValidChar(char c) {
            if (c >= '0' && c <= '9')
                return true;
            if (c >= 'A' && c <= 'Z')
                return true;
            if (c >= 'a' && c <= 'z')
                return true;
            if (c == '+' || c == '/' || c == '=')
                return true;
                return false;
        }
    };
};
#endif