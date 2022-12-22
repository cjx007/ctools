/*********************************************************************************
*文件名：graph.c
*描   述：图算法工具实现文件
*作   者：Domi
*版   本：1.0
*记   录：1.File created by Domi  2020-02-23           
*备   注：  
**********************************************************************************/ 
#include "../include/basetype.h"
#include "../include/list.h"
#include "../include/hash.h"
#include "../include/heap.h"
#include "../include/graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


INT BKDRHash(CHAR *pcStr)
{
    INT iSeed = 131; // 31 131 1313 13131 131313 etc..
    INT iHash = 0;

    while (*pcStr)
    {
        iHash = iHash * iSeed + (*pcStr++);
    }

    return (iHash & 0x7FFFFFFF);
}

INT GRAPH_HashIndexCalc(IN ULONG ulData)
{
    CHAR *pcNodeName = (CHAR*)ulData;
    return BKDRHash(pcNodeName) % GRAPH_HASH_SIZE;
}

ULONG GRAPH_Create(IN GRAPH_S *pstGraph)
{
    return HASH_TABLE_Create(pstGraph, GRAPH_HASH_SIZE, GRAPH_HashIndexCalc);
}
VOID GRAPH_Destroy(IN GRAPH_S *pstGraph)
{
    UINT uiIndex= 0;
    HASH_HEAD_S *pstHashHead     = NULL;
    GRAPH_NODE_S *pstNodePos     = NULL;
    GRAPH_NODE_S *pstNodeNext    = NULL;
    GRAPH_LINK_S *pstLinkPos     = NULL;
    GRAPH_LINK_S *pstLinkNext    = NULL;
    HASH_NODE_S *pstNodeP = NULL;
    HASH_NODE_S *pstNodeN = NULL;

    /*逐哈希格进行释放*/
    for (pstHashHead = pstGraph->pstHashList; uiIndex < pstGraph->uiTblSize; pstHashHead++, uiIndex++)
    {
        /*释放冲突链节点*/
        HASH_LIST_FOR_EACH_SAFE(pstHashHead, pstNodeP, pstNodeN)        
        {
            pstNodePos = HASH_ENTRY(pstNodeP, GRAPH_NODE_S, stHashNode);
            DTQ_FOR_EACH_ENTRY_SAFE(&(pstNodePos->stLinks), pstLinkPos, pstLinkNext, GRAPH_LINK_S, stNode)
            {
                /*释放节点下link链表*/
                DTQ_DelNode(&(pstLinkPos->stNode));
                free(pstLinkPos);
            }
            HASH_NODE_Del(&(pstNodePos->stHashNode));
            free(pstNodePos);
        }
    }
    /*销毁哈希表*/
    (VOID)HASH_TABLE_Destroy(pstGraph);
    return;
}

GRAPH_NODE_S* GRAPH_NODE_Add(IN GRAPH_S *pstGraph, IN CHAR *pcNodeName)
{
    INT iHashIndex = 0;
    HASH_HEAD_S *pstHead  = NULL;
    GRAPH_NODE_S *pstPos  = NULL;
    GRAPH_NODE_S *pstNode = NULL;
    HASH_NODE_S *pstPosP  = NULL;
    HASH_NODE_S *pstNextN = NULL;
    
    if (NULL == pstGraph || NULL == pcNodeName || 0 == *pcNodeName)
    {

        return NULL;
    }
 
    pstHead =  pstGraph->pstHashList + pstGraph->pfHashIndexCalc(pcNodeName);
    HASH_LIST_FOR_EACH_SAFE(pstHead, pstPosP, pstNextN)
    {
        pstPos = HASH_ENTRY(pstPosP, GRAPH_NODE_S,stHashNode);
        if (0 == strcmp(pcNodeName, pstPos->szName))
        {
            pstNode = pstPos;
            break;
        }
    }
    
    if (NULL == pstNode)
    {
        pstNode = (GRAPH_NODE_S *)malloc(sizeof(GRAPH_NODE_S));
        if (NULL != pstNode)
        {
            memset(pstNode, 0, sizeof(GRAPH_NODE_S));
            strcpy(pstNode->szName, pcNodeName);
            DTQ_Init(&(pstNode->stLinks));
            HASH_NODE_Init(&(pstNode->stHashNode));
            HASH_LIST_AddHead(pstHead, &(pstNode->stHashNode));
        }
        
    }
    
    return pstNode;
}

