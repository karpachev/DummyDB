#include "tablet/sstable.h"
namespace DummyDB
{

SSTable::SSTable(const MemTable& mem_table)
{
    boost::shared_ptr<SortedBlock> sb(new SortedBlock);
    unsigned int current_size = 0;
    for(unsigned int i=0;i<mem_table.size();i++) {
        std::pair<Key,Value> key_value = mem_table[i];
        current_size+= key_value.first.bufferSize();
        current_size+= key_value.second.bufferSize();
        sb->set(key_value.first, key_value.second);

        if (current_size>BLOCK_SIZE) {
            this->index.push_back(key_value.first);
            this->loaded_blocks.push_back(sb);
            sb = boost::shared_ptr<SortedBlock>(new SortedBlock);
            current_size = 0;
        }
    }
}

SSTable::~SSTable()
{
    //dtor
}


} // namespace DummyDB
