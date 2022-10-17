//
//  main.cpp
//  FlexibleComputerLanguage
//
//  Created by Dileepa Jayathilaka on 5/8/18.
//  Copyright (c) 2018 Dileepa Jayathilaka. All rights reserved.
//
// VERSION 2

#include <iostream>
#include "TestCaseExecuter.h"
#include "TestCaseBase.h"
#include "Tests.h"

//using namespace rapidjson;
//using json = nlohmann::json;
//
//INITIALIZE_EASYLOGGINGPP


int main(int argc, const char * argv[])
{

    std::cout << "Started\n";
    //Tests tt;
    //tt.RunTest5();

    TestCaseArgument *targ = new TestCaseArgument();
    targ->scriptsFolder = "../Core/TestCases/files/";

    TestCaseExecuter testCaseExecuter;
    testCaseExecuter.ExecuteAllTestCases(targ);

    return 0;
}
