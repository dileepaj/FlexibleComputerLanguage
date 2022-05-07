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
    PInt GenerateInteger(MULONG initialValue);
    PNODE  GenerateNode(MSTRING initVal,MSTRING initLVal, MSTRING initRVal,MSTRING initCusVal);
    PString GenerateString(MSTRING initialValue);
    PBool GenerateBool(MBOOL initialValue);
    int nodeId =0;
};


#endif //FLEXIBLECOMPUTERLANGUAGE_GENERATOR_H
