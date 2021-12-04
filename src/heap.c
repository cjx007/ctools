/*********************************************************************************
*文件名：heap.c
*描   述：二叉堆实现文件
*作   者：Domi
*版   本：1.0
*记   录：1.File created by Domi  2020-02-20           
*备   注：  
**********************************************************************************/ 

#include "../include/basetype.h"
#include "../include/heap.h"
#include <stdlib.h>
#include <stdio.h>

/**********************************************************
Function   : HEAP_Print
Description: 二叉堆信息打印
Input      : HEAP_S *pstHeap     二叉堆指针
Output     : NONE
Return     : VOID
Others     : NONE
Records    ：1.Function created by Domi 2018-07-20
***********************************************************/
VOID HEAP_Print(IN HEAP_S *pstHeap)
{
    INT i = 0;
    for(i = 0; i < pstHeap->uiHeapLength; i++)
    {
        printf("%d ", pstHeap->pulHeap[i]);
    }
    printf("\r\n");
    return;
}
/**********************************************************
Function   : HEAP_Create
Description: 二叉堆初始化
Input      : HEAP_S *pstHeap     二叉堆指针
             PF_COMPARE pfComp   比较函数指针
Output     : HEAP_S *pstHeap     二叉堆指针
Return     : SUCCESS             成功
             FAILED              失败
Others     : NONE
Records    ：1.Function created by Domi 2018-07-20
***********************************************************/
ULONG HEAP_Create(INOUT HEAP_S *pstHeap, IN PF_COMPARE pfComp)
{
    if (NULL == pstHeap || NULL == pfComp)
    {
        return FAILED;
    }
    pstHeap->pulHeap = (ULONG*)malloc(HEAP_INIT_SIZE * sizeof(ULONG));
    if (NULL == pstHeap->pulHeap)
    {
        return FAILED;
    }
    (VOID)memset(pstHeap->pulHeap, 0, HEAP_INIT_SIZE * sizeof(ULONG));
    pstHeap->uiHeapLength = 0;
    pstHeap->uiHeapSize = HEAP_INIT_SIZE;
    pstHeap->pfComp = pfComp;
    return SUCCESS;
}

