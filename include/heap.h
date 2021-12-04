/*********************************************************************************
*文 件 名：heap.h
*描    述：二叉堆相关接口头文件
*作    者：Domi
*版    本：1.0
*修改记录：1.File created by Domi  2020-02-20           
*备    注：  
**********************************************************************************/ 

/*二叉堆比较函数类型定义*/
typedef INT (*PF_COMPARE) (ULONG, ULONG);
/*二叉堆数据结构*/
typedef struct stHEAP
{
    ULONG *pulHeap;
    UINT uiHeapSize;
    UINT uiHeapLength;
    PF_COMPARE pfComp;
}HEAP_S;

/*二叉堆初始化大小*/
#define HEAP_INIT_SIZE  200
/*二叉堆递增步长*/
#define HEAP_STEP_SIZE  50  

/*计算当前索引的父节点索引*/
#define PARENT(i)       (INT)((i - 1) / 2)
/*计算当前索引的左孩子索引*/
#define SON_LEFT(i)     (INT)((2 * i) + 1)
/*计算当前索引的右孩子索引*/
#define SON_RIGHT(i)    (INT)(2 * (i + 1))

/*堆初始化*/
ULONG HEAP_Create(HEAP_S *pstHeap, PF_COMPARE pfComp);

/*堆销毁*/
VOID HEAP_Destroy(HEAP_S *pstHeap);


/*自顶向下堆化*/
VOID HEAP_ShiftDown(HEAP_S *pstHeap);

/*自底向上堆化*/
VOID HEAP_ShiftUp(HEAP_S *pstHeap);

/*弹出二叉堆最小元素*/
ULONG HEAP_PopMin(HEAP_S *pstHeap);


/*二叉堆中添加元素*/
ULONG HEAP_Add(HEAP_S *pstHeap, ULONG ulValue);


