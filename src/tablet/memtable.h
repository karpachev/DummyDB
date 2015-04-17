#ifndef MEMTABLE_H
#define MEMTABLE_H
#include "base/sorted_block.h"
namespace DummyDB
{

class MemTable : public SortedBlock
{
    public:
        MemTable();
        virtual ~MemTable();

    protected:
    private:

};

} // namespace DummyDB
#endif // MEMTABLE_H
