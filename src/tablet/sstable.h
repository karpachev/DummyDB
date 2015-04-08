#ifndef SSTABLE_H
#define SSTABLE_H
#include "base/result.h"
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

        Result<Value>       search(const Key& ) const;
        Result< std::vector<Value> >
                            prefixScan(const Key& ) const;
        Result<Value>       remove(const Key& );


    protected:
    private:
};

} // namespace DummyDB
#endif // SSTABLE_H
