//
// Created by Youssef on 16/05/2020.
//

#include "AssignmentStatement.h"

const string &AssignmentStatement::getVariableName() const {
    return variableName;
}

const string &AssignmentStatement::getValueExpression() const {
    return valueExpression;
}
