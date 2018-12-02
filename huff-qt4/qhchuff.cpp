#include "qhchuff.h"
#include "ui_qhchuff.h"
#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"time.h"
#include"windows.h"
struct HuffNode//树的结构
{
        unsigned char b;
        long count;
        long parent;
        long lch, rch;
        char bits[256];
};
int value=0;
void reset(HuffNode HuffTreeNode[])//初始化树
{
        int i;
        for (i = 0; i<512; i++)
        {
                if (HuffTreeNode[i].count != 0)//权值不为0
                {
                        HuffTreeNode[i].b = (unsigned char)i;//存储代表的字
                }
                else
                {
                        HuffTreeNode[i].b = '\0';
                }
                HuffTreeNode[i].parent = -1;
                HuffTreeNode[i].lch = HuffTreeNode[i].rch = -1;
                HuffTreeNode[i].count = 0;
        }
}
void rank(HuffNode HuffTreeNode[])//排序,按权值比较
{
        int i, j;
        HuffNode tmp;
        for (i = 0; i <= 256; i++)
        {
                int k = i;
                for (j = i + 1; j < 256; j++)
                {
                        if (HuffTreeNode[j].count > HuffTreeNode[k].count)
                                k = j;
                }
                if (k != i)
                {
                        tmp = HuffTreeNode[i];
                        HuffTreeNode[i] = HuffTreeNode[k];
                        HuffTreeNode[k] = tmp;
                }
        }
}
void generatTree(HuffNode HuffTreeNode[], int n, int m)//合并树
{
        int j, i;
        long pt, min;
        for (i = n; i<m; i++)
        {
                min = 0x7FFFFFFF;
                for (j = 0; j<i; j++)
                {
                        if (HuffTreeNode[j].parent != -1)//已经在树中,跳过
                                continue;
                        if (min>HuffTreeNode[j].count)
                        {
                                pt = j;
                                min = HuffTreeNode[j].count;
                                continue;
                        }
                }
                HuffTreeNode[i].count = HuffTreeNode[pt].count;//
                HuffTreeNode[pt].parent = i;
                HuffTreeNode[i].lch = pt;
                min = 0x7FFFFFFF;
                for (j = 0; j<i; j++)
                {
                        if (HuffTreeNode[j].parent != -1)
                                continue;
                        if (min>HuffTreeNode[j].count)
                        {
                                pt = j;
                                min = HuffTreeNode[j].count;
                                continue;
                        }
                }
                HuffTreeNode[i].count += HuffTreeNode[pt].count;
                HuffTreeNode[pt].parent = i;
                HuffTreeNode[i].rch = pt;
        }
}
void huffmanCode(HuffNode HuffTreeNode[], int n)//哈夫曼编码
{
        int i, j, f;
        for (i = 0; i<n; i++)
        {
                f = i;
                HuffTreeNode[i].bits[0] = 0;
                while (HuffTreeNode[f].parent != -1)//取叶子节点
                {
                        j = f;
                        f = HuffTreeNode[f].parent;
                        if (HuffTreeNode[f].lch == j)//判断与父节点的关系
                        {
                                j = strlen(HuffTreeNode[i].bits);
                                memmove(HuffTreeNode[i].bits + 1, HuffTreeNode[i].bits, j + 1);//链接
                                HuffTreeNode[i].bits[0] = '0';//左
                        }
                        else
                        {
                                j = strlen(HuffTreeNode[i].bits);
                                memmove(HuffTreeNode[i].bits + 1, HuffTreeNode[i].bits, j + 1);
                                HuffTreeNode[i].bits[0] = '1';//右
                        }
                }
        }
}
int Qhchuff::compress(char* filename)
{
            time_t start, end;
            HuffNode HuffTreeNode[512];
            int i = 0, j = 0;
            int n = 0, m = 0;
            long min, pt, f;
            unsigned char c;
            long flength = 0;
            long length = 0;
            FILE *ifp;
            //初始化HUFFTREENODE数组
            reset(HuffTreeNode);
            //printf("请输入需要压缩 的文件名:");
            //gets(filename);
            //打开文件并计算权
            ifp = fopen(filename, "rb");
            start = clock();
            if (ifp == NULL)
            {
                    printf("\t文件打开失败！\n");
                    return 0;
            }
            else
            {
                    while (!feof(ifp))
                    {
                            fread(&c, 1, 1, ifp);
                            HuffTreeNode[c].count++;
                            flength++;
                    }
                    flength--;
                    length = flength;
                    HuffTreeNode[c].count--;
            }
            fclose(ifp);
            //对叶节点的权进行从大到小排序
            rank(HuffTreeNode);
            //计算叶节点 分结点
            for (int i = 0; i < 256; i++)
            {
                    if (HuffTreeNode[i].count == 0)
                            break;
                    n = i + 1;
                    m = 2 * n - 1;

            }
            //生成树
            generatTree(HuffTreeNode, n, m);
            //哈弗曼编码
            huffmanCode(HuffTreeNode, n);
            //对文件进行压缩

            ///////////////////////////////////////////////////////


            FILE *ifp1, *ofp1;
            char filename1[255];
            strcpy(filename1,"out");
            ifp1 = fopen(filename, "rb");
            char buf[512];
            unsigned char z;
            buf[0] = 0;
            pt = 8, f = 0;
            j = 0, i = 0;
            //printf("\t请输入压缩后的文件名\n");
            //gets(filename1);
            strcat(filename1, ".huf");
            ofp1 = fopen(filename1, "wb");
            fseek(ifp1, 0, SEEK_SET);
            fwrite(&flength, sizeof(int), 1, ofp1);
            fseek(ofp1, 8, SEEK_SET);
            while (!feof(ifp1))
            {
                    z = getc(ifp1);
                    f++;
                    for (i = 0; i<n; i++)
                    {
                            if (z == HuffTreeNode[i].b)
                                    break;
                    }
                    strcat(buf, HuffTreeNode[i].bits);
                    j = strlen(buf);
                    z = 0;
                    while (j >= 8)//大于八进行拆分,分成两个字节存储
                    {
                            for (i = 0; i<8; i++)
                            {
                                    if (buf[i] == '1')
                                            z = (z << 1) | 1;
                                    else
                                            z = z << 1;
                            }
                            //写入文件
                            fwrite(&z, 1, 1, ofp1);
                            pt++;
                            strcpy(buf, buf + 8);
                            j = strlen(buf);
                    }
                    if (f == flength)
                            break;
            }

            if (j>0)
            {
                    strcat(buf, "00000000");
                    for (i = 0; i<8; i++)
                    {
                            if (buf[i] == '1')
                                    z = (z << 1) | 1;
                            else
                                    z = z << 1;
                    }
                    fwrite(&z, 1, 1, ofp1);//写入最后一个字节尾部
                    pt++;
            }
            fseek(ofp1, 4, SEEK_SET);
            fwrite(&pt, sizeof(long), 1, ofp1);//写入压缩后文件长度,4字节
            fseek(ofp1, pt, SEEK_SET);
            fwrite(&n, sizeof(long), 1, ofp1);//写入节点数
            for (i = 0; i<n; i++)
            {
                    fwrite(&(HuffTreeNode[i].b), 1, 1, ofp1);//写入每个结点代表的字符
                    z = strlen(HuffTreeNode[i].bits);
                    fwrite(&z, 1, 1, ofp1);//写入每个字符的哈夫曼编码长度
                    j = strlen(HuffTreeNode[i].bits);//统计哈夫曼编码的长度
                    if (j % 8 != 0)//不足8补0
                    {
                            for (f = j % 8; f<8; f++)
                                    strcat(HuffTreeNode[i].bits, "0");
                    }
                    while (HuffTreeNode[i].bits[0] != 0)//转为2进制
                    {
                            z = 0;
                            for (j = 0; j<8; j++)
                            {
                                    if (HuffTreeNode[i].bits[j] == '1')//通过位数左移符来实现补0
                                            z = (z << 1) | 1;
                                    else
                                            z = z << 1;
                            }
                            strcpy(HuffTreeNode[i].bits, HuffTreeNode[i].bits + 8);//继续转换后面的字符
                            fwrite(&z, 1, 1, ofp1);
                    }
            }
            long length00 = pt--;//压缩后的文件大小
            double div = ((double)flength - (double)length00) / (double)flength;//计算压缩率
            end = clock();
            fclose(ifp1);
            fclose(ofp1);
            printf("\n\t压缩文件成功！\n");
            printf("\t压缩率为%f%%\n\n", div * 100);
            printf("所用时间为:%d 毫秒", end - start);
            return (end - start)/1000;
}

