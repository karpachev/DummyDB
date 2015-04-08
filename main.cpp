#include <iostream>
#include "base/key.h"
#include "boost/shared_ptr.hpp"

using namespace std;

int main()
{
    DummyDB::Key key("vasil");
    boost::shared_ptr<DummyDB::Key> p( new DummyDB::Key("vasil1") );
    boost::shared_ptr<DummyDB::Key> p1 = p;
    cout << p1->toString();
    return 0;
}
