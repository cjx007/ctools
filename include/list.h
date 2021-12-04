/*********************************************************************************
*�� �� ����list.h
*��    �������������ؽӿ�ͷ�ļ�
*��    �ߣ�Domi
*��    ����1.0
*�޸ļ�¼��1.File created by Domi  2020-02-20           
*��    ע��  
**********************************************************************************/ 

/*********************************************************************************
    ��ͷ���˫�˶���(Double-Tail-Queue)�����ݽṹ��ͼ���£�
    +------------------------------------------------------------------------+
    |                     User Data        User Data         User Data       |
    |    DTQ_HEAD_S       +--------+       +--------+        +--------+      |
    |    +--------+       |  ....  |       |  ....  |        |  ....  |      |
    +--->|pstNext |------>|pstNext |------>|pstNext |  ....  |pstNext |------+
    +----|pstPrev |<------|pstPrev |<------|pstPrev |  ....  |pstPrev |<-----+
    |    +--------+       |  ....  |       |  ....  |        |  ....  |      |
    |                     +--------+       +--------+        +--------+      |
    |                                                                        |
    |                                                                        |
    +------------------------------------------------------------------------+
**********************************************************************************/

typedef struct stDTQ_NODE
{
    struct stDTQ_NODE *pstNext;
    struct stDTQ_NODE *pstPrev;
}DTQ_NODE_S;

/*��ͷ����*/
typedef DTQ_NODE_S DTQ_HEAD_S;

/*���½ӿ���Σ������߱�֤��Ϊ��*/
/*�����ʼ��*/
VOID DTQ_Init(DTQ_HEAD_S *pstList);


/*����ʼ��*/
VOID DTQ_NodeInit(DTQ_NODE_S *pstNode);


/*����ͷ��������*/
VOID DTQ_AddHead(DTQ_HEAD_S *pstList, DTQ_NODE_S *pstNode);


/*����β��������*/
VOID DTQ_AddTail(DTQ_HEAD_S *pstList, DTQ_NODE_S *pstNode);


/*ָ�����������*/
VOID DTQ_AddAfter(DTQ_NODE_S *pstNode1, DTQ_NODE_S *pstNode2);


/*ָ�����ǰ������*/
VOID DTQ_AddBefore(DTQ_NODE_S* pstNode1, DTQ_NODE_S *pstNode2);


/*ժ�����*/
VOID DTQ_DelNode(DTQ_NODE_S *pstNode);

/*�ж������Ƿ�Ϊ��*/
BOOL DTQ_IsEmpty(DTQ_HEAD_S *pstList);

/*ժ��ͷ�ڵ�*/
VOID DTQ_DelHead(DTQ_HEAD_S *pstList);

/*ժ��β���*/
VOID DTQ_DelTail(DTQ_HEAD_S *pstList);


/*����������ָ���ȡ���ݽ��*/
#define DTQ_ENTRY_S(ptr, type, member) container_of(ptr, type, member)

/*��������*/
#define DTQ_FOR_EACH(head, pos) \
    for (pos = (head)->pstNext; pos != (head); \
            pos = pos->pstNext)
            
#define DTQ_FOR_EACH_SAFE(head, pos, next) \
            for (pos = (head)->pstNext, next = pos->pstNext; pos != (head); \
                pos = next, next = pos->pstNext) 
            
#define DTQ_FOR_EACH_ENTRY(head, pos, type, member)              \
    for (pos = DTQ_ENTRY_S((head)->pstNext, type, member);   \
         &pos->member != (head);  \
         pos = DTQ_ENTRY_S(pos->member.pstNext, type, member))  

#define DTQ_FOR_EACH_ENTRY_SAFE(head, pos, next, type, member)                  \
             for (pos = DTQ_ENTRY_S((head)->pstNext, type, member),      \
                     next = DTQ_ENTRY_S(pos->member.pstNext, type, member); \
                  &pos->member != (head);                                   \
                 pos = next, next = DTQ_ENTRY_S(next->member.pstNext, type, member))

#define DTQ_FOR_EACH_R(head, pos) \
                 for (pos = (head)->pstPrev; pos != (head); \
                         pos = pos->pstPrev)                         
                         
#define DTQ_FOR_EACH_ENTRY_R(head, pos, type, member)              \
                 for (pos  =DTQ_ENTRY_S((head)->pstPrev, type, member);   \
                      &pos->member != (head);  \
                      pos = DTQ_ENTRY_S(pos->member.pstPrev, type, member))              



