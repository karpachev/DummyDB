#ifndef MEMTABLE_H
#define MEMTABLE_H
#include "base/key.h"
#include "base/value.h"
#include "base/result.h"
#include <vector>
namespace DummyDB
{

class MemTable
{
    public:
        MemTable();
        virtual ~MemTable();

        Result<Value>   add(const Key& key, const Value& value);
        Result<Value>   remove(const Key&);

        Result<Value>   get(const Key& ) const;
        Result< std::vector<Value> >
                        prefixSearch(const Key& ) const;

    protected:
    private:
};

} // namespace DummyDB
#endif // MEMTABLE_H
