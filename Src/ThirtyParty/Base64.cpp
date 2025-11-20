#include "Base64.h"
#include <vector>

using namespace std;

namespace{
    const char* tbl = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
}
//teste
namespace Base64{
    string encode(const string& in){
        string out;
        int val = 0;
        int valb = -6;

        for (uint8_t c: in)
        {
            val = (val<<8) + c; //convertendo caracter individual para bit
            valb  = valb + 8; //posição onde esta os caracteres -- valb += 8
            while (valb >= 0)
            {
                out.push_back(tbl[val>>valb] & 0x3F);
                valb -= 6; //valb = valb - 6
            }
            
        }
        if (valb > -6)
        {
            out.push_back(tbl[((val<<8)>>(valb+8)) & 0x3F]);
        }
        while (out.size() % 4)
        {
            out.push_back('=');
        }
        return out;
    }

    string decode(const string& in){
        vector<int> T(256, -1);

        for (int i = 0; i < 64; i++)
        {
            T[(unsigned char)tbl[i]]=i;
        }
        string out;

        int val = 0;
        int valb = -8;
        for (unsigned char c : in)
        {
            if(T[c]==-1) break;

            val = (val<<6) + T[c];
            valb += 6;
            if (valb >= 0)
            {
                out.push_back(char((val>>valb) & 0xFF));
                valb -= 8;
            }
            
        }
        return out;
    }
}