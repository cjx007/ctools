/*********************************************************************************
*�� �� ����heap.h
*��    �����������ؽӿ�ͷ�ļ�
*��    �ߣ�Domi
*��    ����1.0
*�޸ļ�¼��1.File created by Domi  2020-02-20           
*��    ע��  
**********************************************************************************/ 

/*����ѱȽϺ������Ͷ���*/
typedef INT (*PF_COMPARE) (ULONG, ULONG);
/*��������ݽṹ*/
typedef struct stHEAP
{
    ULONG *pulHeap;
    UINT uiHeapSize;
    UINT uiHeapLength;
    PF_COMPARE pfComp;
}HEAP_S;

/*����ѳ�ʼ����С*/
#define HEAP_INIT_SIZE  200
/*����ѵ�������*/
#define HEAP_STEP_SIZE  50  

/*���㵱ǰ�����ĸ��ڵ�����*/
#define PARENT(i)       (INT)((i - 1) / 2)
/*���㵱ǰ��������������*/
#define SON_LEFT(i)     (INT)((2 * i) + 1)
/*���㵱ǰ�������Һ�������*/
#define SON_RIGHT(i)    (INT)(2 * (i + 1))

/*�ѳ�ʼ��*/
ULONG HEAP_Create(HEAP_S *pstHeap, PF_COMPARE pfComp);

/*������*/
VOID HEAP_Destroy(HEAP_S *pstHeap);


/*�Զ����¶ѻ�*/
VOID HEAP_ShiftDown(HEAP_S *pstHeap);

/*�Ե����϶ѻ�*/
VOID HEAP_ShiftUp(HEAP_S *pstHeap);

/*�����������СԪ��*/
ULONG HEAP_PopMin(HEAP_S *pstHeap);


/*����������Ԫ��*/
ULONG HEAP_Add(HEAP_S *pstHeap, ULONG ulValue);


