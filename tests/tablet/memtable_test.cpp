#include "tests_main.hpp"
#include "tablet/memtable.h"
#include <string.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

TEST_CASE( "Memtable class is being tested", "[]" )
{
    DummyDB::MemTable mem_table;
    std::vector< std::pair<DummyDB::Key,DummyDB::Value> > table;
    table.push_back( std::pair<DummyDB::Key,DummyDB::Value>(
        DummyDB::Key("Teranova"), DummyDB::Value("This is going to be a long night")
    ));

    SECTION( "Putting a single value and getting it back" ) {
        DummyDB::Key key = table[0].first;
        DummyDB::Value value = table[0].second;

        // Add a single key/value pair
        mem_table.set(key,value);

        // Get back the same value for this key
        DummyDB::ResultValue res = mem_table.get(key);
        REQUIRE( res.status == true );
        REQUIRE( res.value == value );
    }

    SECTION( "Putting 1000 values and making sure it is sorted" ) {
        srand (time(NULL));

        for (int i=0;i<1000;i++)
        {
            int j;
            std::string key_str = "";
            for (j=0;j<rand()%35;j++) {
                key_str.push_back('a'+rand()%27);
            }
            std::string value_str = "";
            for (j=0;j<rand()%135;j++) {
                value_str.push_back('a'+rand()%27);
            }

            mem_table.set(DummyDB::Key(key_str),DummyDB::Value(value_str));
        }
        REQUIRE( mem_table.numbElements() == 1000 );
    }
}
