#ifndef SORTEDBLOCK_H
#define SORTEDBLOCK_H
#include "base/key.h"
#include "base/value.h"
#include "base/result.h"
#include <vector>
namespace DummyDB
{

/**
  * Class that keeps a sorted block of key/value pairs.
  * Inserts are linear, but searches are fast logarithmic.
  */
class SortedBlock
{
    public:
        SortedBlock();
        virtual ~SortedBlock();

        Result<Value>   set(const Key& key, const Value& value);
        Result<Value>   remove(const Key&);

        Result<Value>   get(const Key& ) const;
        Result<SortedBlock>
                        prefixSearch(const Key& ) const;

        /// Return the number of <key,value> pairs
        unsigned int    size() const { return block.size(); }
        /// Return the number of bytes used for all the <key,value> pairs
        unsigned int    sizeInBytes() const { return block_size; }
        std::pair<Key,Value>
                        operator[] (unsigned int i) const {return block[i];}

        /// Printout the table to the stdout.. Mostly for debuggin
        void            toStdout();
    protected:
        /// Find the index of Key, or -1 otherwise
        Result< std::vector<int> >
                        indexOf(const Key&, bool (*compare)(const Key&, const Key&) ) const;
        int
                        indexOfSplit(const Key&, int index_min, int index_max, bool lower_range) const;

    private:
        /**
          * The key sorted list of values. Vector is appropriate
          * since it allows for fast searches (including prefix searches). The
          * inserts are inefficient (relative to a map implementation)
          */
        std::vector< std::pair<Key,Value> >
                        block;
        /// The total size in bytes of the block key/value vector
        unsigned int    block_size;
};

} // namespace DummyDB
#endif // SORTEDBLOCK_H
