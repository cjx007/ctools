/*********************************************************************************
*文件名：hash.c
*描   述：哈希表相关实现代码文件
*作   者：Domi
*版   本：1.0
*记   录：1.File created by Domi  2020-02-21           
*备   注：  
**********************************************************************************/ 

#include "../include/basetype.h"
#include "../include/hash.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*创建哈希表*/
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

/*销毁哈希表，调用该函数前应将冲突链所有节点内存释放*/
ULONG HASH_TABLE_Destroy(IN HASH_TABLE_S *pstHashTbl)
{
    ULONG ulRet = SUCCESS;    
    
    /*1.释放哈希冲突链头节点*/
    free(pstHashTbl->pstHashList);

    /*2.清空数据，进行初始化*/
    (VOID)memset(pstHashTbl, 0, sizeof(HASH_TABLE_S));
    
    return ulRet;
}

