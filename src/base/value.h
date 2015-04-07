#ifndef VALUE_H
#define VALUE_H
#include "base/bytearray.h"
namespace DummyDB
{

class Value : public ByteArray
{
    public:
        static const unsigned int MAX_VALUE_SIZE = 1024*1024;

    public:
        Value(void* const key, const unsigned int size);


    private:
        void validate(const unsigned int size);

};

} // namespace DummyDB
#endif // VALUE_H
