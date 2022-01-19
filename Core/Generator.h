//
// Created by TharinduB on 1/6/2022.
//

#ifndef FLEXIBLECOMPUTERLANGUAGE_GENERATOR_H
#define FLEXIBLECOMPUTERLANGUAGE_GENERATOR_H

#include "CommonIncludes.h"
#include "Entity.h"
#include "ExecutionContext.h"
#include "EntityList.h"
class Generator : public Entity{
public:
    Generator();
    virtual ~Generator();
    virtual  void Destroy();

    Generator* GetCopy();
    virtual MSTRING ToString();
    PInt GenerateInteger(MSTRING name,MINT value,ExecutionContext* pContext);
    PString GenerateString(MSTRING name,MSTRING value,ExecutionContext* pContext);
    PNODE  GenerateNode(MSTRING name,ExecutionContext* pContext);
    PENTITYLIST GenerateList(MSTRING name,PENTITYLIST values,ExecutionContext* pContext);
    PBool GenerateBool(MSTRING name,MBOOL value,ExecutionContext *pContext);
    int nodeId =0;
};


#endif //FLEXIBLECOMPUTERLANGUAGE_GENERATOR_H
