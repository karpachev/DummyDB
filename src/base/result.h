#ifndef RESULT_H
#define RESULT_H
#include "base/key.h"
#include "base/value.h"
namespace DummyDB
{

template <class T>
struct Result
{
    public:
        Result() {
            status = false;
        }
        Result(const T& v, bool st = true) {
            value = v;
            status = st;
        }
        virtual ~Result() {
        }

        T       value;
        bool    status;

};

typedef Result<Value> ResultValue;
typedef Result<Key> ResultKey;

} // namespace DummyDB
#endif // RESULT_H
