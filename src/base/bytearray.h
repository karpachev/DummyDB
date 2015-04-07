#ifndef BYTEARRAY_H
#define BYTEARRAY_H
#include <string>
#include <boost/shared_ptr.hpp>
namespace DummyDB
{


class ByteArray
{
    public:
        ByteArray(const void* const key, const unsigned int size);
        ByteArray(const ByteArray& other);
        ByteArray& operator=(const ByteArray& other);
        virtual ~ByteArray();

        std::string Get();
        int GetSize() { return _data->_size; }
        void Get(char** key, unsigned int* size);

    protected:
        virtual void validate(const unsigned int size);

    private:
        inline void copy(const void* const key, const unsigned int size);
        inline void init();

    protected:
        struct ByteArraySharedData
        {
                /// the location and size of the data
                char* _key;
                unsigned int _size;

                ByteArraySharedData() {
                    _key = NULL;
                    _size = 0;
                }
        };

        boost::shared_ptr<ByteArraySharedData> _data;
};

} // namespace DummyDB
#endif // BYTEARRAY_H
