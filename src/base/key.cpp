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

bool Key::validate(const unsigned int size)
{
    if ( size==0 ) {
        throw new std::string("Key::Key Keys cannot be empty");
    }
    if ( size>Key::MAX_KEY_SIZE ) {
        throw new std::string("Key::Key Keys cannot exceed (maximum number bytes)");
    }

    return true;
}





} // namespace DummyDB
