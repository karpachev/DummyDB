#ifndef KEY_H
#define KEY_H
#include <string>
namespace DummyDB
{


class Key
{
    public:
        static const unsigned int MAX_KEY_SIZE = 1024;

    public:
        Key(void* const key, const unsigned int size);
        Key(const char* const key);
        Key(const std::string& key);
        virtual ~Key();


        operator std::string ();
        operator const char* ();

    private:
        inline void copy(const void* const key, const unsigned int size);
        inline void validate(const int size);

    private:
        char* _key;
        unsigned int _size;
};


} // namespace DummyDB
#endif // KEY_H
