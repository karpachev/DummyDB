#ifndef BYTEARRAY_H
#define BYTEARRAY_H
namespace DummyDB
{

class ByteArray
{
    public:
        ByteArray(const void* const key, const unsigned int size);
        virtual ~ByteArray();

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
