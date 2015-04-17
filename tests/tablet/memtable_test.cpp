#include "tests_main.hpp"
#include "tablet/memtable.h"
#include <iostream>
#include <string.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

TEST_CASE( "Memtable class is being tested", "[]" )
{
#if 0
    const int NUM_TEST = 1000;
    DummyDB::MemTable mem_table;
    srand (time(NULL));
    for (int i=0;i<NUM_TEST;)
    {
        int j;
        std::string key_str = "";
        for (j=0;j<rand()%50;j++) {
            key_str.push_back( (rand()%2?'a':'A')+rand()%26);
        }
        std::string value_str = "";
        for (j=0;j<rand()%135+20;j++) {
            value_str.push_back( (rand()%2?'a':'A')+rand()%26);
        }
        DummyDB::Key key(key_str);
        DummyDB::Value value(value_str);

        DummyDB::Result<DummyDB::Value> result = mem_table.get(key);
        if (result.status==false) {
            mem_table.set(key,value);
            i++;
        }
    }


    SECTION( "Require that the number of elements be NUM_TEST" ) {
        REQUIRE( mem_table.numbElements() == NUM_TEST );
    }

    SECTION( "Putting a single value and getting it back" ) {
        DummyDB::Key key = "teranova";
        DummyDB::Value value = "This is going to be a long night";
        DummyDB::Value new_value = "Way to reach the moon";

        // Add a single key/value pair
        mem_table.set(key,value);

        // Get back the same value for this key
        DummyDB::ResultValue res = mem_table.get(key);
        //mem_table.toStdout();
        REQUIRE( res.status == true );
        REQUIRE( res.value == value );
        REQUIRE( mem_table.numbElements() == NUM_TEST+1 );


        // Overwrite the same key with new value
        mem_table.set(key,new_value);

        // Get back the new value for this key
        res = mem_table.get(key);
        //mem_table.toStdout();
        REQUIRE( res.status == true );
        REQUIRE( res.value == new_value );
        REQUIRE( mem_table.numbElements() == NUM_TEST+1 );

        // Remove the value for this key
        res = mem_table.remove(key);
        REQUIRE( res.status == true );
        REQUIRE( res.value == new_value );
        REQUIRE( mem_table.numbElements() == NUM_TEST );
    }
#endif // 0
}
