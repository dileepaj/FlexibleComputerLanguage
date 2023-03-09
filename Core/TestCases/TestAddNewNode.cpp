//
// Created by Erandika Ovitigala on 2/27/2023.
//

#include "TestAddNewNode.h"
#include "DefFileReader.h"
#include "ScriptReader.h"
#include "MetaData.h"
#include "ExecutionContext.h"
#include "MemMan.h"
#include "Node.h"
#include "OTPParser.h"
#include "ResultGenerator.h"
#include "Int.h"
#include "EntityList.h"

TestCaseExecutionResult TestAddNewNode::Execute(TestCaseArgument *arg) {

    TestCaseExecutionResult res;
    int id = 0;
    DefFileReader dfr;
    MetaData *pMD = dfr.Read(arg->scriptsFolder + _MSTR(testAddNodeNew/Defs.txt));
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
    ec.map_Var["RESULT"] = pRESULT;
    op.p_ETL->Execute(&ec);

    std::string result = ResultGenerator::CreateResult(pRESULT);
    std::cout << result;

    res.succ = true;
    res.message = EMPTY_STRING;
    return res;

}

