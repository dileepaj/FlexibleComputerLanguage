//
// Created by Erandika Ovitigala on 2/28/2023.
//

#ifndef FLEXIBLECOMPUTERLANGUAGE_TESTCASEANCESTOR_H
#define FLEXIBLECOMPUTERLANGUAGE_TESTCASEANCESTOR_H


#include "TestCaseBase.h"

class TestCaseAncestor : public TestCaseBase{
public:
    virtual TestCaseExecutionResult Execute(TestCaseArgument *arg);
};


#endif //FLEXIBLECOMPUTERLANGUAGE_TESTCASEANCESTOR_H
