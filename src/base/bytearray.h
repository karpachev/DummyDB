#ifndef BYTEARRAY_H
#define BYTEARRAY_H
#include <string>
#include <boost/shared_ptr.hpp>
namespace DummyDB
{


class ByteArray
{
    public:
        ByteArray(const void* const key, const unsigned int size){
            init();
            validate(size);
            copy(key,size);
        }
        ByteArray(const ByteArray& other) {
            _data = other._data;
        }
        ByteArray& operator= (const ByteArray& other) {
            _data = other._data;
            return *this;
        }
        virtual ~ByteArray();

        std::string toString() const;
        operator std::string() const {
            return toString();
        }
        int bufferSize() const { return _data->_size; }
        void rawBuffer(char** key, unsigned int* size) const;

        bool operator == (const ByteArray& other) const;
        bool operator > (const ByteArray& other) const;
        bool operator < (const ByteArray& other) const;
    protected:
        virtual bool validate(const unsigned int size) {
            return true;
        }

    private:
        void copy(const void* const key, const unsigned int size);
        void init();

    protected:
        struct ByteArraySharedData
        {
                /// the location and size of the data
                char* _buffer;
                unsigned int _size;

                ByteArraySharedData() {
                    _buffer = NULL;
                    _size = 0;
                }
        };

        boost::shared_ptr<ByteArraySharedData> _data;
};

} // namespace DummyDB
#endif // BYTEARRAY_H
