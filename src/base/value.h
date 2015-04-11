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
        Value(const void* const value, const unsigned int size):
            ByteArray(value,size) { }
        Value(const char* const str);
        Value(std::string str): ByteArray(str.c_str(), str.length()) { }
        Value():
            ByteArray(NULL,0) { }


    private:
        bool validate(const unsigned int size);

};

} // namespace DummyDB
#endif // VALUE_H
