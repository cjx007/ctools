/*********************************************************************************
*�ļ�����hash.h
*��   ������ϣ��ʵ��ͷ�ļ�
*��   �ߣ�Domi
*��   ����1.0
*��   ¼��1.File created by Domi  2020-02-20           
*��   ע��  
**********************************************************************************/ 

/*��ϣ��ͻ���ڵ�*/
typedef struct stHASH_NODE
{
    struct stHASH_NODE *pstNext, **ppstPrev;
}HASH_NODE_S;

/*��ϣ��ͻ��ͷ�ڵ�*/
typedef struct stHASH_HEAD
{
    HASH_NODE_S *pstFirst;
}HASH_HEAD_S;

/*��ϣ�������㺯��ָ�����Ͷ���*/
typedef INT (*PF_CALC) (ULONG);

/*��ϣ��ṹ����*/
typedef struct stHASH_TABLE
{
    UINT uiTblSize;            /*��ϣ���С*/
    HASH_HEAD_S *pstHashList;
    PF_CALC pfHashIndexCalc;
}HASH_TABLE_S;

/*��ͻ����ʼ��*/
STATIC inline VOID HASH_HEAD_Init(HASH_HEAD_S *pstHead)
{
    pstHead->pstFirst = NULL;
    return;
}

/*��ͻ���ڵ��ʼ��*/
STATIC inline VOID HASH_NODE_Init(HASH_NODE_S *pstNode)
{
    pstNode->pstNext  = NULL;
    pstNode->ppstPrev = NULL;
    return;
}
/*�жϽڵ��Ƿ��ڳ�ͻ������*/
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
/*�жϳ�ͻ���Ƿ�Ϊ��*/
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

/*��ͻ����ժ���ڵ�*/
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
/*��ͻ����ժ���ڵ�*/
STATIC inline VOID HASH_NODE_Del(HASH_NODE_S *pstNode)
{
    if (HASH_NODE_Hashed(pstNode))
    {
        HashNodeDel(pstNode);
        HASH_NODE_Init(pstNode);
    }
    return;
}

/*��ͻ��ͷ����ڵ�*/
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

/*ָ���ڵ�ǰ����ڵ�*/
STATIC inline VOID HASH_LIST_AddBefore(HASH_NODE_S *pstPos, HASH_NODE_S *pstNode)
{
    pstNode->ppstPrev = pstPos->ppstPrev;
    pstNode->pstNext = pstPos;
    pstPos->ppstPrev = &pstNode->pstNext;
    *(pstNode->ppstPrev) = pstNode;
    
    return;
}
/*ָ���ڵ�����ڵ�*/
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

/*�ƶ���ͻ��*/
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

/*������ϣ��ͻ��*/
#define HASH_LIST_FOR_EACH(head, pos) \
    for (pos = (head)->pstFirst; pos ; pos = pos->pstNext)

/*��ȫ������ϣ��ͻ�������������п�����ժ���ڵ����*/
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




