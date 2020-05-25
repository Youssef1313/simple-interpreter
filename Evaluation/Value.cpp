#include "Value.h"

bool Value::isBoolValue() const {
    return isBool;
}

bool Value::isIntValue() const {
    return isInt;
}

bool Value::isDoubleValue() const {
    return isDouble;
}

bool Value::getBoolValue() const {
    return boolValue;
}

int Value::getIntValue() const {
    return intValue;
}

double Value::getDoubleValue() const {
    return doubleValue;
}

Value::Value(bool value) {
    isBool = true;
    isInt = false;
    isDouble = false;
    boolValue = value;
}

Value::Value(int value) {
    isBool = false;
    isInt = true;
    isDouble = false;
    intValue = value;
}

Value::Value(double value) {
    isBool = false;
    isInt = false;
    isDouble = true;
    doubleValue = value;
}

string Value::toString() const {
    if (isBool) return boolValue ? "true" : "false";
    return isInt ? to_string(intValue) : to_string(doubleValue);
}

ostream &operator<<(ostream &os, const Value &value) {
    return os << value.toString();
}

bool Value::operator<(const Value &rhs) const {
    double lhsValue = boolValue;
    double rhsValue = rhs.boolValue;
    if (!isBool)
        lhsValue = isInt ? intValue : doubleValue;

    if (!rhs.isBool)
        rhsValue = rhs.isInt ? rhs.intValue : rhs.doubleValue;
    return lhsValue < rhsValue;

}

bool Value::operator>(const Value &rhs) const {
    return rhs < *this;
}

bool Value::operator<=(const Value &rhs) const {
    return !(rhs < *this);
}

bool Value::operator>=(const Value &rhs) const {
    return !(*this < rhs);
}
