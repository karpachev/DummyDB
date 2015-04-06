#include "bytearray.h"
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


} // namespace DummyDB
