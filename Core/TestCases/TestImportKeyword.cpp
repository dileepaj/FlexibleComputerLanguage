//
// Created by Tharindu Balasooriya on 3/11/2022.
//

#include "TestImportKeyword.h"
#include "DefFileReader.h"
#include "ScriptReader.h"
#include "MetaData.h"
#include "ExecutionContext.h"
#include "MemMan.h"
#include "EntityList.h"
#include "Int.h"
#include "Node.h"

TestCaseExecutionResult TestImportKeyword::Execute(TestCaseArgument *arg) {

    TestCaseExecutionResult res;
    int id = 0;
    DefFileReader dfr;
    MetaData *pMD = dfr.Read(arg->scriptsFolder + _MSTR(testImportKeyword/Defs.txt));
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
    query.erase(std::remove( query.begin(),  query.end(), ' '),query.end());

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


    std::cout<<pRESULT->GetAggregatedValue();

    if(ec.p_mapFunctions->size() == 0){
        res.succ = false;
        res.message = "IMPORT keyword not working , function loading failed";
        return res;
    }

    res.succ = true;
    res.message = EMPTY_STRING;
    return res;


}