GRAPH_NODE_S* GRAPH_NODE_Find(IN GRAPH_S *pstGraph, IN CHAR *pcNodeName)
{
    INT iHashIndex = 0;
    HASH_HEAD_S *pstHead  = NULL;
    GRAPH_NODE_S *pstPos  = NULL;
    GRAPH_NODE_S *pstNode = NULL;
    HASH_NODE_S *pstPosP  = NULL;
    HASH_NODE_S *pstNextN = NULL;
    BOOL bFind = FALSE;

    if (NULL == pstGraph || NULL == pcNodeName || 0 == *pcNodeName)
    {

        return NULL;
    } 
    pstHead =  pstGraph->pstHashList + pstGraph->pfHashIndexCalc(pcNodeName);
    HASH_LIST_FOR_EACH_SAFE(pstHead, pstPosP, pstNextN)
    {
        pstPos = HASH_ENTRY(pstPosP, GRAPH_NODE_S,stHashNode); 
        if (0 == strcmp(pcNodeName, pstPos->szName))
        {
            pstNode = pstPos;
            bFind = TRUE;
            break;
        }
    }
     
    return pstNode;
}
/*增加A->B的Link*/
ULONG GRAPH_LINK_Add(IN GRAPH_S *pstGraph, 
                     IN CHAR *szNodeA, 
                     IN CHAR *szNodeB, 
                     IN INT iMetric)
{
    ULONG ulRet = FAILED;
    GRAPH_NODE_S *pstNodeA = NULL;
    GRAPH_NODE_S *pstNodeB = NULL;
    GRAPH_LINK_S *pstLink  = NULL;
    
    if (NULL == pstGraph || NULL == szNodeA || 
        NULL == szNodeB || 0 == *szNodeA || 0 == *szNodeB)
    {
        return ulRet;
    }
    pstNodeA = GRAPH_NODE_Add(pstGraph, szNodeA);
    pstNodeB = GRAPH_NODE_Add(pstGraph, szNodeB);
    if (NULL != pstNodeA && NULL != pstNodeB)
    {
        pstLink = (GRAPH_LINK_S *)malloc(sizeof(GRAPH_LINK_S));
        if (NULL != pstLink)
        {
            memset(pstLink, 0, sizeof(GRAPH_LINK_S));
            pstLink->iMetric = iMetric;
            pstLink->pstSrcNode = pstNodeA;
            pstLink->pstDstNode = pstNodeB;
            DTQ_NodeInit(&(pstLink->stNode));
            DTQ_AddTail(&(pstNodeA->stLinks), &(pstLink->stNode));  
            ulRet = SUCCESS;
        }
    }
    return ulRet;
}
/*删除A->B之间指定metric的Link*/
ULONG GRAPH_LINK_Del(IN GRAPH_S *pstGraph, IN CHAR *szNodeA, IN CHAR *szNodeB, IN INT iMetric)
{
    ULONG ulRet = FAILED;
    GRAPH_NODE_S *pstNodeA = NULL;
    GRAPH_NODE_S *pstNodeB = NULL;
    GRAPH_LINK_S *pstLink  = NULL;
    GRAPH_LINK_S *pstPos = NULL;
    GRAPH_LINK_S *pstNext = NULL;
    
    if (NULL == pstGraph || NULL == szNodeA || 
        NULL == szNodeB || 0 == *szNodeA || 0 == *szNodeB)
    {
        return ulRet;
    }
    pstNodeA = GRAPH_NODE_Find(pstGraph, szNodeA);
    pstNodeB = GRAPH_NODE_Find(pstGraph, szNodeB);

    DTQ_FOR_EACH_ENTRY_SAFE(&(pstNodeA->stLinks), pstPos, pstNext, GRAPH_LINK_S, stNode)
    {
        if (pstNodeB == pstPos->pstDstNode && iMetric == pstPos->iMetric)
        {
            ulRet = SUCCESS;
            DTQ_DelNode(&(pstPos->stNode));
            free(pstPos);
            break;
        }
    }
    
    return ulRet;
}

INT graphLinkComp(IN GRAPH_LINK_S *pstLink1, IN GRAPH_LINK_S *pstLink2)
{
    return (pstLink1->iMetric - pstLink2->iMetric);
}

/*以指定名称节点为根进行Dijkstra计算*/
ULONG GRAPH_Dijkstra(IN GRAPH_S *pstGraph, IN CHAR *szRootName)
{

    ULONG ulRet              =FAILED;
    GRAPH_NODE_S *pstNode    = NULL;
    GRAPH_LINK_S *pstLink    = NULL;
    GRAPH_LINK_S *pstLinkMin = NULL;
    INT iMetric              = 0;
    BOOL bContinue           = FALSE;
    
    HEAP_S stHeap;
    if (NULL == pstGraph || NULL == szRootName || 0 == *szRootName)
    {
        return ulRet;
    }
    
    pstNode = GRAPH_NODE_Find(pstGraph, szRootName);
    if (NULL == pstNode)
    {
        return ulRet;
    }
    (VOID)HEAP_Create(&stHeap, graphLinkComp);
    printf("%s->\r\n",szRootName);
    pstNode->bHaveDone = TRUE;
    do
    {
        if (bContinue == FALSE)
        {        
            DTQ_FOR_EACH_ENTRY(&(pstNode->stLinks), pstLink, GRAPH_LINK_S, stNode)
            {
                if (pstLink->pstDstNode->bHaveDone != TRUE)
                {
                    pstLink->iMetric += iMetric;
                    HEAP_Add(&stHeap, pstLink);
                }
            }
        }
        pstLinkMin = HEAP_PopMin(&stHeap);
        if (pstLinkMin->pstDstNode->bHaveDone == TRUE)
        {

            bContinue = TRUE;
        }
        else
        {
            bContinue =FALSE;
            iMetric = pstLinkMin->iMetric;
            printf("   %s:%d\r\n", pstLinkMin->pstDstNode->szName, iMetric);
            pstNode = pstLinkMin->pstDstNode;  
            pstNode->bHaveDone = TRUE;
        }
        
    }while(stHeap.uiHeapLength > 0);
    HEAP_Destroy(&stHeap);
    
    return ulRet;
}

