/*********************************************************************************
*文件名：hash.h
*描   述：哈希表实现头文件
*作   者：Domi
*版   本：1.0
*记   录：1.File created by Domi  2020-02-20           
*备   注：  
**********************************************************************************/ 

/*哈希冲突链节点*/
typedef struct stHASH_NODE
{
    struct stHASH_NODE *pstNext, **ppstPrev;
}HASH_NODE_S;

/*哈希冲突链头节点*/
typedef struct stHASH_HEAD
{
    HASH_NODE_S *pstFirst;
}HASH_HEAD_S;

/*哈希索引计算函数指针类型定义*/
typedef INT (*PF_CALC) (ULONG);

/*哈希表结构定义*/
typedef struct stHASH_TABLE
{
    UINT uiTblSize;            /*哈希格大小*/
    HASH_HEAD_S *pstHashList;
    PF_CALC pfHashIndexCalc;
}HASH_TABLE_S;

/*冲突链初始化*/
STATIC inline VOID HASH_HEAD_Init(HASH_HEAD_S *pstHead)
{
    pstHead->pstFirst = NULL;
    return;
}

/*冲突链节点初始化*/
STATIC inline VOID HASH_NODE_Init(HASH_NODE_S *pstNode)
{
    pstNode->pstNext  = NULL;
    pstNode->ppstPrev = NULL;
    return;
}
/*判断节点是否在冲突链表上*/
STATIC inline BOOL HASH_NODE_Hashed(const HASH_NODE_S *pstNode)
{
    if (NULL == pstNode->ppstPrev)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }    
}
/*判断冲突链是否为空*/
STATIC inline BOOL HASH_LIST_IsEmpty(const HASH_HEAD_S *pstHead)
{
    if (NULL == pstHead->pstFirst)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }    
}

/*冲突链上摘除节点*/
STATIC inline VOID HashNodeDel(HASH_NODE_S *pstNode)
{
    HASH_NODE_S *pstNext = pstNode->pstNext;
    HASH_NODE_S **ppstPrev = pstNode->ppstPrev;
    *ppstPrev = pstNext;
    if (NULL != pstNext)
    {
        pstNext->ppstPrev = ppstPrev;
    }
    return;
}
/*冲突链上摘除节点*/
STATIC inline VOID HASH_NODE_Del(HASH_NODE_S *pstNode)
{
    if (HASH_NODE_Hashed(pstNode))
    {
        HashNodeDel(pstNode);
        HASH_NODE_Init(pstNode);
    }
    return;
}

/*冲突链头插入节点*/
STATIC inline VOID HASH_LIST_AddHead(HASH_HEAD_S *pstHead, HASH_NODE_S *pstNode)
{
    HASH_NODE_S *pstFirst = pstHead->pstFirst;
    pstNode->pstNext= pstFirst;
    if (NULL != pstFirst)
    {
        pstFirst->ppstPrev = &pstNode->pstNext;
    }
    pstHead->pstFirst = pstNode;
    pstNode->ppstPrev = &pstHead->pstFirst;
    return;
}

/*指定节点前插入节点*/
STATIC inline VOID HASH_LIST_AddBefore(HASH_NODE_S *pstPos, HASH_NODE_S *pstNode)
{
    pstNode->ppstPrev = pstPos->ppstPrev;
    pstNode->pstNext = pstPos;
    pstPos->ppstPrev = &pstNode->pstNext;
    *(pstNode->ppstPrev) = pstNode;
    
    return;
}
/*指定节点后插入节点*/
STATIC inline VOID HASH_LIST_AddAfter(HASH_NODE_S *pstPos, HASH_NODE_S *pstNode)
{
    pstNode->pstNext  = pstPos->pstNext;
    pstPos->pstNext   = pstNode;
    pstNode->ppstPrev = &pstPos->pstNext;

    if(NULL != pstNode->pstNext)
    {
        pstNode->pstNext->ppstPrev = &pstNode->pstNext;
    }
    return;
}

/*移动冲突链*/
STATIC inline VOID HASH_LIST_MOV(HASH_HEAD_S *pstOld, HASH_HEAD_S *pstNew)
{
    pstNew->pstFirst = pstOld->pstFirst;
    if (NULL != pstNew->pstFirst)
    {
        pstNew->pstFirst->ppstPrev = &pstNew->pstFirst;
    }
    pstOld->pstFirst = NULL;
    return;
}

#define HASH_ENTRY(ptr, type, member) container_of(ptr,type,member)

/*遍历哈希冲突链*/
#define HASH_LIST_FOR_EACH(head, pos) \
    for (pos = (head)->pstFirst; pos ; pos = pos->pstNext)

/*安全遍历哈希冲突链：遍历过程中可能有摘除节点情况*/
#define HASH_LIST_FOR_EACH_SAFE(head, pos, next) \
    for (pos = (head)->pstFirst; pos && ({ next = pos->pstNext; 1; }); \
         pos = next)


#define HASH_LIST_ENTRY_SAFE(ptr, type, member) \
    ({ typeof(ptr) ____ptr = (ptr); \
       ____ptr ? HASH_ENTRY(____ptr, type, member) : NULL; \
    })


ULONG HASH_TABLE_Create(IN HASH_TABLE_S *pstHashTbl, 
                        IN UINT uiTblSize, 
                        IN PF_CALC pfHashIndexCalc);
    
ULONG HASH_TABLE_Destroy(IN HASH_TABLE_S *pstHashTbl);




