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
    PENTITY AddElem(PENTITY pentity);
    PENTITYLIST GetPrefix(int index);
    PENTITY GetlastElement();
    PENTITYLIST RemoveFromStart(int numOfElements);
    PENTITYLIST RemoveFromEnd(int numOfElements);
    PENTITYLIST ReverseList();
    PENTITY GetNthElement(MINT numberOfElem);
    PENTITYLIST GetSuffix(int numberOfElem);
    PENTITYLIST RemoveElement(int index);
    PENTITYLIST GetSubList(int stIndex, int numOfElem);
    PENTITYLIST Split(int splitPos);
    PENTITYLIST Split(PENTITYLIST splitPos);
    PENTITYLIST SortASC();
    PENTITYLIST SortDSC();



};

#endif