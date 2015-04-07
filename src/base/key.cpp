#include "base/key.h"
#include <iostream>
#include <string.h>
namespace DummyDB
{


Key::Key(void* const key, const unsigned int size) :
    ByteArray(key,size)
{

}

Key::Key(const char* const key) :
    ByteArray(key,strlen(key))
{
}

Key::Key(const std::string& key) :
    ByteArray(key.c_str(), key.length())
{
}

void Key::validate(const unsigned int size)
{
    ByteArray::validate(size);

    if ( size>Key::MAX_KEY_SIZE ) {
        _data->DecRef();
        throw new std::string("Key::Key Keys cannot exceed (maximum number bytes)");
    }
}





} // namespace DummyDB
