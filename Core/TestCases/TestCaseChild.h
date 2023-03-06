//
// Created by Erandika Ovitigala on 2/28/2023.
//

#ifndef FLEXIBLECOMPUTERLANGUAGE_TESTCASECHILD_H
#define FLEXIBLECOMPUTERLANGUAGE_TESTCASECHILD_H


#include "TestCaseBase.h"

class TestCaseChild : public TestCaseBase {
public:
    virtual TestCaseExecutionResult Execute(TestCaseArgument *arg);
};


#endif //FLEXIBLECOMPUTERLANGUAGE_TESTCASECHILD_H
