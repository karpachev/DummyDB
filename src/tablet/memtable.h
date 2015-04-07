#ifndef MEMTABLE_H
#define MEMTABLE_H
#include "base/key.h"
#include "base/value.h"
namespace DummyDB
{

class MemTable
{
    public:
        MemTable();
        virtual ~MemTable();

        void Add(const Key& key, const Value& value);
    protected:
    private:
};

} // namespace DummyDB
#endif // MEMTABLE_H
