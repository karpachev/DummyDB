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

        Result<Value>   set(const Key& key, const Value& value);
        Result<Value>   remove(const Key&);

        Result<Value>   get(const Key& ) const;
        Result< std::vector<Value> >
                        prefixSearch(const Key& ) const;

        unsigned int    numbElements() { return mem_table.size(); }

        /// Printout the table to the stdout.. Mostly for debuggin
        void            toStdout();

    protected:
        /// Find the index of Key, or -1 otherwise
        int             indexOf(const Key& ) const;
    private:
        std::vector< std::pair<Key,Value> >
                        mem_table;
};

} // namespace DummyDB
#endif // MEMTABLE_H
