#include "binutils.h"

template<> void binutils::write<std::string>(std::ostream &out, const std::string &x)
{
    binutils::write(out, x.size());
    out.write(x.c_str(), x.size());
}

template<> void binutils::read<std::string>(std::istream &in, std::string &out)
{
    size_t sz;
    binutils::read(in, sz);
    char *str = new char[sz];
    in.read(str, sz);
    out.resize(sz);
    for (int i = 0; i < sz; ++i)
        out[i] = str[i];
    delete []str;
}
