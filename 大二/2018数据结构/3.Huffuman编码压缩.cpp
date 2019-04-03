/*
用huffman压缩技术实现对任意文件的压缩和解压缩处理
要求对所有的文件类型进行压缩，压缩之后的文件后缀名为huff。同时，可以对所有后缀名为huff的压缩文件进行解压缩
1.      题目2中以1个字节(8bit)为单位进行huffman编码
2.      对任意文件进行压缩后可以输出一个后缀名为huff的单文件，并且可以对任意一个后缀名为huff的单文件进行解压还原出原文件。
3.      群内将提供10不同种类的文件包括文档、图片、视频、可执行文件等进行压缩测试，要求可以完成压缩和解压的步骤，并且解压出来的文件没有任何损失。
*/


#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <cstdio>
#include <cstring>



struct HTNode
{
    unsigned int weight;
    unsigned int parent;
    unsigned int lchild;
    unsigned int rchild;
};

typedef char* *HCode;

struct Elem
{
    unsigned char ch;
    unsigned int weight;
};


//求文件fp大小
unsigned int SizeOfFile(FILE *fp)
{
    unsigned int cur = ftell(fp);
    fseek(fp, 0, SEEK_END);
    unsigned int size = ftell(fp);
    fseek(fp, cur, SEEK_SET);
    return size;
}

//在HT[1~n]上选择出parent为0且weight最小的两个结点，序号为s1、s2
void Select(HTNode* HT, int n, int &s1, int &s2)
{
    int i;
    unsigned int min = 0xffffffff;
    for (i = 1; i <= n; i++)
    {
        if (HT[i].parent == 0)
        {
            if (HT[i].weight < min)
            {
                s1 = i;
                min = HT[i].weight;
            }
        }
    }
    min = 0xffffffff;
    for (i = 1; i <= n; i++)
    {
        if (i!=s1 && HT[i].parent == 0)
        {
            if (HT[i].weight < min)
            {
                s2 = i;
                min = HT[i].weight;
            }
        }
    }
}

