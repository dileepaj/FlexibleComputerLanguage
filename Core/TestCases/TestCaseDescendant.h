//
// Created by Erandika Ovitigala on 3/6/2023.
//

#ifndef FLEXIBLECOMPUTERLANGUAGE_TESTCASEDESCENDANT_H
#define FLEXIBLECOMPUTERLANGUAGE_TESTCASEDESCENDANT_H


#include "TestCaseBase.h"

class TestCaseDescendant : public TestCaseBase{
public:
    virtual TestCaseExecutionResult Execute(TestCaseArgument *arg);
};


#endif //FLEXIBLECOMPUTERLANGUAGE_TESTCASEDESCENDANT_H
