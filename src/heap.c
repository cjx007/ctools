/*********************************************************************************
*�ļ�����heap.c
*��   ���������ʵ���ļ�
*��   �ߣ�Domi
*��   ����1.0
*��   ¼��1.File created by Domi  2020-02-20           
*��   ע��  
**********************************************************************************/ 

#include "../include/basetype.h"
#include "../include/heap.h"
#include <stdlib.h>
#include <stdio.h>

/**********************************************************
Function   : HEAP_Print
Description: �������Ϣ��ӡ
Input      : HEAP_S *pstHeap     �����ָ��
Output     : NONE
Return     : VOID
Others     : NONE
Records    ��1.Function created by Domi 2018-07-20
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
Description: ����ѳ�ʼ��
Input      : HEAP_S *pstHeap     �����ָ��
             PF_COMPARE pfComp   �ȽϺ���ָ��
Output     : HEAP_S *pstHeap     �����ָ��
Return     : SUCCESS             �ɹ�
             FAILED              ʧ��
Others     : NONE
Records    ��1.Function created by Domi 2018-07-20
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
Description: ���������
Input      : HEAP_S *pstHeap     �����ָ��            
Output     : HEAP_S *pstHeap     �����ָ��
Return     : VOID
Others     : NONE
Records    ��1.Function created by Domi 2018-07-20
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
Description: ������Զ����¶ѻ�
Input      : HEAP_S *pstHeap     �����ָ��            
Output     : NONE
Return     : VOID
Others     : NONE
Records    ��1.Function created by Domi 2018-07-20
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
Description: ������Ե����϶ѻ�
Input      : HEAP_S *pstHeap     �����ָ��            
Output     : NONE
Return     : VOID
Others     : NONE
Records    ��1.Function created by Domi 2018-07-20
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
Description: �����������СԪ��
Input      : HEAP_S *pstHeap     �����ָ��            
Output     : HEAP_S *pstHeap     �����ָ�� 
Return     : ULONG               �����Ԫ������
Others     : NONE
Records    ��1.Function created by Domi 2018-07-20
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
Description: �����������СԪ��
Input      : HEAP_S *pstHeap     �����ָ��  
             ULONG ulValue       �����Ԫ������
Output     : HEAP_S *pstHeap     �����ָ�� 
Return     : SUCCESS             �ɹ�
             FAILED              ʧ��
Others     : NONE
Records    ��1.Function created by Domi 2018-07-20
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

