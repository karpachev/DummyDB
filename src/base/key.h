#ifndef KEY_H
#define KEY_H
#include "bytearray.h"
#include <string>
namespace DummyDB
{


class Key : public ByteArray
{
    public:
        static const unsigned int MAX_KEY_SIZE = 1024;

    public:
        Key(void* const key, const unsigned int size);
        Key(const char* const key);
        Key(const std::string& key);


        operator std::string ();

    private:
        void validate(const unsigned int size);

    private:
};


} // namespace DummyDB
#endif // KEY_H
