/*********************************************************************************
*文 件 名：list.h
*描    述：链表队列相关接口头文件
*作    者：Domi
*版    本：1.0
*修改记录：1.File created by Domi  2020-02-20           
*备    注：  
**********************************************************************************/ 

/*********************************************************************************
    带头结点双端队列(Double-Tail-Queue)，数据结构简图如下：
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

/*表头定义*/
typedef DTQ_NODE_S DTQ_HEAD_S;

/*以下接口入参，调用者保证不为空*/
/*链表初始化*/
VOID DTQ_Init(DTQ_HEAD_S *pstList);


/*结点初始化*/
VOID DTQ_NodeInit(DTQ_NODE_S *pstNode);


/*链表头部插入结点*/
VOID DTQ_AddHead(DTQ_HEAD_S *pstList, DTQ_NODE_S *pstNode);


/*链表尾部插入结点*/
VOID DTQ_AddTail(DTQ_HEAD_S *pstList, DTQ_NODE_S *pstNode);


/*指定结点后插入结点*/
VOID DTQ_AddAfter(DTQ_NODE_S *pstNode1, DTQ_NODE_S *pstNode2);


/*指定结点前插入结点*/
VOID DTQ_AddBefore(DTQ_NODE_S* pstNode1, DTQ_NODE_S *pstNode2);


/*摘除结点*/
VOID DTQ_DelNode(DTQ_NODE_S *pstNode);

/*判断链表是否为空*/
BOOL DTQ_IsEmpty(DTQ_HEAD_S *pstList);

/*摘除头节点*/
VOID DTQ_DelHead(DTQ_HEAD_S *pstList);

/*摘除尾结点*/
VOID DTQ_DelTail(DTQ_HEAD_S *pstList);


/*根据链表结点指针获取数据结点*/
#define DTQ_ENTRY_S(ptr, type, member) container_of(ptr, type, member)

/*遍历链表*/
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



