#ifndef SSTABLE_H
#define SSTABLE_H
#include "base/result.h"
#include "base/sorted_block.h"
#include "tablet/memtable.h"
#include <vector>
namespace DummyDB
{

class SSTable
{
    public:
        enum {
            BLOCK_SIZE = 6144
        };
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
        std::vector< boost::shared_ptr<SortedBlock> >
                            loaded_blocks;
        std::vector< Key >  index;
};

} // namespace DummyDB
#endif // SSTABLE_H
