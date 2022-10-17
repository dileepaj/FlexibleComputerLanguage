//
// Created by Tharindu Balasooriya on 2/3/2022.
//

#include "TestListSort.h"

#include "DefFileReader.h"
#include "ScriptReader.h"
#include "MetaData.h"
#include "ExecutionContext.h"
#include "MemMan.h"
#include "EntityList.h"
#include "Int.h"
#include "Node.h"
#include "String.h"

TestCaseExecutionResult TestListSort::Execute(TestCaseArgument *arg) {
    int id = 0;
    DefFileReader dfr;
    TestCaseExecutionResult res;


    MetaData *pMD = dfr.Read(arg->scriptsFolder + _MSTR(testListSort/Defs.txt));;
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
    PENTITYLIST list2;
    MemoryManager::Inst.CreateObject(&list2);

    PInt val1 = new Int();
    val1->SetValue(14);
    PInt val2 = new Int();
    val2->SetValue(223);
    PInt val3 = new Int();
    val3->SetValue(32);

    PInt val4 = new Int();
    val4->SetValue(41);
    PInt val5 = new Int();
    val5->SetValue(5);
    PInt val6 = new Int();
    val6->SetValue(6);

    list1->push_back(val1);
    list1->push_back(val2);
    list1->push_back(val3);

    list1->push_back(val4);
    list1->push_back(val5);
    list1->push_back(val6);

    PString sVal1 = new String();
    PString sVal2 = new String();
    PString sVal3 = new String();

    sVal1->SetValue("z");
    sVal2->SetValue("l");
    sVal3->SetValue("m");

    list2->push_back(sVal1);
    list2->push_back(sVal2);
    list2->push_back(sVal3);



    ec.map_Var["RESULT"] = pRESULT;
    ec.map_Var["LIST1"] = list1;
    ec.map_Var["LIST2"] = list2;

    op.p_ETL->Execute(&ec);


    PENTITYLIST pListASC = (PENTITYLIST)ec.map_Var["ASC_SORTED"];
    PENTITYLIST pListDSC = (PENTITYLIST)ec.map_Var["DSC_SORTED"];

    if(pListASC->size() != 6 && pListDSC->size() != 6 ){
        res.succ = false;
        res.message = _MSTR(Size of result list);
        return res;
    }


    res.succ = true;
    res.message = EMPTY_STRING;
    return res;


}
