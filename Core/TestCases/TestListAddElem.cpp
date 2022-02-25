//
// Created by Tharindu B on 1/25/2022.
//

#include "TestListAddElem.h"
#include "DefFileReader.h"
#include "ScriptReader.h"
#include "MetaData.h"
#include "ExecutionContext.h"
#include "MemMan.h"
#include "EntityList.h"
#include "Int.h"
#include "Node.h"


TestCaseExecutionResult TestListAddElem::Execute(TestCaseArgument *arg) {

    TestCaseExecutionResult res;
    int id = 0;
    DefFileReader dfr;
    MetaData *pMD = dfr.Read(arg->scriptsFolder + _MSTR(testAddElem/Defs.txt));
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

    if (list1->size() != 4) {
        res.succ = false;
        res.message = _MSTR(Result list size is incorrect);
        return res;
    }

    list1->SeekToEnd();
    PInt lastInt = (PInt) list1->GetCurrElem();

    if (4 != lastInt->GetValue()) {
        res.succ = false;
        res.message = _MSTR(Add element failed number 4 is not included in the list);
        return res;
    }

    res.succ = true;
    res.message = EMPTY_STRING;
    return res;


}