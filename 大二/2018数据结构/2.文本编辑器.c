/*
1.问题描述

实现一个简单的行编辑器
文本：由0个或多个字符构成的单行序列。这些字符的ASCII码在闭区间[32, 126]内，也就是说，这些字符均为可见字符或空格；如果这段文本为空，我们就说这个文本编辑器是空的。
光标：在一段文本中用于指示位置的标记，可以位于文本的第一个字符之前，文本的最后一个字符之后或文本的某两个相邻字符之间，光标初始位置为0。

文本编辑器：为一个可以对一段文本和该文本中的一个光标进行如下七条操作的程序。：
1.  Move k：将光标移动到第k个字符之后，如果k=0则将光标移到文本第一个字符之前。
2.  Insert n （换行） S：在光标后插入长度为n的字符串S，光标位置不变，n≥1。
3.  Delete n：删除光标后的n个字符，光标位置不变，n≥1。
4.  Rotate n：反转光标后的n个字符，光标位置不变，n≥1。
5.  Get：输出此时程序内保存的文本
6.  Prev：光标前移一个字符。
7.  Next：光标后移一个字符。
*/

#include <stdio.h>

void print(char *text,int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        printf("%c",text[i]);
    }
    printf("\n");
}

void copy(char *a, char *b, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        a[i] = b[i];
    }
}

void insert(char *text,int length,char *S,int n,int cursor)
{
    char t[100005];
    copy(t, text + cursor, length - cursor);
    copy(text + cursor, S, n);
    copy(text + cursor + n, t, length - cursor);
}

void rotate(char *a, int n)
{
    char t, *b = a + n - 1;
    while (a < b)
    {
        t = *a;
        *a = *b;
        *b = t;
        a++;
        b--;
    }
}

int main()
{
    char text[100005];
    char S[100005];
    int length = 0;
    int cursor = 0;

    int N,i,j,n;
    char command[20];

    scanf("%d",&N);

    for (i = 1; i <= N; i++)
    {
        scanf("%s", command);
        switch (command[0])
        {
            //Move n：将光标移动到第n个字符之后，如果n=0则将光标移到文本第一个字符之前。
            case 'M':
            {
                scanf("%d", &n);
                cursor = n;
                break;
            }

            //Insert n（换行）S：在光标后插入长度为n的字符串S，光标位置不变，n≥1。
            case 'I':
            {
                scanf("%d%*c", &n);
                scanf("%[^\n]", S);
                insert(text, length, S, n, cursor);
                length += n;
                break;
            }

            //Delete n：删除光标后的n个字符，光标位置不变，n≥1。
            case 'D':
            {
                scanf("%d", &n);
                for (j = 0; j < length - cursor - n; j++)
                {
                    text[cursor + j] = text[cursor + j + n];
                }
                length -= n;
                break;
            }

            //Rotate n：反转光标后的n个字符，光标位置不变，n≥1。
            case 'R':
            {
                scanf("%d", &n);
                rotate(text + cursor, n);
                break;
            }

            //Get：输出此时程序内保存的文本
            case 'G':
            {
                print(text,length);
                break;
            }

            //Prev：光标前移一个字符。
            case 'P':
            {
                cursor--;
                break;
            }

            // Next：光标后移一个字符。
            case 'N':
            {
                cursor++;
                break;
            }
        }
    }
    return 0;
}
