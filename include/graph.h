/*********************************************************************************
*文件名：graph.h
*描   述：图相关接口头文件
*作   者：Domi
*版   本：1.0
*记   录：1.File created by Domi  2020-02-23           
*备   注：  
**********************************************************************************/ 
#define GRAPH_HASH_SIZE      127
#define GRAPH_NODE_NAME_LEN  64

/*图结点数据结构*/
typedef struct stNODE
{
    HASH_NODE_S stHashNode;                /*哈希结点*/
    CHAR szName[GRAPH_NODE_NAME_LEN + 1];  /*结点标识*/
    DTQ_HEAD_S stLinks;                    /*结点相关边 LINK_S*/
    BOOL bHaveDone;                        /*是否已处理*/
}GRAPH_NODE_S;

/*图结点相关边数据结构*/
typedef struct stLINK
{
    DTQ_NODE_S stNode;
    GRAPH_NODE_S *pstSrcNode;                    /*源结点*/
    GRAPH_NODE_S *pstDstNode;                    /*目的结点*/
    INT  iMetric;                                /*边度量值*/
}GRAPH_LINK_S;

typedef HASH_TABLE_S GRAPH_S;


/*创建图*/
ULONG GRAPH_Create(IN GRAPH_S *pstGraph);

/*销毁图*/
VOID GRAPH_Destroy(IN GRAPH_S *pstGraph);

/*图中增加节点*/
GRAPH_NODE_S* GRAPH_NODE_Add(IN GRAPH_S *pstGraph, IN CHAR *pcNodeName);

/*根据节点名称查找节点*/
GRAPH_NODE_S* GRAPH_NODE_Find(IN GRAPH_S *pstGraph, IN CHAR *pcNodeName);

/*增加A->B的Link*/
ULONG GRAPH_LINK_Add(IN GRAPH_S *pstGraph, IN CHAR *szNodeA, IN CHAR *szNodeB, IN INT iMetric);

/*删除A->B之间指定metric的Link*/
ULONG GRAPH_LINK_Del(IN GRAPH_S *pstGraph, IN CHAR *szNodeA, IN CHAR *szNodeB, IN INT iMetric);

ULONG GRAPH_Dijkstra(IN GRAPH_S *pstGraph, IN CHAR *szRootName);



