/*********************************************************************************
*�ļ�����graph.h
*��   ����ͼ��ؽӿ�ͷ�ļ�
*��   �ߣ�Domi
*��   ����1.0
*��   ¼��1.File created by Domi  2020-02-23           
*��   ע��  
**********************************************************************************/ 
#define GRAPH_HASH_SIZE      127
#define GRAPH_NODE_NAME_LEN  64

/*ͼ������ݽṹ*/
typedef struct stNODE
{
    HASH_NODE_S stHashNode;                /*��ϣ���*/
    CHAR szName[GRAPH_NODE_NAME_LEN + 1];  /*����ʶ*/
    DTQ_HEAD_S stLinks;                    /*�����ر� LINK_S*/
    BOOL bHaveDone;                        /*�Ƿ��Ѵ���*/
}GRAPH_NODE_S;

/*ͼ�����ر����ݽṹ*/
typedef struct stLINK
{
    DTQ_NODE_S stNode;
    GRAPH_NODE_S *pstSrcNode;                    /*Դ���*/
    GRAPH_NODE_S *pstDstNode;                    /*Ŀ�Ľ��*/
    INT  iMetric;                                /*�߶���ֵ*/
}GRAPH_LINK_S;

typedef HASH_TABLE_S GRAPH_S;


/*����ͼ*/
ULONG GRAPH_Create(IN GRAPH_S *pstGraph);

/*����ͼ*/
VOID GRAPH_Destroy(IN GRAPH_S *pstGraph);

/*ͼ�����ӽڵ�*/
GRAPH_NODE_S* GRAPH_NODE_Add(IN GRAPH_S *pstGraph, IN CHAR *pcNodeName);

/*���ݽڵ����Ʋ��ҽڵ�*/
GRAPH_NODE_S* GRAPH_NODE_Find(IN GRAPH_S *pstGraph, IN CHAR *pcNodeName);

/*����A->B��Link*/
ULONG GRAPH_LINK_Add(IN GRAPH_S *pstGraph, IN CHAR *szNodeA, IN CHAR *szNodeB, IN INT iMetric);

/*ɾ��A->B֮��ָ��metric��Link*/
ULONG GRAPH_LINK_Del(IN GRAPH_S *pstGraph, IN CHAR *szNodeA, IN CHAR *szNodeB, IN INT iMetric);

ULONG GRAPH_Dijkstra(IN GRAPH_S *pstGraph, IN CHAR *szRootName);



