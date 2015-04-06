#ifndef BYTEARRAY_H
#define BYTEARRAY_H
#include <string>
namespace DummyDB
{

class ByteArray
{
    public:
        ByteArray(const void* const key, const unsigned int size);
        virtual ~ByteArray();

        std::string Get();
        void Get(char** key, unsigned int* size);

    protected:
        virtual void validate(const unsigned int size);

    private:
        inline void copy(const void* const key, const unsigned int size);

    protected:
        char* _key;
        unsigned int _size;
};

} // namespace DummyDB
#endif // BYTEARRAY_H
