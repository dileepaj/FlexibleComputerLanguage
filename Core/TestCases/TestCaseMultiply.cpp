//
// Created by Erandika Roshani on 1/17/2023.
//

#include "DefFileReader.h"
#include "ScriptReader.h"
#include "MetaData.h"
#include "ExecutionContext.h"
#include "MemMan.h"
#include "Node.h"
#include "OTPParser.h"
#include "ResultGenerator.h"
#include "TestCaseMultiply.h"

TestCaseExecutionResult TestCaseMultiply::Execute(TestCaseArgument *arg) {
    TestCaseExecutionResult res;
    int id = 0;
    DefFileReader dfr;
    MetaData *pMD = dfr.Read(arg->scriptsFolder + _MSTR(testMultiply/Defs.txt));
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

    Node *pY = MemoryManager::Inst.CreateNode(++id);

    //Parse text to NodeTree
    std::string line;
    std::string jsonline;
    std::ifstream jsonfile("../Core/TestCases/files/testMultiply/Json.txt");
    if (jsonfile.is_open()) {
        getline(jsonfile, line);
        jsonline = line;
        jsonfile.close();
    }
    OTPParser jsonParser;
    Node *root = jsonParser.TDPJSONToNodeTree(jsonline);
    std::string s = "52";

    root->SetValue((char *) s.c_str());
    ec.map_Var["X"] = root;
    ec.map_Var["Y"] = pY;
    ec.map_Var["RESULT"] = pRESULT;

    if (root->IsNull()) {
        res.succ = false;
        res.message = "Json parsing to node tree failed";
        return res;
    }

    op.p_ETL->Execute(&ec);

    std::string result = ResultGenerator::CreateResult(pRESULT);
    std::cout << result;

    res.succ = true;
    res.message = EMPTY_STRING;
    return res;
}




