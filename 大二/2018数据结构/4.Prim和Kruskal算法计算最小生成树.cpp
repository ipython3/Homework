/*
求通讯网的最小代价生成树

输入一个无向铁通讯网图，用Prim和Kruskal算法计算最小生成树并输出。
*/

#include <cstdio>
#include <cstdlib>

struct Edge
{
    int a;
    int b;
    int w;
};

int pre[10005];

//返回x号结点的老大的编号
int HeadOf(int x)
{
    if (pre[x] == x)
    {
        return x;
    }
    else
    {
        pre[x] = HeadOf(pre[x]);
        return pre[x];
    }
}

void Join(int x, int y)
{
    int head_x = HeadOf(x), head_y = HeadOf(y);
    if (head_x != head_y)
    {
        pre[head_y] = head_x;
    }
}

int MyCompare(const void *elem1, const void *elem2)
{
    
    Edge *p1 = (Edge *)elem1;
    Edge *p2 = (Edge *)elem2;
    return p1->w - p2->w;
}

int main()
{
    int n, m, i, a, b, w, result = 0;
    Edge *E = new Edge[100005];
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
    {
        pre[i] = i;
    }
    for (i = 0; i < m; i++)
    {
        scanf("%d%d%d", &(E[i].a), &(E[i].b), &(E[i].w));
    }
    qsort(E, m, sizeof(Edge), MyCompare);
    for (i = 0; i < m; i++)
    {
        if (HeadOf(E[i].a) != HeadOf(E[i].b))//如果E[i]这条边连接了两个部分
        {
            result += E[i].w;
            Join(E[i].a, E[i].b);
        }
    }
    printf("%d", result);
    return 0;
}
