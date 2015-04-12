#include "sorted_block.h"
#include <stdio.h>
namespace DummyDB
{

SortedBlock::SortedBlock()
{
    //ctor
}

SortedBlock::~SortedBlock()
{
    //dtor
}

Result<Value>
SortedBlock::set(const Key& key, const Value& value)
{
    std::vector< std::pair<Key,Value> >::iterator it;
    for(it=block.begin(); it!=block.end(); it++) {
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

    block.insert(it, std::pair<Key,Value>(key,value));
    Result<Value>  result(value);
    result.status= true;
    return result;
}

bool equal_keys(const Key& a, const Key& b) {
    return a == b;
}
bool prefix_equal_keys(const Key& a, const Key& b) {
    return a |= b;
}

Result<Value>
SortedBlock::remove(const Key& key)
{
    int index = indexOf(key,equal_keys);
    if (index==-1) {
        // not found - emptyr result
        return Result<Value>();
    }

    Result<Value> result(block[index].second);
    block.erase( block.begin()+index );
    return result;
}

Result<Value>
SortedBlock::get(const Key& key) const
{
    int index = indexOf(key,equal_keys);
    if (index==-1) {
        // not found - emptyr result
        return Result<Value>();
    }

    return Result<Value>(block[index].second);
}




/**
  * Perform a binary sarch to find a matching entry
  * in the sorted map_table.
  * @return -1 - not found
  *         <index> - the index of the found entry
  */
int
SortedBlock::indexOf(const Key& key, bool (*compare)(const Key& a, const Key& b) ) const
{
    int min_index =0,
                    max_index = block.size()-1;
    if (max_index==0) {
        return -1; // Not found: table still empty
    }

    while(min_index<=max_index) {
        int middle_index = (min_index+max_index)/2;

        if ( compare(key, block[middle_index].first) ) {
            return middle_index; // Found
        }

        if ( key < block[middle_index].first ) {
            max_index= middle_index-1;
        } else {
            min_index= middle_index+1;
        }
    }

    // Binnary search not successfull
    return -1;
}

Result< std::vector<Value> >
SortedBlock::prefixSearch(const Key& key) const
{
    Result< std::vector<Value> > result;
    int index = indexOf(key,prefix_equal_keys);
    if (index==-1) {
        // not found - emptyr result
        return result;
    }

    printf("Found prefix: %d\r\n", index);
    //return Result<Value>(block[index].second);
    return result;
}

void
SortedBlock::toStdout() {
    std::vector< std::pair<Key,Value> >::iterator it;
    int i=0;
    for (it=block.begin();it<block.end();it++) {
        printf( "%4d: [%3d=>%3d]'%s'=>'%s'\r\n",
                i++,
                it->first.toString().size(), it->second.toString().size(),
                it->first.toString().c_str(),it->second.toString().c_str()
        );
    }
}

} // namespace DummyDB