//构建Huffman树HT，求出Huffman编码HC
//set为字符集（含有字符频率信息），共有n种字符
void HuffmanCoding(HTNode* &HT, HCode &HC, Elem *set, int n)
{
    //n个叶子节点的Huffman树，共有2n-1个结点
    int i, m = 2 * n - 1, s1, s2;
    HT = new HTNode[m + 1];
    for (i = 1; i <= n; i++)
    {
        HT[i].weight = set[i].weight;
        HT[i].parent = HT[i].lchild = HT[i].rchild = 0;
    }
    for (; i <= m; i++)
    {
        HT[i].weight = HT[i].parent = HT[i].lchild = HT[i].rchild = 0;
    }
    for (i = n + 1; i <= m; i++)
    {
        Select(HT, i - 1, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    HC = new char*[n + 1];
    char *str = new char[n];
    int start,t,f;
    str[n - 1] = 0;
    for (i = 1; i <= n; i++)
    {
        start = n - 1;
        for (t = i, f = HT[i].parent; f != 0; t = f, f = HT[f].parent)
        {
            if (HT[f].lchild == t)
            {
                str[--start] = '0';
            }
            else
            {
                str[--start] = '1';
            }
        }
        HC[i] = new char[n - start];
        strcpy(HC[i], str + start);
    }
    delete[]str;
}

//找到字符ch对应的编码
char *Search(HCode HC, Elem *set,int n, unsigned char ch)
{
    int i;
    for (i = 1; i <= n; i++)
    {
        if (set[i].ch == ch)
        {
            break;
        }
    }
    return HC[i];
}

//向bitstream中写入数据，Byte_pos与bit_left记录了正在写入的位置
//bit_left取值只能为1、2、3、4、5、6、7、8，不能为0
void WriteBitstream(unsigned char *bitstream, int &Byte_pos, int &bit_left, char *code)
{
    int code_len = strlen(code);
    unsigned char *t;
    int i = 0;
    while(1)
    {
        t = bitstream + Byte_pos;//找到正在写入的那个字节
        while (bit_left > 0)
        {
            *t <<= 1;
            if (code[i] == '1')
            {
                *t += 1;
            }
            i++;
            bit_left--;
            if (i == code_len)
            {
                if (bit_left == 0)
                {
                    Byte_pos++;
                    bit_left = 8;
                }
                return;
            }
        }
        Byte_pos++;
        bit_left = 8;
    }
}

//读出bitstream中bit_num位置的那个比特是0还是1
int ReadBit(unsigned char *bitstream, int bit_num)
{
    unsigned char t = *(bitstream + (bit_num / 8));
    bit_num = bit_num % 8;
    t <<= bit_num;
    t >>= 7;
    return t;
}

void Extract(unsigned char *bitstream, int bit_num, HTNode *HT, int root, Elem *set, FILE *file_extract)
{
    int p = root, i, b;
    for (i = 0; i < bit_num; i++)
    {
        b = ReadBit(bitstream, i);
        if (b == 0)
        {
            p = HT[p].lchild;
        }
        else
        {
            p = HT[p].rchild;
        }
        if (HT[p].lchild == 0 && HT[p].rchild == 0)
        {
            fputc(set[p].ch, file_extract);
            p = root;
        }
    }
}

int main()
{
    char ORIGIN[100] = "[9]test.mp4";//原始文件名
    char COMPRESSED[100] = "[9]test.mp4.huff";//压缩文件名
    char EXTRACT[100] = "[9]test_original.mp4";//解压缩文件名
    FILE *file_origin = fopen(ORIGIN, "rb");
    unsigned int size = SizeOfFile(file_origin);
    unsigned int i;
    char ch;
    unsigned int freq[256];

    //统计字符频率
    for (i = 0; i < 256; i++)
    {
        freq[i] = 0;
    }
    for (i = 0; i < size; i++)
    {
        ch = fgetc(file_origin);
        freq[(unsigned char)ch]++;
    }

    //构建字符集（含有字符频率信息）
    int n = 0;
    Elem set[257];
    for (i = 0; i < 256; i++)
    {
        if (freq[i] != 0)
        {
            n++;
            set[n].ch = i;
            set[n].weight = freq[i];
        }
    }

    //构建Huffman树HT，求出Huffman编码HC
    HTNode *HT;
    HCode HC;
    HuffmanCoding(HT, HC, set, n);
    
    //由编码HC进行文件压缩
    fseek(file_origin, 0, SEEK_SET);
    unsigned char *bitstream = new unsigned char[50000000];
    int Byte_pos = 0;
    int bit_left = 8;
    char *code;
    for (i = 0; i < size; i++)
    {
        ch = fgetc(file_origin);
        code = Search(HC, set, n, (unsigned char)ch);
        WriteBitstream(bitstream, Byte_pos, bit_left, code);
    }
    fclose(file_origin);
    if (bit_left != 8)
    {
        *(bitstream + Byte_pos) <<= bit_left;
    }
    int bit_num = Byte_pos * 8 + (8 - bit_left);
    int byte_num = bit_left == 8 ? Byte_pos : Byte_pos + 1;
    FILE *file_compressed = fopen(COMPRESSED, "wb");
    fwrite(bitstream, 1, byte_num, file_compressed);
    for (i = 1; i <= n; i++)
    {
        fwrite(bitstream, 1, strlen(HC[i]), file_compressed);
    }
    fclose(file_compressed);


    //由Huffman树HT进行文件解压缩
    FILE *file_extract = fopen(EXTRACT, "wb");
    file_compressed = fopen(COMPRESSED, "rb");
    fread(bitstream, 1, byte_num, file_compressed);
    fclose(file_compressed);
    Extract(bitstream, bit_num, HT, 2*n-1, set, file_extract);
    fclose(file_extract);
    return 0;
}
