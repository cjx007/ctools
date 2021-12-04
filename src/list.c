/*********************************************************************************
*�ļ�����list.c
*��   �����������ʵ�ִ����ļ�
*��   �ߣ�Domi
*��   ����1.0
*��   ¼��1.File created by Domi  2020-02-20           
*��   ע��  
**********************************************************************************/ 

#include "../include/basetype.h"
#include "../include/list.h"
/*��ͷ��ʼ��*/
VOID DTQ_Init(DTQ_HEAD_S *pstList)
{
    pstList->pstNext = pstList;
    pstList->pstPrev = pstList;

    return;
}

/*����ڵ��ʼ��*/
VOID DTQ_NodeInit(DTQ_NODE_S *pstNode)
{
    pstNode->pstNext = NULL;
    pstNode->pstPrev = NULL;

    return;
}

/*��ͷ����ڵ�*/
VOID DTQ_AddHead(DTQ_HEAD_S *pstList, DTQ_NODE_S *pstNode)
{
    pstNode->pstNext = pstList->pstNext;
    pstNode->pstPrev = pstList;    
    pstList->pstNext->pstPrev = pstNode;
    pstList->pstNext = pstNode;
    
    return;
}

/*��β����ڵ�*/
VOID DTQ_AddTail(DTQ_HEAD_S *pstList, DTQ_NODE_S *pstNode)
{
    pstNode->pstNext = pstList;
    pstNode->pstPrev = pstList->pstPrev;
    pstList->pstPrev->pstNext = pstNode;
    pstList->pstPrev = pstNode;
    
    return;
}

/*ָ���ڵ�����ڵ�*/
VOID DTQ_AddAfter(DTQ_NODE_S *pstNode1, DTQ_NODE_S *pstNode2)
{
    pstNode2->pstNext = pstNode1->pstNext;
    pstNode2->pstPrev = pstNode1;    
    pstNode1->pstNext->pstPrev = pstNode2;
    pstNode1->pstNext = pstNode2;
    
    return;
}

/*ָ���ڵ�ǰ����ڵ�*/
VOID DTQ_AddBefore(DTQ_NODE_S* pstNode1, DTQ_NODE_S *pstNode2)
{
    pstNode2->pstNext = pstNode1;
    pstNode2->pstPrev = pstNode1->pstPrev;
    pstNode1->pstPrev->pstNext = pstNode2;
    pstNode1->pstPrev = pstNode2;
    return;
}

/*ժ��ָ���ڵ�*/
VOID DTQ_DelNode(DTQ_NODE_S *pstNode)
{
    pstNode->pstPrev->pstNext = pstNode->pstNext;
    pstNode->pstNext->pstPrev = pstNode->pstPrev;

    DTQ_NodeInit(pstNode);
    return;
}
/*�ж������Ƿ�Ϊ��*/
BOOL DTQ_IsEmpty(DTQ_HEAD_S *pstList)
{
    BOOL bRet = FALSE;
    if (pstList->pstNext == pstList)
    {
        bRet = TRUE;
    }
    return bRet;
}
/*�ӱ�ͷժ���ڵ�*/
VOID DTQ_DelHead(DTQ_HEAD_S *pstList)
{
    if (!DTQ_IsEmpty(pstList))
    {
        DTQ_DelNode(pstList->pstNext);
    }
    return;
}
/*�ӱ�βժ���ڵ�*/
VOID DTQ_DelTail(DTQ_HEAD_S *pstList)
{
    if (!DTQ_IsEmpty(pstList))
    {
        DTQ_DelNode(pstList->pstPrev);
    }
    return;
}
