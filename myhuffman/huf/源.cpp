#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct HuffNode//定义哈夫曼树的结构体
{
	unsigned char b;//值
	long count;//频率
	long parent;//父
	long lch, rch;//左右
	char bits[256];//对应的哈夫曼编码
};
void menu();
int compress();
void reset(HuffNode HuffTreeNode[]);
void rank(HuffNode HuffTreeNode[]);
void generatTree(HuffNode HuffTreeNode[], int n, int m);
void huffmanCode(HuffNode HuffTreeNode[], int n);
int uncompress();
int main()
{
	int id = 0;
	while (1)
	{
		system("cls");
		menu();
		scanf("%d", &id);
	switch (id)
	{
	case 1:
		system("cls");
		compress();
		
		break;
	case 2:
		system("cls");
		uncompress();
		break;
	case 3:
		return 0;
		break;
	}
	}
	compress();
	uncompress();
	return 0;
}
int compress()
{
	time_t start, end;
	HuffNode HuffTreeNode[512];
	int i = 0, j = 0;
	int n = 0, m = 0;
	long min, pt, f;
	unsigned char c;
	long flength = 0;
	long length = 0;
	FILE *ifp, *ofp;
	char filename[255];
	//初始化HUFFTREENODE数组
	reset(HuffTreeNode);
	printf("请输入需要压缩 的文件名:\n");
	getchar();
	gets_s(filename);
	//打开文件并计算权
	ifp = fopen(filename, "rb");
	start = clock();
	if (ifp == NULL)//判断文件是否存在
	{
		printf("\t文件打开失败！\n");
		return 0;
	}
	else
	{
		while (!feof(ifp))//如果文件没有结束则一直读取
		{
			fread(&c, 1, 1, ifp);//读取一个
			HuffTreeNode[c].count++;//记录频率
			flength++;//统计文件长度
		}
		flength--;
		length = flength;//原文件的总长度
		HuffTreeNode[c].count;
	}
	fclose(ifp);
	//对叶节点的权进行从大到小排序
	rank(HuffTreeNode);
	//计算叶节点 分结点
	for (int i = 0; i < 256; i++)//权值计算
	{
		if (HuffTreeNode[i].count == 0)
			break;
		n = i + 1; //n为叶子结点个数;
		m = 2 * n - 1;
	}
	//生成树
	generatTree(HuffTreeNode, n, m);
	//哈弗曼编码
	huffmanCode(HuffTreeNode, n);
	for (i = 0; i < 35; i++)
	{
		
		printf("%d %d  %d  %d %d %d \n", i, HuffTreeNode[i].count, HuffTreeNode[i].parent, HuffTreeNode[i].lch, HuffTreeNode[i].rch,HuffTreeNode[i].bits);
		
	}
	system("pause");
	//对文件进行压缩

	///////////////////////////////////////////////////////


	FILE *ifp1, *ofp1;//ifp1指向源文件,ofp1指向压缩后的文件
	char filename1[255];
	ifp1 = fopen(filename, "rb");//以二进制流形式打开文件读取
	char buf[512];
	unsigned char z;
	buf[0] = 0;
	pt = 8, f = 0;
	j = 0, i = 0;
	printf("请输入压缩后的文件名\n");
	gets_s(filename1);
	strcat(filename1, ".hub");
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
		while (j >= 8)//大于8进行拆分,分成两个字节存储
		{
			for (i = 0; i<8; i++)
			{
				if (buf[i] == '1')
					z = (z << 1) | 1;
				else
					z = z << 1;
			}
			//写入文件ofp
			fwrite(&z, 1, 1, ofp1);
			pt++;
			strcpy(buf, buf + 8);//一个字节一个字节取
			j = strlen(buf);
		}
		if (f == flength)//全部取完结束
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
		fwrite(&z, 1, 1, ofp1);//写入最后一个字节结尾
		pt++;
	}
	fseek(ofp1, 4, SEEK_SET);//移动到第四个字节
	fwrite(&pt, sizeof(long), 1, ofp1);//写入压缩后文件长度,4字节
	fseek(ofp1, pt, SEEK_SET);//移动到末尾
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
	end = clock();//时钟结束
	fclose(ifp1);
	fclose(ofp1);
	printf("\n压缩文件成功！\n");
	printf("压缩率为%f%%\n\n", div * 100);
	printf("所用时间为:%d 毫秒\n", end - start);
	system("pause");
}
void reset(HuffNode HuffTreeNode[])
{
	int i;
	for (i = 0; i<512; i++)
	{
		if (HuffTreeNode[i].count != 0)
		{
			HuffTreeNode[i].b = (unsigned char)i;
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
void rank(HuffNode HuffTreeNode[])
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
void generatTree(HuffNode HuffTreeNode[], int n, int m)
{
	int j, i;
	long pt, min;
	for (i = n; i<m; i++)
	{
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
		HuffTreeNode[i].count = HuffTreeNode[pt].count;
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
void huffmanCode(HuffNode HuffTreeNode[], int n)
{
	int i, j, f;
	for (i = 0; i<n; i++)
	{
		f = i;
		HuffTreeNode[i].bits[0] = 0;
		while (HuffTreeNode[f].parent != -1)
		{
			j = f;
			f = HuffTreeNode[f].parent;
			if (HuffTreeNode[f].lch == j)
			{
				j = strlen(HuffTreeNode[i].bits);
				memmove(HuffTreeNode[i].bits + 1, HuffTreeNode[i].bits, j + 1);
				HuffTreeNode[i].bits[0] = '0';
			}
			else
			{
				j = strlen(HuffTreeNode[i].bits);
				memmove(HuffTreeNode[i].bits + 1, HuffTreeNode[i].bits, j + 1);
				HuffTreeNode[i].bits[0] = '1';
			}
		}
	}
}
int uncompress()
{
	time_t start, end;
	HuffNode HuffTreeNode[512];
	char filename[255], outputfile[255], buf[255], bx[255];
	unsigned char c;
	long i, j, m, n, f, p, l;
	long flength;
	reset(HuffTreeNode);
	FILE *ifp, *ofp;
	printf(" 请输入需要解压缩的文件名\n");
	getchar();
	gets_s(filename);
	ifp = fopen(filename, "rb");
	if (ifp == NULL)
	{
		printf("\n\t文件打开失败!\n");
		return 0;
	}
	printf("将当前目录下解压,请输入解压后的文件及扩展名\n");
	gets_s(outputfile);
	ofp = fopen(outputfile, "wb");
	start = clock();
	if (ofp == NULL)
	{
		printf("解压缩文件失败!\n");
		return 0;
	}


	fread(&flength, sizeof(long), 1, ifp);//读取原文及长度
	fread(&f, sizeof(long), 1, ifp);//读取4个字节的文件长度
	fseek(ifp, f, SEEK_SET);//移动到存储总数的位置
	fread(&n, sizeof(long), 1, ifp);//读取节点总数



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
			f = c;//转十进制
			itoa(f, buf, 2);//转为二进制
			f = strlen(buf);//不足8位补0
			for (l = 8; l > f; l--)
			{
				strcat(HuffTreeNode[i].bits, "0");//先在结点编码补0
			}
			strcat(HuffTreeNode[i].bits, buf);//链接字符串
		}
		HuffTreeNode[i].bits[p] = 0;//结束符
	}
	HuffNode tmp;
	for (i=0;i<n;i++)//排序结点
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
	p = strlen(HuffTreeNode[n - 1].bits);//编码的最大长度


	fseek(ifp, 8, SEEK_SET);//指针指向存放哈夫曼编码的位置
	m = 0;
	bx[0] = 0;//字符串
	while (1)
	{//根据编码长短,依次解码,从原来的位存储还原到字节
		while (strlen(bx) < (unsigned int)p)
		{
			fread(&c, 1, 1, ifp);//取字节,转成2进制
			f = c;
			itoa(f, buf, 2);
			f = strlen(buf);
			for (l = 8; l > f; l--)//补上0
			{
				strcat(bx, "0");
			}
			strcat(bx, buf);
		}
		for (i = 0; i < n; i++)
		{//找编码
			if (memcmp(HuffTreeNode[i].bits, bx, HuffTreeNode[i].count) == 0)
				break;
		}
		strcpy(bx, bx + HuffTreeNode[i].count);
		//判断编码对应字符
		c = HuffTreeNode[i].b;
		fwrite(&c, 1, 1, ofp);//写入目标文件
		m++;//比较,统计解压后的文件长度
		if (m == flength)break;//源文件长度
	}
	fclose(ifp);
	fclose(ofp);
	end = clock();
	printf(" 解压缩成功\n");
	if (m == flength)
	{
		printf("解压文件与源文件相同\n");
		printf("所需时间为:%d 秒\n", (end - start) / 1000);
		system("pause");
	}
	else
	{
		printf("\t解压文件与源文件不同!\n\n");
		system("pause");
	}
	return 0;
}
void menu()
{
	printf("++++++++++++++++++++++++++++++++++++\n");
	printf("++++++++++++++++++++++++++++++++++++\n");
	printf("++++++++++++++++++++++++++++++++++++\n");
	printf("+        1:压缩                    +\n");
	printf("+        2:解压                    +\n");
	printf("+        3:退出                    +\n");
	printf("++++++++++++++++++++++++++++++++++++\n");
	printf("+          by qhc                  +\n");
	printf("++++++++++++++++++++++++++++++++++++\n");
}
