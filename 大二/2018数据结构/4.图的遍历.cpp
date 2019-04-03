/*
图的遍历

   输入一个无向图，输出图的深度优先搜索遍历顺序与广度优先搜索遍历顺序。显然的，最后的答案会有多种可能，这里统一要求：当有多个节点可以搜索时，优先去节点编号最小的那个。
*/


#include <cstdio>
#include <cstring>

char G[40][40];//用邻接矩阵表示的无向图
char visited[40];//标记是否已经访问
int n;//顶点数量
int m;//边的数量
int start;//搜索的起始顶点

struct Node
{
    int v;
    Node *next;
};

//纯数字的链表队列
class Queue_Number
{
public:

    Queue_Number()
    {
        head = NULL;
        tail = NULL;
    }

    void EnQueue(int v)
    {
        Node *t = new Node;
        t->v = v;
        if (head == NULL)
        {
            head = t;
            tail = t;
        }
        else
        {
            tail->next = t;
            tail = t;
        }
    }

    int DeQueue()
    {
        int p;
        Node *t;
        if (head == NULL)//若是空队列，返回0
        {
            return 0;
        }
        p = head->v;
        t = head;
        if (head == tail)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            head = head->next;
        }
        delete t;
        return p;
    }

    int is_empty()
    {
        if (head == NULL)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    Node * head;
    Node *tail;
};

void print_v(int v)
{
    if (v == start)
    {
        printf("%d", v);
    }
    else
    {
        printf(" %d", v);
    }
}

int FirstAdjVex(int v)
{
    int i;
    for (i = 1; i <= n; i++)
    {
        if (G[v][i] == 1)
        {
            return i;
        }
    }
    return 0;
}

int NextAdjVex(int v, int w)
{
    int i;
    for (i = w + 1; i <= n; i++)
    {
        if (G[v][i] == 1)
        {
            return i;
        }
    }
    return 0;
}

void DFS(int v)
{
    int i;
    visited[v] = 1;
    print_v(v);
    for (i = FirstAdjVex(v); i != 0; i = NextAdjVex(v, i))
    {
        if (visited[i] == 0)
        {
            DFS(i);
        }
    }
}

void DFS_start()
{
    int i, v = start;
    for (i = 1; i <= n; i++)
    {
        if (visited[v] == 0)
        {
            DFS(v);
        }
        v = (v == n) ? 1 : v + 1;
    }
}


void BFS_start()
{
    Queue_Number Q;
    int i, j, t, v = start;
    for (i = 1; i <= n; i++)
    {
        if (visited[v] == 0)
        {
            visited[v] = 1;
            print_v(v);
            Q.EnQueue(v);
            while (Q.is_empty() == 0)
            {
                t = Q.DeQueue();
                for (j = FirstAdjVex(t); j != 0; j = NextAdjVex(t, j))
                {
                    if (visited[j] == 0)
                    {
                        visited[j] = 1;
                        print_v(j);
                        Q.EnQueue(j);
                    }
                }
            }
        }
        v = (v == n) ? 1 : v + 1;
    }
}

int main()
{
    int i, a, b;
    memset(G, 0, sizeof(G));
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        G[a][b] = 1;
        G[b][a] = 1;
    }
    scanf("%d", &start);

    memset(visited, 0, sizeof(visited));
    DFS_start();
    printf("\n");
    memset(visited, 0, sizeof(visited));
    BFS_start();
    return 0;
}
