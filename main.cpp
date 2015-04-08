#include <iostream>
#include "base/key.h"
#include "boost/shared_ptr.hpp"

using namespace std;

class A {
public:
    A() { cout<<"A()\r\n";}
    A(const A& other) { cout<<"A(A)\r\n";}
    A operator= (const A& other) { cout<<"operator= (A)\r\n"; return *this;}
    ~A() { cout<<"~A()\r\n";}

    int i;

};

A f()
{
    A a;
    a.i = 10;
    return a;
}

int main()
{
    A b( f() );
    //A c(b);
    cout << b.i;
    return 0;

    DummyDB::Key key("vasil");
    boost::shared_ptr<DummyDB::Key> p( new DummyDB::Key("vasil1") );
    boost::shared_ptr<DummyDB::Key> p1 = p;
    cout << p1->toString();
    return 0;
}
