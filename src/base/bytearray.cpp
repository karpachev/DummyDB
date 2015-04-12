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

std::string ByteArray::toString() const
{
    char* result = new char[_data->_size+1];
    if (_data->_buffer) {
        memcpy(result, _data->_buffer, _data->_size);
    }
    result[_data->_size]= 0;
    std::string result_as_string(result);
    delete result;
    return result_as_string;
}

void ByteArray::rawBuffer(char** key, unsigned int* size) const
{
    *key= new char[_data->_size];
    if (_data->_buffer) {
        memcpy(*key, _data->_buffer, _data->_size);
    }
    *size= _data->_size;
}

bool ByteArray::operator == (const ByteArray& other) const {
    // when different sizes -> cannot be equal
    if (_data->_size != other._data->_size) {
        return false;
    }
    // After here -> they are equal
    // If both are empty -> they are equal
    if (_data->_size==0) {
        return true;
    }
    // They are equal only when they match byte by byte
    return memcmp(_data->_buffer, other._data->_buffer, _data->_size)==0;
}

bool ByteArray::operator |= (const ByteArray& other) const {
    // when *this is longer than other -> cannot be prefix
    if (_data->_size > other._data->_size) {
        return false;
    }
    // The empty bytearray is prefix of everything
    if (_data->_size==0) {
        return true;
    }
    // They are equal only when they match byte by byte
    return memcmp(_data->_buffer, other._data->_buffer, _data->_size)==0;
}

bool ByteArray::operator > (const ByteArray& other) const {
    // "aaa" > "aa"
    // "aba" > "aa"
    if ( _data->_size > other._data->_size ) {
        return memcmp(_data->_buffer, other._data->_buffer, other._data->_size)>=0;
    }
    // Here _data->_size <= other._data->_size
    // "aba" > "abac"
    return memcmp(_data->_buffer, other._data->_buffer, _data->_size)>0;
}

bool ByteArray::operator < (const ByteArray& other) const {
    // "aa" < "aaa"
    // "aa" < "aba"
    if ( _data->_size < other._data->_size ) {
        return memcmp(_data->_buffer, other._data->_buffer, _data->_size)<=0;
    }
    // Here _data->_size >= other._data->_size
    // "aba" > "abac"
    return memcmp(_data->_buffer, other._data->_buffer, other._data->_size)<0;
}

} //namespace DummyDB// namespace DummyDB
