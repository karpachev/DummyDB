#ifndef BYTEARRAY_H
#define BYTEARRAY_H
#include <string>
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
            public:
                ByteArraySharedData() {
                    _key = NULL;
                    _size = 0;
                    _ref_count = 0;
                }
                ~ByteArraySharedData() {
                    if(_key) delete _key;
                }


                /// the location and size of the data
                char* _key;
                unsigned int _size;

                /// the number of
                int _ref_count;

            public:
                void IncRef() {
                    _ref_count++;
                }
                void DecRef() {
                    _ref_count--;
                    if (_ref_count<=0) {
                        delete this;
                    }
                }
        };

        ByteArraySharedData* _data;
};

} // namespace DummyDB
#endif // BYTEARRAY_H
