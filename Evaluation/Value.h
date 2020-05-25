#ifndef SIMPLE_INTERPRETER_VALUE_H
#define SIMPLE_INTERPRETER_VALUE_H

#include <string>
#include <ostream>

using namespace std;

class Value {
private:
    bool isBool;
    bool isInt;
    bool isDouble;
    bool boolValue;
    int intValue;
    double doubleValue;

public:
    Value(bool value);

    Value(int value);

    Value(double value);

    bool isBoolValue() const;

    bool isIntValue() const;

    bool isDoubleValue() const;

    bool getBoolValue() const;

    int getIntValue() const;

    double getDoubleValue() const;

    string toString() const;

    friend ostream &operator<<(ostream &os, const Value &value);

    bool operator<(const Value &rhs) const;

    bool operator>(const Value &rhs) const;

    bool operator<=(const Value &rhs) const;

    bool operator>=(const Value &rhs) const;

};


#endif //SIMPLE_INTERPRETER_VALUE_H
