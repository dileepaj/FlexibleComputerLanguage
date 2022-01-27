//
// Created by Isini Dananjana on 1/26/2022.
//

#include "TestListReverse.h"
#include <DefFileReader.h>
#include <ScriptReader.h>
#include "MetaData.h"
#include "ExecutionContext.h"
#include "Node.h"
#include "EntityList.h"
#include "Int.h"

void TestListReverse::TestRunListReverse(){
    int id=0;
    DefFileReader dfr;
    // CAUTION: This file path is hardcoded and can cause crashes. You have been warned!
    MetaData *pMD = dfr.Read("../Core/TestCases/files/testReverse/Defs.txt");
    ScriptReader sr;
    ScriptReaderOutput op;
    //Read Query to string
    std::ifstream queryFile(pMD->s_RuleFileName);
    std::string query = "";
    std::string qline = "";
    while (getline(queryFile, qline))
    {
        query += qline;
        query += "\n";
    }


    bool bSucc = sr.ProcessScript(pMD, op, query);
    if (!bSucc)
    {
        std::wcout << "\nFailed to read script\n";
    }
    ExecutionContext ec;
    ec.p_mapFunctions = &op.map_Functions;
    ec.p_MD = pMD;
    Node *pRESULT = MemoryManager::Inst.CreateNode(++id);
    PENTITYLIST list1;
    MemoryManager::Inst.CreateObject(&list1);

    PInt val1 = new Int();
    val1 ->SetValue(1);
    PInt val2 = new Int();
    val2 ->SetValue(2);
    PInt val3 = new Int();
    val3 ->SetValue(3);

    list1->push_back(val1);
    list1->push_back(val2) ;
    list1->push_back(val3);

    ec.map_Var["RESULT"] = pRESULT;
    ec.map_Var["LIST"] = list1;

    op.p_ETL->Execute(&ec);
    pRESULT->GetAggregatedValue();
    std::cout<<pRESULT->GetAggregatedValue();
}

