#include "key.h"
#include <iostream>
#include <string.h>
namespace DummyDB
{


Key::Key(void* const key, const unsigned int size)
{
    validate(size);
    copy(key,size);
}

Key::Key(const char* const key)
{
    int size = strlen(key);
    validate(size);
    copy(key,size);
}

Key::Key(const std::string& key)
{
    unsigned int size = key.length();
    validate(size);
    copy(key.c_str(),size);
}

void Key::validate(const int size)
{
    if ( size<1 ) {
        throw new std::string("Key::Key keys must be nonempty");
        _size = 0;
    }

    if ( size>Key::MAX_KEY_SIZE ) {
        throw new std::string("Key::Key Keys cannot exceed (maximum number bytes)");
        _size = 0;
    }
}

void Key::copy(const void* const key, const unsigned int size)
{
    _key = new char[size];
    _size = size;
    memcpy(_key, key, size);
}

Key::~Key()
{
    if (_size) {
        delete _key;
    }
}



} // namespace DummyDB
