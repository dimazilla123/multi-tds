#ifndef BINUTILS_H
#define BINUTILS_H

#include <iostream>

namespace binutils
{
    template<typename T>
    void write(std::ostream &out, T x)
    {
        out.write((char*)(&x), sizeof(T));
    }
    
    template<typename T>
    void read(std::istream &in, T &out)
    {
        in.read((char*)&out, sizeof(T));
    }
}


#endif