#include "EntityList.h"
#include "ExecutionTemplate.h"
#include "ExecutionContext.h"
#include "Utils.h"
#include "Int.h"

EntityList::EntityList()
        : st_CurrElemPos(0) {
    ul_Type = ENTITY_TYPE_LIST;
}

EntityList::~EntityList() {

}

void EntityList::Destroy() {
    // First destroy the children in the list
    DestroyCollection(*this);

    MemoryManager::Inst.DeleteObject(this);
}

Entity *EntityList::GetCopy() {
    EntityList *pNew = 0;
    MemoryManager::Inst.CreateObject(&pNew);
    const_iterator ite1 = this->begin();
    const_iterator iteEnd1 = this->end();
    for (; ite1 != iteEnd1; ++ite1) {
        if (ENTITY_TYPE_NODE != (*ite1)->ul_Type) {
            pNew->push_back((*ite1)->GetCopy());
        } else {
            pNew->push_back(*ite1);
        }
    }
    return pNew;
}

void EntityList::ExecuteElements(ExecutionContext *pContext) {
    iterator ite1 = this->begin();
    const_iterator iteEnd1 = this->end();
    for (; ite1 != iteEnd1; ++ite1) {
        if (ENTITY_TYPE_EXECUTION_TEMPLATE == (*ite1)->ul_Type) {
            ExecutionTemplate *pET = (ExecutionTemplate *) (*ite1);
            if (0 != pET) {
                PENTITY pRes = pET->Execute(pContext);
                (*ite1) = pRes;
                pET->Destroy();
            }
        }
    }
}

Entity *EntityList::GetCurrElem() {
    EntityList::size_type stPos = 0;
    EntityList::const_iterator ite = begin();
    EntityList::const_iterator iteEnd = end();
    while (ite != iteEnd) {
        if (stPos == st_CurrElemPos) {
            return (*ite);
        }
        ++stPos;
        ++ite;
    }
    return 0;
}

void EntityList::SeekToBegin() {
    st_CurrElemPos = 0;
}

void EntityList::SeekToEnd() {
    st_CurrElemPos = size() - 1;
}

void EntityList::Seek(MULONG ulOffset, bool bIsNegative) {
    if (bIsNegative) {
        st_CurrElemPos -= ulOffset;
    } else {
        st_CurrElemPos += ulOffset;
    }
}

EntityList *EntityList::GetInnerCount() {
    EntityList *pListRes = 0;
    MemoryManager::Inst.CreateObject(&pListRes);
    SeekToBegin();
    PENTITY ent = GetCurrElem();
    while (ent) {
        PInt count = 0;
        MemoryManager::Inst.CreateObject(&count);
        count->SetValue(((PENTITYLIST) ent)->size());
        pListRes->push_back(count);

        Seek(1, false);
        ent = GetCurrElem();
    }
    return pListRes;
}
void EntityList::ReverseList()  {
    return  EntityList::reverse();

}

PENTITY EntityList::GetFirstElement() {
    return EntityList::front();

}

PENTITY EntityList::GetNthElement(MINT index) {

    const_iterator ite1 = this->begin();
    const_iterator iteEnd1 = this->end();

    MINT count = 0;
    while (ite1 != iteEnd1) {

            if(index >= this->size() ||  index < 0){
                return *ite1;
            }
            else{
                if (count == index) {
                    return (*ite1)->GetCopy();
                }
            }

        ++count;
        ++ite1;
    }

    return 0;

}


PENTITYLIST  EntityList::Concat(PENTITYLIST list) {
    list::const_iterator iterator1 = list->begin();
    list::const_iterator iteratorEnd = list->end();

    PENTITYLIST pRes = (PENTITYLIST)this->GetCopy();

    for(;iterator1 != iteratorEnd;iterator1++){
        pRes->push_back((*iterator1)->GetCopy());
    }
    return pRes;
}

void EntityList::AddElem(PENTITY pentity) {
    this->push_back(pentity);
}

//Will return, elements from the  begging
PENTITYLIST EntityList::GetPrefix(int numberOfElem){

    PENTITYLIST pRes;
    MemoryManager::Inst.CreateObject(&pRes);
    EntityList::const_iterator iterator1 = this->begin();
    EntityList::const_iterator iteratorEnd = this->end();

    if(numberOfElem<=0){
        //Empty list will be return
        return pRes;
    }
    if(numberOfElem >=  this->size() || numberOfElem <0){
        pRes = (PENTITYLIST)this->GetCopy();
        return pRes;
    }

    MINT it = 0;
    for(;iterator1 != iteratorEnd;iterator1++){

        if(it == numberOfElem){
            break;
        }
        pRes->push_back((*iterator1)->GetCopy());
        it++;
    }
    return pRes;
}

