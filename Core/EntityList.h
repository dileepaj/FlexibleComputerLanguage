#ifndef _ENTITYLIST_H
#define _ENTITYLIST_H

#include "CommonIncludes.h"
#include "Entity.h"

class ExecutionContext;

class EntityList : public Entity, public LST_ENTITYPTR {
    EntityList::size_type st_CurrElemPos;
public:
    EntityList();

    virtual ~EntityList();

    virtual void Destroy();

    Entity *GetCopy();

    void ExecuteElements(ExecutionContext *pContext);

    Entity *GetCurrElem();

    void SeekToBegin();

    void SeekToEnd();

    void Seek(MULONG ulOffset, bool bIsNegative);

    PENTITY GetFirstElement();

    EntityList *GetInnerCount();

    PENTITYLIST Concat(PENTITYLIST list);
    void AddElem(PENTITY pentity);
    PENTITYLIST GetPrefix(int index);
};

#endif