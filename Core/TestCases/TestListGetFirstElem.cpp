//
// Created by Tharindu Balasooriyya on 1/24/2022.
//

#include "DefFileReader.h"
#include "ScriptReader.h"
#include "TestListGetFirstElem.h"
#include "MetaData.h"
#include "ExecutionContext.h"
#include "Node.h"
#include "EntityList.h"
#include "Int.h"

//void TestListGetFirstElem::TestListGetFirstElement() {
//    int id=0;
//    DefFileReader dfr;
//    // CAUTION: This file path is hardcoded and can cause crashes. You have been warned!
//    MetaData *pMD = dfr.Read("../Core/TestCases/files/testGetFirstElem/Defs.txt");
//    ScriptReader sr;
//    ScriptReaderOutput op;
//    //Read Query to string
//    std::ifstream queryFile(pMD->s_RuleFileName);
//    std::string query = "";
//    std::string qline = "";
//    while (getline(queryFile, qline))
//    {
//        query += qline;
//        query += "\n";
//    }
//
//
//    bool bSucc = sr.ProcessScript(pMD, op, query);
//    if (!bSucc)
//    {
//        std::wcout << "\nFailed to read script\n";
//    }
//    ExecutionContext ec;
//    ec.p_mapFunctions = &op.map_Functions;
//    ec.p_MD = pMD;
//    Node *pRESULT = MemoryManager::Inst.CreateNode(++id);
//    PENTITYLIST list1;
//    MemoryManager::Inst.CreateObject(&list1);
//    PInt val1 = new Int();
//    val1->SetValue(1);
//    PInt val2 = new Int();
//    val2->SetValue(2);
//    PInt val3 = new Int();
//    val3->SetValue(3);
//
//   list1->push_back(val1);
//   list1->push_back(val2);
//   list1->push_back(val3);
//
//    ec.map_Var["RESULT"] = pRESULT;
//    ec.map_Var["LIST1"] = list1;
//    op.p_ETL->Execute(&ec);
//    pRESULT->GetAggregatedValue();
//    std::cout<<pRESULT->GetAggregatedValue();
//}


TestCaseExecutionResult TestListGetFirstElem::Execute(TestCaseArgument *arg) {

    TestCaseExecutionResult res;
    int id = 0;
    DefFileReader dfr;
    MetaData *pMD = dfr.Read(arg->scriptsFolder + _MSTR(testGetFirstElem/Defs.txt));
    ScriptReader sr;
    ScriptReaderOutput op;
    //Read Query to string
    std::ifstream queryFile(pMD->s_RuleFileName);
    std::string query = "";
    std::string qline = "";
    while (getline(queryFile, qline)) {
        query += qline;
        query += "\n";
    }

    bool bSucc = sr.ProcessScript(pMD, op, query);
    if (!bSucc) {
        res.message = _MSTR(Failed to read script);
        res.succ = false;
        return res;
    }

    ExecutionContext ec;
    ec.p_mapFunctions = &op.map_Functions;
    ec.p_MD = pMD;
    Node *pRESULT = MemoryManager::Inst.CreateNode(++id);
    PENTITYLIST list1;
    MemoryManager::Inst.CreateObject(&list1);

    PInt val1 = new Int();
    val1->SetValue(1);
    PInt val2 = new Int();
    val2->SetValue(2);
    PInt val3 = new Int();
    val3->SetValue(3);

    list1->AddElem(val1);
    list1->AddElem(val2);
    list1->AddElem(val3);

    ec.map_Var["RESULT"] = pRESULT;
    ec.map_Var["LIST1"] = list1;


    op.p_ETL->Execute(&ec);

    PInt resultElem = (PInt)ec.map_Var["RESULTELEM"];

    if (list1->size() != 3) {
        res.succ = false;
        res.message = _MSTR(Result list size is incorrect);
        return res;
    }



    if(resultElem->GetValue() != 1){
        res.succ = false;
        res.message = _MSTR(Incorrect first element);
        return res;
    }


    res.succ = true;
    res.message = EMPTY_STRING;
    return res;


}
