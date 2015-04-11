#include "tests_main.hpp"
#include "base/bytearray.h"
#include <string.h>

TEST_CASE( "ByteArray class is tested", "[key/value]" ) {
    const char* keys[3]= {
        "This is a key",
        "Necessary ye contented newspaper zealously breakfast he prevailed. Melancholy middletons yet understood decisively boy law she. Answer him easily are its barton little. Oh no though mother be things simple itself. Dashwood horrible he strictly on as. Home fine in so am good body this hope.",
        "Fat son how smiling mrs natural expense anxious friends."
    };

   SECTION( "Check that 'std::string Get()' matches the original keys" ) {
        for (int i=0;i<3;i++) {
            DummyDB::ByteArray bytearray(keys[i],strlen(keys[i]));
            REQUIRE( bytearray.toString() == std::string(keys[i]) );
        }
    }

    SECTION( "Check that Get(&k,&k_size) matches the origional keys" ) {
        for (int i=0;i<3;i++) {
            DummyDB::ByteArray bytearray(keys[i],strlen(keys[i]));
            char* k;
            unsigned int k_size;
            bytearray.rawBuffer(&k,&k_size);
            REQUIRE( memcmp(k,keys[i],k_size)==0  );
        }
    }

    SECTION( "Copy constructor and operator= " ) {
        DummyDB::ByteArray p1(keys[0],strlen(keys[0]));
        DummyDB::ByteArray p2 = p1;
        DummyDB::ByteArray p3(keys[1],strlen(keys[1]));
        REQUIRE( std::string(keys[0]) == p2.toString() );
        p3 = p2;
        REQUIRE( std::string(keys[0]) == p3.toString() );
    }

    SECTION( "Check comparison operators" ) {
        DummyDB::ByteArray empty(NULL, 0);
        REQUIRE( empty == empty );
        REQUIRE( !(empty < empty) );
        REQUIRE( !(empty > empty) );

        DummyDB::ByteArray aa("aa", strlen("aa"));
        REQUIRE( !(empty == aa) );
        REQUIRE( empty < aa );
        REQUIRE( !(empty > aa) );

        DummyDB::ByteArray aaa("aaa", strlen("aaa"));
        REQUIRE( aa < aaa );
        REQUIRE( !(aa > aaa) );
        REQUIRE( aaa > aa );
        REQUIRE( !(aaa < aa) );

        DummyDB::ByteArray aba("aba", strlen("aba"));
        REQUIRE( aa < aba );
        REQUIRE( !(aa > aba) );
        REQUIRE( aaa < aba );
        REQUIRE( !(aaa > aba) );
        REQUIRE( aba > aa );
        REQUIRE( !(aba < aa) );
        REQUIRE( aba > aaa );
        REQUIRE( !(aba < aaa) );
    }
}

