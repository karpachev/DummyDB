#include "memtable.h"
#include <iostream>
#include <stdio.h>
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
            // the key already exists - overwrite it!
            Result<Value> result(it->second);
            it->second = value;
            result.status = true;
            return result;
        }

        if ( key < it->first ) {
            break;
        }
    }

    mem_table.insert(it, std::pair<Key,Value>(key,value));
    Result<Value>  result(value);
    result.status= true;
    return result;
}

Result<Value>
MemTable::remove(const Key& key)
{
    int index = indexOf(key);
    if (index==-1) {
        // not found - emptyr result
        return Result<Value>();
    }

    Result<Value> result(mem_table[index].second);
    mem_table.erase( mem_table.begin()+index );
    return result;
}

Result<Value>
MemTable::get(const Key& key) const
{
    int index = indexOf(key);
    if (index==-1) {
        // not found - emptyr result
        return Result<Value>();
    }

    return Result<Value>(mem_table[index].second);
}

/**
  * Perform a binary sarch to find a matching entry
  * in the sorted map_table.
  * @return -1 - not found
  *         <index> - the index of the found entry
  */
int
MemTable::indexOf(const Key& key) const
{
    int min_index =0,
                    max_index = mem_table.size()-1;
    if (max_index==0) {
        return -1; // Not found: table still empty
    }

    while(min_index<=max_index) {
        int middle_index = (min_index+max_index)/2;

        if ( key == mem_table[middle_index].first ) {
            return middle_index; // Found
        }

        if ( key < mem_table[middle_index].first ) {
            max_index= middle_index-1;
        } else {
            min_index= middle_index+1;
        }
    }

    // Binnary search not successfull
    return -1;
}

Result< std::vector<Value> >
MemTable::prefixSearch(const Key& ) const
{
    Result< std::vector<Value> > result;
    return result;
}

void
MemTable::toStdout() {
    std::vector< std::pair<Key,Value> >::iterator it;
    int i=0;
    for (it=mem_table.begin();it<mem_table.end();it++) {
        printf( "%4d: [%3d=>%3d]'%s'=>'%s'\r\n",
                i++,
                it->first.toString().size(), it->second.toString().size(),
                it->first.toString().c_str(),it->second.toString().c_str()
        );
    }
}


} // namespace DummyDB
