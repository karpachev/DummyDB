#include "tests_main.hpp"
#include "base/sorted_block.h"
#include <string.h>
#include <stdio.h>


TEST_CASE( "SortedBlock class is being tested", "" ) {
    const int NUM_TEST = 10;
    DummyDB::SortedBlock block;
    srand (time(NULL));
    for (int i=0;i<NUM_TEST;)
    {
        int j;
        std::string key_str = rand()%2?"vasil":"";
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
    block.prefixSearch(DummyDB::Key("vasil"));

}
