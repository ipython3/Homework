/*
哈希表

1.  输入关键字序列；

2.  用除留余数法构建哈希函数，用线性探测法解决冲突，构建哈希表HT1；

3.  用除留余数法构建哈希函数，用拉链法解决冲突，构建哈希表HT2；

4.  分别对HT1和HT2计算在等概率情况下查找成功和查找失败的ASL；

5.  分别在HT1和HT2中查找给定的关键字，给出比较次数
*/

#include <cstdio>

//使用线性探测法的哈希表
class HashTableOne
{
public:
    HashTableOne(int p,int n,int *a)
    {
        int i,h;
        this->p = p;
        this->n = n;
        for (i = 0; i < p; i++)
        {
            flag[i] = 0;
        }
        for (i = 0; i < n; i++)
        {
            h = a[i] % p;
            while (flag[h] == 1)
            {
                h = (h + 1) % p;
            }
            data[h] = a[i];
            flag[h] = 1;
        }
    }

    //求位置pos上的查找成功次数
    int success_pos(int pos)
    {
        if (flag[pos] == 0) return 0;
        int target = data[pos];
        int i = 1;
        int h = target % p;
        while (data[h] != target)
        {
            i++;
            h = (h + 1) % p;
        }
        return i;
    }

    //求位置pos上的查找失败次数
    int fail_pos(int pos)
    {
        int i = 1, t = pos;
        while (flag[pos] == 1)
        {
            pos = (pos + 1) % p;
            i++;
            if(i == p) return p;
        }
        return i;
    }

    //计算得到关于成功的一些情况
    void get_success()
    {
        int i, sum = 0;
        for (i = 0; i < p; i++)
        {
            success[i] = success_pos(i);
            sum += success[i];
        }
        avg_success = ((float)sum) / ((float)n);
    }

    //计算得到关于失败的一些情况
    void get_fail()
    {
        int i, sum = 0;
        for (i = 0; i < p; i++)
        {
            fail[i] = fail_pos(i);
            sum += fail[i];
        }
        avg_fail = ((float)sum) / ((float)p);
    }

    int p;
    int n;
    int data[100];
    int flag[100];//0表示此处为空，1表示此处已经存有东西
    int success[100];
    int fail[100];
    float avg_success;
    float avg_fail;
};


int main()
{
    int n, p, i;
    int data[100];
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &data[i]);
    }
    scanf("%d", &p);
    HashTableOne HT1(p, n, data);
    HT1.get_success();
    HT1.get_fail();

    printf("哈希表的地址：");
    for (i = 0; i < p; i++)
    {
        printf("%5d", i);
    }
    printf("\n");

    printf("表中的关键字：");
    for (i = 0; i < p; i++)
    {
        if (HT1.flag[i] == 0)
        {
            printf("   - ");
        }
        else
        {
            printf("%5d", HT1.data[i]);
        }
    }
    printf("\n");

    printf("成功查找次数：");
    for (i = 0; i < p; i++)
    {
       printf("%5d", HT1.success[i]);
    }
    printf("\n");

    printf("失败查找次数：");
    for (i = 0; i < p; i++)
    {
        printf("%5d", HT1.fail[i]);
    }
    printf("\n");

    printf("查找成功的平均查找长度：%.2f\n", HT1.avg_success);
    printf("查找失败的平均查找长度：%.2f", HT1.avg_fail);

    return 0;
}

