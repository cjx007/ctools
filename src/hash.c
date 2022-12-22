/*********************************************************************************
*�ļ�����hash.c
*��   ������ϣ�����ʵ�ִ����ļ�
*��   �ߣ�Domi
*��   ����1.0
*��   ¼��1.File created by Domi  2020-02-21           
*��   ע��  
**********************************************************************************/ 

#include "../include/basetype.h"
#include "../include/hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*������ϣ��*/
ULONG HASH_TABLE_Create(IN HASH_TABLE_S *pstHashTbl, 
                        IN UINT uiTblSize, 
                        IN PF_CALC pfHashIndexCalc)
{
    ULONG ulRet = SUCCESS;
    HASH_HEAD_S *pstHashHead = NULL;
    if (NULL == pstHashTbl || 0 == uiTblSize || NULL == pfHashIndexCalc)
    {
        return FAILED;
    } 
    pstHashHead = (HASH_HEAD_S *)malloc(uiTblSize * sizeof(HASH_HEAD_S));
    if (NULL == pstHashHead)
    {
        return FAILED;
    }
    (VOID)memset(pstHashHead, 0, uiTblSize * sizeof(HASH_HEAD_S));
    pstHashTbl->pfHashIndexCalc = pfHashIndexCalc;
    pstHashTbl->uiTblSize       = uiTblSize;
    pstHashTbl->pstHashList     = pstHashHead;
    
    return ulRet;
}

/*���ٹ�ϣ�����øú���ǰӦ����ͻ�����нڵ��ڴ��ͷ�*/
ULONG HASH_TABLE_Destroy(IN HASH_TABLE_S *pstHashTbl)
{
    ULONG ulRet = SUCCESS;    
    
    /*1.�ͷŹ�ϣ��ͻ��ͷ�ڵ�*/
    free(pstHashTbl->pstHashList);

    /*2.������ݣ����г�ʼ��*/
    (VOID)memset(pstHashTbl, 0, sizeof(HASH_TABLE_S));
    
    return ulRet;
}

