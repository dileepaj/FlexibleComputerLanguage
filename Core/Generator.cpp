//
// Created by User on 1/6/2022.
//

#include "Generator.h"
#include "Utils.h"
#include "MemMan.h"
#include "Int.h"
#include "ExecutionContext.h"
#include "Strings.h"
#include "Bool.h"

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

//Generate integer variable
PInt Generator::GenerateInteger(MSTRING name,MINT value,ExecutionContext* pContext) {
    PInt pIntRes;
    MemoryManager::Inst.CreateObject(&pIntRes);
    pIntRes->SetValue(value);
    pContext->map_Var[name]=(PENTITY)pIntRes;
    return pIntRes;
}
//Generate string variable
PString Generator::GenerateString(MSTRING name, MSTRING value, ExecutionContext *pContext) {
    PString pStringRes;
    MemoryManager::Inst.CreateObject(&pStringRes);
    pStringRes->SetValue(value);
    pContext->map_Var[name]=(PENTITY)pStringRes;
    return pStringRes;
}

//Generate Node variable
//Shared data

PNODE Generator::GenerateNode(MSTRING name, ExecutionContext *pContext) {
    PNODE  pNodeRes = MemoryManager::Inst.CreateNode(nodeId++);
    pContext->map_Var[name]=(PENTITY)pNodeRes;
    return pNodeRes;
}

PBool  Generator::GenerateBool(MSTRING name, MBOOL value, ExecutionContext *pContext) {
    PBool pBoolRes;
    MemoryManager::Inst.CreateObject(&pBoolRes);
    pBoolRes->SetValue(value);
    pContext->map_Var[name]=(PENTITY)pBoolRes;
    return pBoolRes;
}


