//
// Created by TharinduB on 1/12/2022.
//

#include "TestNewObjectGenerator.h"
#include <string>
#include "DefFileReader.h"
#include "ScriptReader.h"
#include "MetaData.h"
#include "ExecutionTemplateList.h"
#include "ExecutionContext.h"
#include "Node.h"
#include "MemMan.h"
#include "CommonIncludes.h"
//#include "OTPParser.h"
#include "LogJsonParser.h"
#include "ResultGenerator.h"
#include "iostream"
#include "Generator.h"

void TestNewObjectGenerator::TestNewInt() {
    int id=0;
    DefFileReader dfr;
    // CAUTION: This file path is hardcoded and can cause crashes. You have been warned!
    MetaData *pMD = dfr.Read("E:\\Tracified\\FlexibleComputerLanguage\\Core\\TestCases\\files\\testNewKeyWord\\NewInteger\\Defs.txt");
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
    PGEN newGenerator = new Generator();

    ec.map_Var["RESULT"] = pRESULT;
    ec.map_Var[pMD->s_NewKeyword]=newGenerator;
    op.p_ETL->Execute(&ec);
    pRESULT->GetAggregatedValue();
    std::cout<<pRESULT->GetAggregatedValue();

}
void TestNewObjectGenerator::TestNewString(){

    int id = 0;
    DefFileReader dfr;
    // CAUTION: This file path is hardcoded and can cause crashes. You have been warned!
    MetaData *pMD = dfr.Read("E:\\Tracified\\FlexibleComputerLanguage\\Core\\TestCases\\files\\testNewKeyWord\\NewString\\Defs.txt");
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
    PGEN newGenerator = new Generator();

    ec.map_Var["RESULT"] = pRESULT;
    ec.map_Var[pMD->s_NewKeyword]=newGenerator;
    op.p_ETL->Execute(&ec);
    pRESULT->GetAggregatedValue();
    std::cout<<pRESULT->GetAggregatedValue();

}

void TestNewObjectGenerator::TestNewNode() {

    int id = 0;
    DefFileReader dfr;
    // CAUTION: This file path is hardcoded and can cause crashes. You have been warned!
    MetaData *pMD = dfr.Read("E:\\Tracified\\FlexibleComputerLanguage\\Core\\TestCases\\files\\testNewKeyWord\\NewNode\\Defs.txt");
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
    PGEN newGenerator = new Generator();

    ec.map_Var["RESULT"] = pRESULT;
    ec.map_Var[pMD->s_NewKeyword]=newGenerator;
    op.p_ETL->Execute(&ec);
    pRESULT->GetAggregatedValue();
    std::cout<<pRESULT->GetAggregatedValue();

}

void TestNewObjectGenerator::TestNewBool() {

    int id = 0;
    DefFileReader dfr;
    // CAUTION: This file path is hardcoded and can cause crashes. You have been warned!
    MetaData *pMD = dfr.Read("E:\\Tracified\\FlexibleComputerLanguage\\Core\\TestCases\\files\\testNewKeyWord\\NewBool\\Defs.txt");
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
    PGEN newGenerator = new Generator();

    ec.map_Var["RESULT"] = pRESULT;
    ec.map_Var[pMD->s_NewKeyword]=newGenerator;
    op.p_ETL->Execute(&ec);
    pRESULT->GetAggregatedValue();
    std::cout<<pRESULT->GetAggregatedValue();

}
