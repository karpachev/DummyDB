#ifndef MEMTABLE_H
#define MEMTABLE_H
#include "base/key.h"
#include "base/value.h"
#include <vector>
namespace DummyDB
{

class MemTable
{
    public:
        MemTable();
        virtual ~MemTable();

        void        Add(const Key& key, const Value& value);
        Value&      Remove(const Key&);

        Value&      search(const Key& ) const;
        std::vector<Value>
                    prefixSearch(const Key& ) const;

    protected:
    private:
};

} // namespace DummyDB
#endif // MEMTABLE_H
