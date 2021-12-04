/*********************************************************************************
*文 件 名：util.c
*描    述：工具包示例实现文件
*作    者：Domi
*版    本：1.0
*修改记录：1.File created by Domi  2018-07-20           
*备    注：  
**********************************************************************************/ 

#include "../include/basetype.h"
#include "../include/list.h"
#include "../include/heap.h"
#include "../include/hash.h"
#include "../include/graph.h"
#include <stdio.h>
#include <stdlib.h>

/**********************************************************
Function   : compare
Description: 比较两个数据大小
Input      : ULONG ulA          数据A
             ULONG ulB          数据B
Output     : NONE
Return     : 1                  A>B
             0                  A=B
             -1                 A<B
Others     : NONE
Records    ：1.Function created by Domi 2018-07-20
***********************************************************/
INT compare(IN ULONG ulA, IN ULONG ulB)
{
    INT iRet = 0;
    INT iA = (INT)ulA;
    INT iB = (INT)ulB;
    
    if (iA > iB)
    {
        iRet = 1;
    }
    else if (iA < iB)
    {
        iRet = -1;
    }
    
    return iRet;
}

/**********************************************************
Function   : HEAP_Sort
Description: 堆排序
Input      : INT *piArray      待排序元素数组
             INT iLen          待排序元素数组大小
Output     : NONE
Return     : VOID
Others     : NONE
Records    ：1.Function created by Domi 2018-07-20
***********************************************************/
VOID HEAP_Sort(IN INT *piArray, IN INT iLen)
{
    INT i = 0;
    INT iTemp = 0;
    HEAP_S stHeap;
    HEAP_Create(&stHeap, compare);
    for (i = 0; i < iLen; i++)
    {
        HEAP_Add(&stHeap, piArray[i]);
    }
    for (i = 0; i < iLen; i++)
    {
        iTemp = (INT)HEAP_PopMin(&stHeap);
        printf("%d ", iTemp);
    }
    printf("\r\n");
    HEAP_Destroy(&stHeap);
    return;
}
GRAPH_S g_stGraph = {0};

VOID main()
{
    #if 0
    INT iA = 0;
    DTQ_HEAD_S stList;
    TEST_S *pstNode = NULL;
    TEST_S *pstNodeNext = NULL;
    DTQ_Init(&stList);
    while(scanf("%d", &iA) && iA != 99)
    {
        pstNode = (TEST_S*)malloc(sizeof(TEST_S));
        if (NULL != pstNode)
        {
            DTQ_NodeInit(&(pstNode->stNode));
            pstNode->iA = iA;
            DTQ_AddHead(&stList, &(pstNode->stNode));
        }
    }
    DTQ_FOR_EACH_ENTRY(&stList, pstNode, TEST_S, stNode)
    {
        printf("%d ", pstNode->iA);
    }
    printf("\r\n");
    DTQ_FOR_EACH_ENTRY_R(&stList, pstNode, TEST_S, stNode)
    {
        printf("%d ", pstNode->iA);
    }
    printf("\r\n");
    DTQ_FOR_EACH_ENTRY_SAFE(&stList, pstNode, pstNodeNext, TEST_S, stNode)
    {
        DTQ_DelNode(&(pstNode->stNode));        
        free(pstNode);
    }
    

    INT aiArray[] = {1,3,5,7,9,2,4,6,8,10,0,19};
    HEAP_Sort(aiArray, sizeof(aiArray)/sizeof(INT));
    #endif

    /*
    Dijkstra最短路径算法示例
    A B 12
    A F 16
    A G 14
    B C 10
    B F 7
    F G 9
    F C 6
    F E 2
    G E 8
    C E 5
    E D 4
    C D 3
    A B 0
    */
    CHAR szNodeA[10] = {0};
    CHAR szNodeB[10] = {0};
    INT iMetric = 0;
    (VOID)GRAPH_Create(&g_stGraph);
    
    while(scanf("%s %s %d",szNodeA,szNodeB,&iMetric) && iMetric !=0 )
    {
        (VOID)GRAPH_LINK_Add(&g_stGraph, szNodeA, szNodeB, iMetric);
        (VOID)GRAPH_LINK_Add(&g_stGraph, szNodeB, szNodeA, iMetric);
        szNodeA[0] = 0;
        szNodeB[0] = 0;
        iMetric = 0;
        
    }
    (VOID)GRAPH_Dijkstra(&g_stGraph,"D");
    GRAPH_Destroy(&g_stGraph);
    
    return;
}

