//
// Created by Tharindu Balasooriya on 1/25/2022.
//

#include "TestListConcat.h"
#include "DefFileReader.h"
#include "ScriptReader.h"
#include "MetaData.h"
#include "ExecutionContext.h"
#include "MemMan.h"
#include "EntityList.h"
#include "Int.h"
#include "Node.h"

TestCaseExecutionResult TestListConcat::Execute(TestCaseArgument *arg) {

    TestCaseExecutionResult res;
    int id = 0;
    DefFileReader dfr;
    MetaData *pMD = dfr.Read(arg->scriptsFolder + _MSTR(testConcatList/Defs.txt));
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

    PENTITYLIST list1;
    MemoryManager::Inst.CreateObject(&list1);
    PENTITYLIST list2;
    MemoryManager::Inst.CreateObject(&list2);

    PInt val1 = new Int();
    val1->SetValue(1);
    PInt val2 = new Int();
    val2->SetValue(2);
    PInt val3 = new Int();
    val3->SetValue(3);

    PInt val4 = new Int();
    val4->SetValue(4);
    PInt val5 = new Int();
    val5->SetValue(5);
    PInt val6 = new Int();
    val6->SetValue(6);

    list1->push_back(val1);
    list1->push_back(val2);
    list1->push_back(val3);

    list2->push_back(val4);
    list2->push_back(val5);
    list2->push_back(val6);



    ec.map_Var["LIST1"] = list1;
    ec.map_Var["LIST2"] = list2;

    op.p_ETL->Execute(&ec);

    PENTITYLIST pResultList =(PENTITYLIST) ec.map_Var["RESULT"];

    if(pResultList->size() != list1->size() + list2->size()){
        res.succ = false;
        res.message = _MSTR(Result list size is incorrect);
        return res;
    }

    res.succ = true;
    res.message = EMPTY_STRING;
    return res;


}