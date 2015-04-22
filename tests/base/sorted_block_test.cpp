#include "tests_main.hpp"
#include "base/sorted_block.h"
#include "base/result.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

int
generate_random_block(DummyDB::SortedBlock& block,
                        const int& NUM_KEYS,
                        const std::string& prefix )
{
    int   number_keys_with_prefix= 0;

    for (int i=0;i<NUM_KEYS;)
    {
        int j;
        std::string key_str=rand()%2?prefix:"";
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
            if (DummyDB::Key(prefix)|=key) {
                number_keys_with_prefix ++;
            }
        }
    }

    return number_keys_with_prefix;
}


TEST_CASE( "SortedBlock class is being tested", "" ) {

    SECTION( "Prefix search is tested " ) {
        const int NUM_TEST = 20000;

        for (int i_test=0;i_test<NUM_TEST;i_test++)
        {
            int NUM_KEYS = 5000;//rand()%5000;
            std::string prefix;// = "ARMANDO";
            for (int j=0;j<rand()%135+20;j++) {
                prefix.push_back( (rand()%2?'a':'A')+rand()%26);
            }
            int   number_keys_with_prefix= 0;
            srand (time(NULL));

            DummyDB::SortedBlock block;
            number_keys_with_prefix= generate_random_block(block,NUM_KEYS,prefix);
            //block.toStdout();

            DummyDB::Result<DummyDB::SortedBlock> result = block.prefixSearch(DummyDB::Key(prefix));
            REQUIRE( result.status == true );
            //printf("===\r\n"); result.value.toStdout();

            DummyDB::SortedBlock& keyvalue_block = result.value;
            REQUIRE(number_keys_with_prefix==keyvalue_block.size());
            for (unsigned int i=0;i<keyvalue_block.size();i++) {
                REQUIRE(  (DummyDB::Key(prefix) |= keyvalue_block[i].first)==true );
                if (i!=0) {
                    REQUIRE( keyvalue_block[i-1].first < keyvalue_block[i].first );
                }
                DummyDB::Result<DummyDB::Value> orig_value = block.get(keyvalue_block[i].first);
                REQUIRE( orig_value.status );
                REQUIRE( orig_value.value==keyvalue_block[i].second );
            }
        }
    }
}
