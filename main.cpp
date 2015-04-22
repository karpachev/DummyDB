#include <iostream>
#include "base/key.h"
#include "boost/shared_ptr.hpp"
#include "boost/scoped_array.hpp"
#include <string.h>
#include <stdio.h>
using namespace std;



int main()
{
    boost::scoped_array<char> p( new char[10] );
    memcpy(p.get(), "vasil", 6);
    printf("Test: %s\r\n", p.get());
    return 0;
}