/**********************************************************
Function   : HEAP_Destroy
Description: 二叉堆销毁
Input      : HEAP_S *pstHeap     二叉堆指针            
Output     : HEAP_S *pstHeap     二叉堆指针
Return     : VOID
Others     : NONE
Records    ：1.Function created by Domi 2018-07-20
***********************************************************/
VOID HEAP_Destroy(INOUT HEAP_S *pstHeap)
{
    if (NULL != pstHeap->pulHeap)
    {
        free(pstHeap->pulHeap);
    }
    (VOID)memset(pstHeap, 0, sizeof(HEAP_S));
    return;
}
/**********************************************************
Function   : HEAP_ShiftDown
Description: 二叉堆自顶向下堆化
Input      : HEAP_S *pstHeap     二叉堆指针            
Output     : NONE
Return     : VOID
Others     : NONE
Records    ：1.Function created by Domi 2018-07-20
***********************************************************/
VOID HEAP_ShiftDown(IN HEAP_S *pstHeap)
{
    INT i = 0;
    ULONG ulTemp = 0;
    while(i < pstHeap->uiHeapLength)
    {
        if (SON_LEFT(i) < pstHeap->uiHeapLength)
        {
            if (SON_RIGHT(i) >= pstHeap->uiHeapLength)
            {
                if (pstHeap->pfComp(pstHeap->pulHeap[i], pstHeap->pulHeap[SON_LEFT(i)]) > 0)
                {
                    ulTemp =  pstHeap->pulHeap[i];
                    pstHeap->pulHeap[i] = pstHeap->pulHeap[SON_LEFT(i)];
                    pstHeap->pulHeap[SON_LEFT(i)] = ulTemp;                    
                    i = SON_LEFT(i);
                }
                else
                {
                    break;
                }
            }
            else if ((pstHeap->pfComp(pstHeap->pulHeap[i], pstHeap->pulHeap[SON_LEFT(i)]) <= 0) &&
                     (pstHeap->pfComp(pstHeap->pulHeap[i], pstHeap->pulHeap[SON_RIGHT(i)]) <= 0))
            {
                break;
            }
            else if (pstHeap->pfComp(pstHeap->pulHeap[SON_LEFT(i)], pstHeap->pulHeap[SON_RIGHT(i)]) <= 0)
            {
                ulTemp =  pstHeap->pulHeap[i];
                pstHeap->pulHeap[i] = pstHeap->pulHeap[SON_LEFT(i)];
                pstHeap->pulHeap[SON_LEFT(i)] = ulTemp;                
                i = SON_LEFT(i);
            }
            else
            {
                ulTemp =  pstHeap->pulHeap[i];
                pstHeap->pulHeap[i] = pstHeap->pulHeap[SON_RIGHT(i)];
                pstHeap->pulHeap[SON_RIGHT(i)] = ulTemp;               
                i = SON_RIGHT(i);                
            }
        }
        else
        {
            break;
        }
        
    }
    return;
}
/**********************************************************
Function   : HEAP_ShiftUp
Description: 二叉堆自底向上堆化
Input      : HEAP_S *pstHeap     二叉堆指针            
Output     : NONE
Return     : VOID
Others     : NONE
Records    ：1.Function created by Domi 2018-07-20
***********************************************************/
VOID HEAP_ShiftUp(IN HEAP_S *pstHeap)
{
    INT i = pstHeap->uiHeapLength - 1;
    ULONG ulTemp = 0;
    while (i > 0)
    {
        if (pstHeap->pfComp(pstHeap->pulHeap[i], pstHeap->pulHeap[PARENT(i)]) < 0)
        {
            ulTemp = pstHeap->pulHeap[PARENT(i)];
            pstHeap->pulHeap[PARENT(i)] = pstHeap->pulHeap[i];
            pstHeap->pulHeap[i] = ulTemp;
            i = PARENT(i);
        }
        else
        {
            break;
        }
    }
    return;
}
/**********************************************************
Function   : HEAP_PopMin
Description: 弹出二叉堆最小元素
Input      : HEAP_S *pstHeap     二叉堆指针            
Output     : HEAP_S *pstHeap     二叉堆指针 
Return     : ULONG               二叉堆元素数据
Others     : NONE
Records    ：1.Function created by Domi 2018-07-20
***********************************************************/
ULONG HEAP_PopMin(INOUT HEAP_S *pstHeap)
{
    ULONG ulRet = NULL;
    if (0 != pstHeap->uiHeapSize)
    {
        ulRet = pstHeap->pulHeap[0];
        pstHeap->uiHeapLength--;
        pstHeap->pulHeap[0] = pstHeap->pulHeap[pstHeap->uiHeapLength];
        pstHeap->pulHeap[pstHeap->uiHeapLength] = NULL;
        HEAP_ShiftDown(pstHeap);
    }
    
    return ulRet;
}

/**********************************************************
Function   : HEAP_Add
Description: 弹出二叉堆最小元素
Input      : HEAP_S *pstHeap     二叉堆指针  
             ULONG ulValue       二叉堆元素数据
Output     : HEAP_S *pstHeap     二叉堆指针 
Return     : SUCCESS             成功
             FAILED              失败
Others     : NONE
Records    ：1.Function created by Domi 2018-07-20
***********************************************************/
ULONG HEAP_Add(INOUT HEAP_S *pstHeap, IN ULONG ulValue)
{
    ULONG ulRet = SUCCESS;
    ULONG *pulTemp = NULL;
    if (pstHeap->uiHeapLength >= pstHeap->uiHeapSize)
    {
        pulTemp = (ULONG*)malloc((pstHeap->uiHeapSize + HEAP_STEP_SIZE) * sizeof(ULONG));
        if (NULL != pulTemp)
        {
            memcpy(pulTemp, pstHeap->pulHeap, pstHeap->uiHeapLength * sizeof(ULONG));
            free(pstHeap->pulHeap);
            pstHeap->pulHeap = pulTemp;
            pstHeap->uiHeapSize += HEAP_STEP_SIZE;
                      
        }
        else
        {
            ulRet = FAILED;
        }
    }
    if (SUCCESS == ulRet)
    {
        pstHeap->pulHeap[pstHeap->uiHeapLength] = ulValue;
        pstHeap->uiHeapLength++;
        HEAP_ShiftUp(pstHeap);  
    }
    return ulRet;
}

