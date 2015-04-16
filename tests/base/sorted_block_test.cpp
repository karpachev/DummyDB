#include "tests_main.hpp"
#include "base/sorted_block.h"
#include "base/result.h"
#include <string.h>
#include <stdio.h>
#include <time.h>


TEST_CASE( "SortedBlock class is being tested", "" ) {
    const int NUM_TEST = 10;
    const std::string prefix = "vasil";

    DummyDB::SortedBlock block;
    srand (time(NULL));
    for (int i=0;i<NUM_TEST;)
    {
        int j;
        std::string key_str = rand()%2?prefix:"";
        for (j=0;j<rand()%50;j++) {
            key_str.push_back( (rand()%2?'a':'A')+rand()%26);
        }
        std::string value_str = "";
        for (j=0;j<rand()%135+20;j++) {
            value_str.push_back( (rand()%2?'a':'A')+rand()%26);
        }
        DummyDB::Key key(key_str);
        DummyDB::Value value(value_str);

        DummyDB::Result<DummyDB::Value> result = block.get(key);
        if (result.status==false) {
            block.set(key,value);
            i++;
        }
    }
    block.toStdout();

    SECTION( "Do a prefix search" ) {
        DummyDB::Result<DummyDB::SortedBlock> result = block.prefixSearch(DummyDB::Key("vasil"));
        REQUIRE( result.status == true );
        printf("===\r\n");
        result.value.toStdout();

        DummyDB::SortedBlock& keyvalue_block = result.value;
        for (unsigned int i=0;i<keyvalue_block.size();i++) {
            REQUIRE(  (DummyDB::Key(prefix) |= keyvalue_block[i].first)==true );
            if (i!=0) {
                REQUIRE( keyvalue_block[i-1].first < keyvalue_block[i].first );
            }
        }
    }

}
