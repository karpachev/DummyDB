#ifndef SSTABLE_H
#define SSTABLE_H
#include "tablet/memtable.h"
namespace DummyDB
{

class SSTable
{
    public:
        /// Create SSTable from MemTable
        SSTable(const MemTable& );
        /// load SSTable from file
        SSTable(const std::string& file);
        virtual ~SSTable();

        Value&      search(const Key& ) const;
        std::vector<Value>
                    prefixSearch(const Key& ) const;


    protected:
    private:
};

} // namespace DummyDB
#endif // SSTABLE_H
