// The same class that was provided as part
// of the curses example.

#ifndef CURSESEX_MYVALUE_H
#define CURSESEX_MYVALUE_H

#include <iostream>

class MyValue
{
private:

    int cnt;

public:
    MyValue();
    ~MyValue();

    int  get();
    MyValue &operator++(int);
    MyValue &operator--(int);
    void operator=(int value);
};

#endif //CURSESEX_VALUE_H