PENTITYLIST EntityList::GetSuffix(int numberOfElem) {
    PENTITYLIST pRes;
    MemoryManager::Inst.CreateObject(&pRes);

    EntityList::const_reverse_iterator iterator1 = this->rbegin();
    EntityList::const_reverse_iterator  iteratorEnd = this->rend();

    if(numberOfElem<=0){
        //Empty list will be return
        return pRes;
    }
    if(numberOfElem >=  this->size() || numberOfElem <0){
        pRes = (PENTITYLIST)this->GetCopy();
        return pRes;
    }

    MINT it = 0;
    for(;iterator1 != iteratorEnd;iterator1++){

        if(it == numberOfElem){
            break;
        }
        pRes->push_back((*iterator1)->GetCopy());
        it++;
    }
    pRes->reverse();
    return pRes;


}


PENTITY EntityList::GetlastElement(){
    return EntityList::back();
}


void EntityList::RemoveFromStart(int numOfElements) {

    PENTITYLIST ResList = new EntityList();
    EntityList::const_iterator ite1 = this->begin();
    EntityList::const_iterator iteEnd1 = this->end();

    int count = 0;
    while (ite1 != iteEnd1) {
        EntityList::const_iterator tobeRemoved = ite1;
        ite1++;

        this->remove(*tobeRemoved);

        if (count == numOfElements - 1) {
            break;
        }
        count++;

    }

}
    void EntityList::RemoveElement(int index) {

        EntityList::const_iterator ite1 = this->begin();
        EntityList::const_iterator iteEnd1 = this->end();

        int i = 0;
        while(ite1 != iteEnd1)
        {
            EntityList::const_iterator tobeRemoved = ite1;
            ite1++;


            if(i == index){
                this->remove(*tobeRemoved);
                break;
            }
            i++;

        }


}


PENTITYLIST EntityList::GetSubList(int stIndex, int numOfElem){
    this->SeekToBegin();
    PENTITYLIST pRes;
    MemoryManager::Inst.CreateObject(&pRes);

    //TODO:Index out bound should be handle in build error analyzing stage
    EntityList::const_iterator iterator1 = this->begin();
    EntityList::const_iterator iteratorEnd = this->end();
    for(int i = 0; i < stIndex;i++){
        iterator1++;
    }

    int availableNumberOfElem = this->size() - stIndex;
    if(numOfElem == 0){
        return pRes;
    }
    if(numOfElem > availableNumberOfElem){
       for(;iterator1 != iteratorEnd;iterator1++){
           pRes->push_back((*iterator1)->GetCopy());
       }
        return pRes;
    }

    int count = 0;
    if(numOfElem <= availableNumberOfElem){
        for(;iterator1 != iteratorEnd;iterator1++){
            pRes->push_back((*iterator1)->GetCopy());
            count++;
            if(count == numOfElem){
                break;
            }
        }
        return pRes;
    }

}


/*
 * Split a list into multiple lists
 * @param : split position
 * */
PENTITYLIST EntityList::Split(int splitPos) {

    PENTITYLIST res;
    MemoryManager::Inst.CreateObject(&res);

    PENTITYLIST firstSubList;
    MemoryManager::Inst.CreateObject(&firstSubList);

    PENTITYLIST secondSubList;
    MemoryManager::Inst.CreateObject(&secondSubList);

    EntityList::const_iterator  iterator1 = this->begin();
    EntityList::const_iterator  iteratorEnd = this->end();

    //TODO:Index out bound should be handle in build error analyzing stage
    int itCount = 0;

    for(;iterator1 != iteratorEnd;iterator1++){
        if(itCount >= splitPos){
            secondSubList->push_back((*iterator1)->GetCopy());
        }else{
            firstSubList->push_back((*iterator1)->GetCopy());
        }
        itCount++;
    }

    res->push_back(firstSubList);
    res->push_back(secondSubList);

    return res;

}

/*
 * Split a list into multiple lists
 * @param : list of split  positions
 * */
PENTITYLIST EntityList::Split(PENTITYLIST splitPos) {
    PENTITYLIST res;
    MemoryManager::Inst.CreateObject(&res);

    PENTITYLIST tempSubList;
    MemoryManager::Inst.CreateObject(&tempSubList);

    EntityList::const_iterator  iterator1 = this->begin();
    EntityList::const_iterator  iteratorEnd = this->end();

    splitPos->SeekToBegin();

    int itCount = 0;

    for(; iterator1 != iteratorEnd; iterator1++){
        //Get current split postion
        int currSplitPost = ((PInt)splitPos->GetCurrElem())->GetValue();

        if(itCount == currSplitPost){
            /*
             * Iterator has reached to the current split post
             * there for rest of the  elements should be included in a new temp sublist
             * */
             res->push_back((PENTITYLIST)tempSubList->GetCopy());
             //clear existing elements
             tempSubList->clear();
             //start new sub list
             tempSubList->push_back((*iterator1)->GetCopy());
             splitPos->Seek(1, false);
        }else{
            tempSubList->push_back((*iterator1)->GetCopy());
        }
        itCount++;
        if(itCount == this->size()){
            res->push_back((PENTITYLIST)tempSubList->GetCopy());
            tempSubList->Destroy();
            return res;
        }
    }
}



