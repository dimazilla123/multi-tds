#ifndef OBJECT_MANAGER
#define OBJECT_MANAGER

#include <cstdlib>
#include <unordered_map>

template<typename T>
class ObjectManager
{
public:
    ObjectManager(size_t sz) : size(sz)
    {
    }
    ~ObjectManager()
    {

    }
private:
    size_t size;

};

#endif