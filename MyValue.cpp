#include "MyValue.h"

MyValue::MyValue()
{
    cnt = 0;
}

MyValue::~MyValue() {}

int MyValue::get() {
    return cnt;
}

MyValue &MyValue::operator++(int) {
    cnt++;
    return *this;
}

MyValue &MyValue::operator--(int) {
    cnt--;
    return *this;
}

void MyValue::operator=(int value) {
    cnt = value;
}
