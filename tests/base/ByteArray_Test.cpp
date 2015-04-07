#include "tests_main.hpp"
#include "base/bytearray.h"
#include <string.h>

TEST_CASE( "ByteArray class is tested", "[key/value]" ) {
    const char* keys[3]= {
        "This is a key",
        "Necessary ye contented newspaper zealously breakfast he prevailed. Melancholy middletons yet understood decisively boy law she. Answer him easily are its barton little. Oh no though mother be things simple itself. Dashwood horrible he strictly on as. Home fine in so am good body this hope.",
        "Fat son how smiling mrs natural expense anxious friends."
    };
    for (int i=0;i<3;i++) {
        DummyDB::ByteArray bytearray(keys[i],strlen(keys[i]));
        REQUIRE( bytearray.Get() == std::string(keys[i]) );
    }
    for (int i=0;i<3;i++) {
        DummyDB::ByteArray bytearray(keys[i],strlen(keys[i]));
        char* k;
        unsigned int k_size;
        bytearray.Get(&k,&k_size);
        REQUIRE( memcmp(k,keys[i],k_size)==0  );
    }
}

