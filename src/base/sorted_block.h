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
  * Inserts are inneficient, but searches are fast logarithmic.
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

        unsigned int    size() { return block.size(); }
        std::pair<Key,Value>
                        operator[] (unsigned int i){return block[i];}

        /// Printout the table to the stdout.. Mostly for debuggin
        void            toStdout();
    protected:
        /// Find the index of Key, or -1 otherwise
        Result< std::vector<int> >
                        indexOf(const Key&, bool (*compare)(const Key&, const Key&) ) const;
        int
                        indexOfSplit(const Key&, int index_min, int index_max, bool lower_range) const;

    private:
        std::vector< std::pair<Key,Value> >
                        block;
};

} // namespace DummyDB
#endif // SORTEDBLOCK_H