int Qhchuff:: uncompress(char* filename)
{

        time_t start, end;
        HuffNode HuffTreeNode[512];
        char  outputfile[255], buf[255], bx[255];
        unsigned char c;
        long i, j, m, n, f, p, l;
        long flength;
        reset(HuffTreeNode);
        FILE *ifp, *ofp;
        //printf("\t 请输入需要解压缩的文件名");
       // gets(filename);

        ifp = fopen(filename, "rb");
        if (ifp == NULL)
        {
                printf("\n\t文件打开失败!\n");
                return 3;
        }
        printf("\t将当前目录下解压,请输入解压后的文件及扩展名");
        //gets(outputfile);
        strcpy(outputfile,"newfile.bmp");
        ofp = fopen(outputfile, "wb");
        start = clock();
        if (ofp == NULL)
        {
                printf("\n\t 解压缩文件失败!\n");
                return 4;
        }


        fread(&flength, sizeof(long), 1, ifp);//读取原文及长度
        fread(&f, sizeof(long), 1, ifp);//读取4个字节的文件长度
        fseek(ifp, f, SEEK_SET);//移动到存储总数的位置
        fread(&n, sizeof(long), 1, ifp);//读取节点总数


        value=20;
        ui->progressBar->setValue(value);
        for (i = 0; i < n; i++)//重新构造叶子节点
        {
                fread(&HuffTreeNode[i].b, 1, 1, ifp);//读取一个字节,得到一个结点
                fread(&c, 1, 1, ifp);//读取哈夫曼编码长度
                p = (long)c;
                HuffTreeNode[i].count = p;//保存结点的编码长度
                HuffTreeNode[i].bits[0] = 0;//初始编码为0
                if (p % 8 > 0)
                        m = p / 8 + 1;
                else
                        m = p / 8;
                for (j = 0; j < m; j++)
                {
                        fread(&c, 1, 1, ifp);//取出但个字节
                        f = c;
                        itoa(f, buf, 2);//转为二进制
                        f = strlen(buf);//不足8位补0
                        for (l = 8; l > f; l--)
                        {
                                strcat(HuffTreeNode[i].bits, "0");
                        }
                        strcat(HuffTreeNode[i].bits, buf);//链接字符串
                }
                HuffTreeNode[i].bits[p] = 0;//结束符
        }
        HuffNode tmp;
        value=40;
        ui->progressBar->setValue(value);
        for (i=0;i<n;i++)//排序结点,根据编码长度
        {
                for (j = i + 1; j < n; j++)
                {
                        if (strlen(HuffTreeNode[i].bits) > strlen(HuffTreeNode[j].bits))
                        {
                                tmp = HuffTreeNode[i];
                                HuffTreeNode[i] = HuffTreeNode[j];
                                HuffTreeNode[j] = tmp;
                        }
                }
        }
        p = strlen(HuffTreeNode[n - 1].bits);


        fseek(ifp, 8, SEEK_SET);//指针指向存放哈夫曼编码的位置
        m = 0;
        bx[0] = 0;
        value=60;
        ui->progressBar->setValue(value);
        while (1)//根据编码长短,依次解码,从原来的位存储还原到字节
        {
                while (strlen(bx) < (unsigned int)p)
                {
                        fread(&c, 1, 1, ifp);
                        f = c;
                        itoa(f, buf, 2);
                        f = strlen(buf);
                        for (l = 8; l > f; l--)
                        {
                                strcat(bx, "0");//补上0
                        }
                        strcat(bx, buf);
                }
                for (i = 0; i < n; i++)//找编码
                {
                        if (memcmp(HuffTreeNode[i].bits, bx, HuffTreeNode[i].count) == 0)//判断编码对应字符
                                break;
                }
                strcpy(bx, bx + HuffTreeNode[i].count);
                c = HuffTreeNode[i].b;
                fwrite(&c, 1, 1, ofp);
                m++;
                if (m == flength)break;//比较,统计解压后的文件长度
                value=100;
                ui->progressBar->setValue(value);
        }

        fclose(ifp);
        fclose(ofp);
        end = clock();
        printf("\n\t 解压缩成功\n");
        if (m == flength)
        {
                printf("\t解压文件与源文件相同\n\n");
                printf("所需时间为:%d 秒", (end - start) / 1000);
                int time=(end - start) / 1000;
                return 9;
        }
        else
                printf("\t解压文件与源文件不同!\n\n");
        return 0;
}

Qhchuff::Qhchuff(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Qhchuff)
{
    ui->setupUi(this);
    ui->progressBar->setOrientation(Qt::Horizontal);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(0);
}

Qhchuff::~Qhchuff()
{


    delete ui;
}

void Qhchuff::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Qhchuff::on_pushButton_clicked()//压缩文件
{

   value=0;
   QString str=ui->textEdit->toPlainText();
   QByteArray str1=str.toLatin1();
   char* str2;
   int time;
   str2=str1.data();
   compress(str2);
   time=compress(str2);
   value=100;
   ui->progressBar->setValue(value);
   QString time1=QString::number(time,10);
   ui->textEdit->setPlainText("program use  "+time1+"  second");
   Sleep(1000);
    value=0;
    ui->progressBar->setValue(value);

}

void Qhchuff::on_pushButton_2_clicked()//解压缩文件
{
    value=0;
    QString str=ui->textEdit->toPlainText();
    QByteArray str1=str.toLatin1();
    char* str2;
    int time2;
    str2=str1.data();
    time2=uncompress(str2);
    QString time1=QString::number(time2,10);
    ui->textEdit->setPlainText("program use  "+time1+"  second");
    Sleep(1000);
     value=0;
     ui->progressBar->setValue(value);
}

