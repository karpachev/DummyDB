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
    Result< std::vector<int> > index = indexOf(key,equal_keys);
    if (index.status==false) {
        // not found - emptyr result
        return Result<Value>();
    }
    const int& index_found= index.value[0];

    Result<Value> result(block[index_found].second);
    block.erase( block.begin()+index_found );
    return result;
}

Result<Value>
SortedBlock::get(const Key& key) const
{
    Result< std::vector<int> > index = indexOf(key,equal_keys);
    if (index.status==false) {
        // not found - emptyr result
        return Result<Value>();
    }
    // index.value[0] is the index of the found entry
    const int& index_found= index.value[0];
    return Result<Value>(block[index_found].second);
}




/**
  * Perform a binary sarch to find a matching entry
  * in the sorted map_table.
  * @return Result.status==false - not found
  *         Result.value[0] - the index of the found entry
  *         Result.value[1] - the max index of the last step
  *         Result.value[2] - the min index of the last step
  */
Result< std::vector<int> >
SortedBlock::indexOf(const Key& key, bool (*compare)(const Key& a, const Key& b) ) const
{
    Result< std::vector<int> > result;
    int min_index =0,
                    max_index = block.size()-1;
    if (max_index==0) {
        return result; // Not found: table still empty
    }

    while(min_index<=max_index) {
        int middle_index = (min_index+max_index)/2;

        if ( compare(key, block[middle_index].first) ) {
            // Found
            result.status = true;
            result.value.push_back(middle_index);
            result.value.push_back(max_index);
            result.value.push_back(min_index);
            return result;
        }

        if ( key < block[middle_index].first ) {
            max_index= middle_index-1;
        } else {
            min_index= middle_index+1;
        }
    }

    // Binary search not successful
    return result;
}

Result<SortedBlock>
SortedBlock::prefixSearch(const Key& key) const
{
    Result<SortedBlock> result;
    Result< std::vector<int> > index = indexOf(key, prefix_equal_keys);
    if (index.status==false) {
        // not found - empty result
        return result;
    }
    // index.value[0] is the index of a matching key
    // index.value[1] is the index of a bigger key
    // index.value[2] is the index of a lesser key
    const int& index_found = index.value[0];
    const int& index_max = index.value[1];
    const int& index_min = index.value[2];

    const int& low_bound = indexOfSplit(key, index_min, index_found, true);
    const int& high_bound = indexOfSplit(key, index_found, index_max, false);

    result.status=true;
    result.value.block = std::vector< std::pair<Key,Value> >(
                block.begin()+low_bound,
                block.begin()+high_bound+1
    );
    return result;
}

int
SortedBlock::indexOfSplit(const Key& key, int index_min, int index_max, bool lower_range) const
{
    do
    {
        bool min_found = key |= block[index_min].first;
        bool max_found = key |= block[index_max].first;
        if (min_found&&max_found) {
            // the whole range is of identical keys.
            if (lower_range) {
                // In the low range the split must be the first key
                return index_min;
            } else {
                // In the higher range the split must be the first key
                return index_max;
            }
        }
        if (!min_found&&!max_found) {
            // the whole range is of different keys.
            if (lower_range) {
                // In the low range the split must be the first key
                return index_max-1;
            } else {
                // In the higher range the split must be the first key
                return index_min+1;
            }
        }


        int index_middle = (index_min+index_max)/2;
        bool middle_found = key |= block[index_middle].first;

        if (min_found) {
            if(middle_found) {
                // split must in in the [index_middle,index_max]
                index_min = index_middle+1;
            } else {
                // split must in in the [index_min,index_middle)
                index_max = index_middle-1;
            }
        }

        if (max_found) {
            if(middle_found) {
                // split must in in the [index_min,index_middle)
                index_max = index_middle-1;
            } else {
                // split must in in the [index_middle,index_max]
                index_min = index_middle+1;
            }
        }

    } while (index_min<=index_max);

    return 1;
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
