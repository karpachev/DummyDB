#include "base/bytearray.h"
#include <iostream>
#include <string.h>

namespace DummyDB
{


ByteArray::ByteArray(const void* const key, const unsigned int size)
{
    init();
    validate(size);
    copy(key,size);
}

ByteArray::ByteArray(const ByteArray& other)
{
    _data = other._data;
    _data->IncRef();
}

ByteArray& ByteArray::operator=(const ByteArray& other)
{
    _data = other._data;
    _data->IncRef();

    return *this;
}

void ByteArray::init() {
    _data = new ByteArraySharedData;
    _data->IncRef();
}

ByteArray::~ByteArray()
{
    _data->DecRef();
}

void ByteArray::copy(const void* const key, const unsigned int size)
{
    _data->_key = new char[size];
    _data->_size = size;
    memcpy(_data->_key, key, size);
}

void ByteArray::validate(const unsigned int size)
{
    if ( size==0 ) {
        _data->DecRef();
        throw new std::string("Key::Key keys must be nonempty");
    }
}


std::string ByteArray::Get()
{
    char* result = new char[_data->_size+1];
    memcpy(result, _data->_key, _data->_size);
    result[_data->_size]= 0;
    std::string result_string(result);
    delete result;
    return result_string;
}

void ByteArray::Get(char** key, unsigned int* size)
{
    *key= new char[_data->_size];
    memcpy(*key, _data->_key, _data->_size);
    *size= _data->_size;
}

} //namespace DummyDB// namespace DummyDB
