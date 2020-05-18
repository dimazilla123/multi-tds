#ifndef BINUTILS_H
#define BINUTILS_H

#include <iostream>

namespace binutils
{
    template<typename T> void write(std::ostream &out, const T &x);
    template<> void write<std::string>(std::ostream &out, const std::string &x);
    
    template<typename T>
    void write(std::ostream &out, const T &x)
    {
        out.write((char*)(&x), sizeof(T));
    }
    
    template<typename T> void read(std::istream &in, T &out);
    template<> void read<std::string>(std::istream &in, std::string &out);
    template<typename T>
    void read(std::istream &in, T &out)
    {
        in.read((char*)&out, sizeof(T));
    }
}


#endif