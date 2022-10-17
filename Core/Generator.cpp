//
// Created by User on 1/6/2022.
//

#include "Generator.h"
#include "Utils.h"
#include "MemMan.h"
#include "Int.h"
#include "ExecutionContext.h"
#include "String.h"
#include "Bool.h"
#include "Node.h"


Generator::Generator() {
    ul_Type=ENTITY_TYPE_GENERATOR;
}
Generator::~Generator()  {

}

void Generator::Destroy() {

}

MSTRING Generator::ToString() {
#ifdef ISWIDECHAR
    wchar_t buff[100];
    wsprintf(buff, L"%x", this);
    return MSTRING(buff);
#else
    char buff[100];
    sprintf(buff, "%p", this);
    return MSTRING(buff);
#endif
}

Generator* Generator::GetCopy()
{
    Generator* newGen = new Generator();
    return newGen;
}



//Generate integer
PInt Generator::GenerateInteger(MULONG initialValue) {
    PInt pIntRes;
    MemoryManager::Inst.CreateObject(&pIntRes);
    pIntRes->SetValue(initialValue);
    return pIntRes;

}
//Generate string variable
PString Generator::GenerateString(MSTRING initialValue) {
    PString pStringRes;
    MemoryManager::Inst.CreateObject(&pStringRes);
    pStringRes->SetValue(initialValue);
    return  pStringRes;
}


//Generate Node variable
//Shared data

PNODE Generator::GenerateNode(MSTRING initVal,MSTRING initLVal, MSTRING initRVal,MSTRING initCusVal) {
    PNODE  pNodeRes = MemoryManager::Inst.CreateNode(nodeId++);

    pNodeRes->SetValue((PMCHAR)initVal.c_str());
    pNodeRes->SetLValue((PMCHAR)initLVal.c_str());
    pNodeRes->SetRValue((PMCHAR)initRVal.c_str());
    pNodeRes->SetCustomString((PMCHAR)initCusVal.c_str());

    return pNodeRes;
}

PBool  Generator::GenerateBool(MBOOL initialValue) {
    PBool pBoolRes;
    MemoryManager::Inst.CreateObject(&pBoolRes);
    pBoolRes->SetValue(initialValue);
    return pBoolRes;
}


