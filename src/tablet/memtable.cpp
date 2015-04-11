#include "memtable.h"
namespace DummyDB
{


MemTable::MemTable()
{
    //ctor
}

MemTable::~MemTable()
{
    //dtor
}

Result<Value>
MemTable::set(const Key& key, const Value& value)
{
    std::vector< std::pair<Key,Value> >::iterator it;
    for(it=mem_table.begin(); it!=mem_table.end(); it++) {
        if ( key == it->first ) {
            // the key already exists - cannot add it!
            Result<Value> result(it->second);
            result.status = false;
            return result;
        }

        if ( key > it->first ) {
            break;
        }
    }

    mem_table.insert(it, std::pair<Key,Value>(key,value));
    Result<Value>  result(value);
    result.status= true;
    return result;
}

Result<Value>
MemTable::remove(const Key&)
{
    Result<Value> result;
    return result;
}

Result<Value>
MemTable::get(const Key& key) const
{

    unsigned int min_index =0,
                    max_index = mem_table.size(),
                    middle_index = (min_index+max_index)/2;
    while(min_index<max_index) {
        if ( key == mem_table[middle_index].first ) {
            Result<Value> result(mem_table[middle_index].second);
            return result;
        }

        if ( key < mem_table[middle_index].first ) {
            max_index= middle_index-1;
        } else {
            min_index= middle_index+1;
        }
    }

    Result<Value> result;
    return result;
}

Result< std::vector<Value> >
MemTable::prefixSearch(const Key& ) const
{
    Result< std::vector<Value> > result;
    return result;
}


} // namespace DummyDB
