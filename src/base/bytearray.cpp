#include "base/bytearray.h"
#include <iostream>
#include <string.h>

namespace DummyDB
{


ByteArray::ByteArray(const void* const key, const unsigned int size)
{
    validate(size);
    copy(key,size);
}

ByteArray::~ByteArray()
{
    if (_size>0 && _key) {
        delete _key;
    }
}

void ByteArray::copy(const void* const key, const unsigned int size)
{
    _key = new char[size];
    _size = size;
    memcpy(_key, key, size);
}

void ByteArray::validate(const unsigned int size)
{
    if ( size==0 ) {
        throw new std::string("Key::Key keys must be nonempty");
        _size = 0;
    }
}


std::string ByteArray::Get()
{
    char* result = new char[_size+1];
    memcpy(result, _key, _size);
    result[_size]= 0;
    std::string result_string(result);
    delete result;
    return result_string;
}

void ByteArray::Get(char** key, unsigned int* size)
{
    *key= new char[_size];
    memcpy(*key, _key, _size);
    *size= _size;
}

} //namespace DummyDB// namespace DummyDB
