#include "base/value.h"
namespace DummyDB
{

Value::Value(void* const key, const unsigned int size) :
    ByteArray(key,size)
{

}

void Value::validate(const unsigned int size)
{
    ByteArray::validate(size);

    if ( size>Value::MAX_VALUE_SIZE ) {
        _data->DecRef();
        throw new std::string("Key::Key Keys cannot exceed (maximum number bytes)");
    }
}


} // namespace DummyDB
