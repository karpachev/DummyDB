#include "base/value.h"
#include "string.h"
namespace DummyDB
{

Value::Value(const char* const str) :
            ByteArray(str,strlen(str))
{
}

bool Value::validate(const unsigned int size)
{
    if ( size>Value::MAX_VALUE_SIZE ) {
        throw new std::string("Key::Key Keys cannot exceed (maximum number bytes)");
    }

    return true;
}


} // namespace DummyDB
