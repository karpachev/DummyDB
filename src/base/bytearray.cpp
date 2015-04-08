#include "base/bytearray.h"
#include <iostream>
#include <string.h>

namespace DummyDB
{


void ByteArray::init() {
    _data = boost::shared_ptr<ByteArraySharedData>( new ByteArraySharedData );
}

ByteArray::~ByteArray()
{
}

void ByteArray::copy(const void* const key, const unsigned int size)
{
    _data->_buffer = new char[size];
    _data->_size = size;
    memcpy(_data->_buffer, key, size);
}

void ByteArray::validate(const unsigned int size)
{
    if ( size==0 ) {
        throw new std::string("Key::Key keys must be nonempty");
    }
}


std::string ByteArray::toString() const
{
    char* result = new char[_data->_size+1];
    memcpy(result, _data->_buffer, _data->_size);
    result[_data->_size]= 0;
    std::string result_string(result);
    delete result;
    return result_string;
}

void ByteArray::rawBuffer(char** key, unsigned int* size) const
{
    *key= new char[_data->_size];
    memcpy(*key, _data->_buffer, _data->_size);
    *size= _data->_size;
}

} //namespace DummyDB// namespace DummyDB
