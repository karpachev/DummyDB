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
        Result< std::vector<Value> >
                        prefixSearch(const Key& ) const;

        unsigned int    numbElements() { return block.size(); }

        /// Printout the table to the stdout.. Mostly for debuggin
        void            toStdout();
    protected:
        /// Find the index of Key, or -1 otherwise
        int             indexOf(const Key&, bool (*compare)(const Key&, const Key&) ) const;

    private:
        std::vector< std::pair<Key,Value> >
                        block;
};

} // namespace DummyDB
#endif // SORTEDBLOCK_H
