# 一、串
## （一）、定义
串，即字符串（string）是由零个或多个字符组成的有限序列。引号括起来的字符序列是串的值；可以是字母、数字、中文或其他字符；串中字符的个数n称为串的长度。n=0时的串称为空串。
子串：串中任意个==连续的==字符组成的子序列
主串：包含子串的串
字符在主串中的位置：字符在串中的序号
子串在主串中的位置：子串的第一个字符在主串中的位置
==**注意**==：**位序从1开始而不是从0开始**
**空串**：M=''，是不包含任何字符的串，其长度n为0
空串是任意串的子串；任意串s都是s本身的子串，除s本身外，s的其他子串称为s的真子串。
**空格串**：N='   '，由一个或多个空格组成的串，其长度n为空格字符个数；
串是一种特殊的线性表，数据元素之间呈线性关系；通常以“子串”为增删改查的操作对象。
**两个串相等**当且仅当者两个串的长度相等并且每个对应位置上的字符都相同。
## （二）、基本操作
### 1、StrAssign(&s,cstr)：
串赋值，将字符串常量cstr赋给串s，即生成其值等于cstr的串s
### 2、DestroyStr(&s)：
销毁串，释放为串s分配的存储空间（回收存储空间）
### 3、StrCopy(&s,t)：
串复制，将串t赋给串s
### 4、StrEqual(s,t)：
判断串是否相等，若两个串相等则返回真；否则返回假
### 5、==StrLen(s)==：
求串长，返回串s中字符的个数
### 6、==Strcat(s,t)==：
串连接，返回由两个串s和t连接在一起形成的新串
### 7、SubStr(s,i,j)：
求子串，返回串s中从第i个字符开始的连续j个字符组成的子串
### 8、InsertStr(s1,i,s2)：
子串插入，将串s2插入到串s1的第i个位置，并返回产生的新串
### 9、DelStr(s,i,j)：
子串删除，从串s中删去从第i个字符开始的长度为j的子串，并返回产生的新串
### 10、RepStr(s,i,j,t)：
子串替换，在串s中将第i个字符开始的j个字符构成的子串用串t替换，并返回产生的新串
### 11、DispStr(s)：
串输出，输出串s的所有字符值
### 12、==StrCmp(s,t)==：
比较操作，若串s>串t，则返回值>0；若串s=串t，则返回值=0；若串s<串t，则返回值<0；
### 13、==IndexStr(s,t)==：
定位操作（模式匹配），若主串s中存在域串t值相同的子串，则返回它在主串中第一次出现的位置，否则函数值为0
# 二、串的存储结构
## （一）、串的顺序存储
==**1、定长顺序存储表示**==：用一组地址连续的存储单元存储串值得字符序列，属**静态存储**方式
```c
#define MaxSize 255		//预定义最大串长为255
//静态数组实现（定长顺序存储）
typedef struct
{
	char data[MaxSize];	//每个分量存储一个字符
	int length;		//串的实际长度
}SqString;
```
==**2、堆分配存储表示**==：用一组地址连续的存储单元存储串值得字符序列，但存储空间是在程序执行过程中**动态分配**而得。
```c
//动态数组实现（堆分配存储）
typedef struct
{
	char *data;		//按串长分配存储区，ch指向串的基地址
	int length		//串的长度
}SdqString;
SdqString s;
s.data=(char *)malloc(MaxSize*sizeof(char));
s.length=0;
```
### 1、StrAssign(&s,cstr)：
什么是引用型参数？可参考专栏：[数构（C语言）——第二章、线性表](https://blog.csdn.net/weixin_64215932/category_11791636.html)

==引用型参数==是一个重点！！！一定要会
```c
//将一个字符串常量c（以‘\0’字符标识结尾）赋给顺序串，即生成一个其值等于cstr的串s
void StrAssign(SqString &s,char cstr[])		//s为引用型参数
{
	int i;
	for(i=0;cstr[i]!='\0';i++)
		s.data[i]=cstr[i];
	s.length=i;		//设置串s的长度
}
```
### 2、DestroyStr(&s)：
由于顺序串是之间采用顺序串本身来表示的，而不是顺序串指针，它的存储空间由操作系统管理，即由操作系统分配其存储空间，并在超出作用域时释放其存储空间。此处不包含销毁串的任何操作。
### 3、StrCopy(&s,t)：

```c
//串复制，将串t赋给串s
void StrCopy(SqString &s,SqString t)	//s为引用型参数
{
	int i;
	for(i=0;i<t.length;i++)		//复制t的所有字符
		s.data[i]=t.data[i];
	s.length=t.length;		//设置串s的长度
}
```

### 4、StrEqual(s,t)：

```c
//判断串是否相等，若两个串相等则返回真；否则返回假
bool StrEqual(SqString s,SqString t)
{
	bool same=true;
	int i;
	if(s.length!=t.length)		//长度不等时则返回
		same=false;
	else
		for(i=0;i<s.length;i++)
			if(s.data[i]!=t.data[i])	//有一个对应字符不相同时返回
			{
				same=false;
				break;
			}
	return same;
}
```

### 5、==StrLen(s)==：

```c
//求串长，返回串s中字符的个数
int StrLen(SqString s)
{
	return s.length;
}
```

### 6、==Strcat(s,t)==：

```c
//串连接，返回由两个串s和t连接在一起形成的新串
SqString Strcat(SqString s,SqString t)
{
	SqString str;		//定义结果串str
	int i;
	str.length=s.length+t.length;
	for(i=0;i<s.length;i++)		//将s.data[0..s.length-1]复制到str
		str.data[i]=s.data[i];
	for(i=0;i<t.length;i++)		//将t.data[0..t.length-1]复制到str
		str.data[s.length+i]=t.data[i];
	return str;
}
```

### 7、SubStr(s,i,j)：

```c
//求子串，返回串s中从第i个字符开始的连续j个字符组成的子串。当参数不正确时返回一个空串
SqString SubStr(SqString s,int i,int j)
{
	int k;
	SqString str;		//定义结果串
	str.length=0;		设置str为空串
	if(i<=0||i>s.length||j<0||i+j-1>s.length)
		return str;		//参数不正确时返回空串
	for(k=i-1;k<i+j-1;k++)		//将s.data[0..s.length-1]复制到str
		str.data[k-i+1]=s.data[k];
	str.length=j;
	return str;
}
```

### 8、InsertStr(s1,i,s2)：

```c
//子串插入，将串s2插入到串s1的第i个位置，并返回产生的新串。当参数不正确时返回一个空串
SqString InsertStr(SqString s1,int i,SqString s2)
{
	int j;
	SqString str;		//定义结果串
	str.length=0;		//设置str为空串
	if(i<=0||i>s1.length+1)		//参数不正确时返回空串
		return str;
	for(j=0;j<i-1;j++)		//将s1.data[0..i-2]复制到str
		str.data[j]=s1.data[j];
	for(j=0;j<s2.length;j++)	//将s2.data[0..s2.length-1]复制到str
		str.data[j]=s2.data[j];
	for(j=i-1;j<s1.length;j++)	//将s1.data[i-1..s1.length-1]复制到str
		str.data[s2.length+j]=s1.data[j];
	str.length=s1.length+s2.length;
	return str;
}
```

### 9、DelStr(s,i,j)：

```c
//子串删除，从串s中删去从第i个字符开始的长度为j的子串，并返回产生的新串。当参数不正确时返回一个空串
SqString DelStr(SqString s,int i,int j)
{
	int k;
	SqString s;		//定义结果串
	str.length=0;		//设置str为空串
	if(i<=0||i>s.length||i+j>s.length+1)
		return str;		//参数不正确时返回空串
	for(k=0;k<i-1;k++)		//将s.data[0..i-2]复制到str
		str.data[k]=s.data[k];
	for(k=i+j-1;k<s.length;k++)		//将s.data[i+j-1..s.length-1]复制到str
		str.data[k-j]=s.data[k];
	str.length=s.length-j;
	return str;
}
```

### 10、RepStr(s,i,j,t)：

```c
//子串替换，在串s中将第i个字符开始的j个字符构成的子串用串t替换，并返回产生的新串。当参数不正确时返回一个空串
SqString RepStr(SqString s,int i,int j,SqString t)
{
	int k;
	SqString str;	//定义结果串
	str.length=0;	//设置str为空串
	if(i<=0||i>s.length||i+j-1>s.length)
		return str;		//参数不正确时返回空串
	for(k=0;k<i-1;k++)		//将s.data[0..i-2]复制到str
		str.data[k]=s.data[k];
	for(k=0;k<t.length;k++)		//将t.data[0..t.length-1]复制到str
		str.data[i+k-1]=t.data[k];
	for(k=i+j-1;k<s.length;k++)	//将s,data[i+j-1..s.length-1]复制到str
		str.data[t.length+k-j]=s.data[k];
	str.length=s.length-j+t.length;
	return str;
}
```

### 11、DispStr(s)：

```c
//串输出，输出串s的所有字符值
void DispStr(SqString s)
{
	int i;
	if(s.length>0)
	{
		if(i=0;i<s.length;i++)
			printf("%c",s.data[i]);
		printf("\n");
	}
}
```
### 12、==StrCmp(s,t)==：

```c
//比较操作，若串s>串t，则返回值>0；若串s=串t，则返回值=0；若串s<串t，则返回值<0；
int StrCmp(SqString s,SqString t)
{
	int i;
	fro(i=0;i<s.length&&i<t.length;i++)
		if(s.data[i]!=t.data[i])
			return s.data[i]-t.data[i];
	//扫描过的所有字符都相同，则长度长的串更大
	return s.length-t.length;
}
```

### 13、==IndexStr(s,t)==：

```c
//定位操作（模式匹配），若主串s中存在域串t值相同的子串，则返回它在主串中第一次出现的位置，否则函数值为0
int IndexStr(SqString s,SqString t)
{
	int i=1,n=StrLen(s),m=StrLen(t);
	SqString str;	//定义结果串
	while(i<=n-m+1)
	{
		SubStr(str,s,i,m);
		if(StrCmp(str,t)!=0)
			i++;
		else		//返回子串在主串中的位置
			return i;
	}
	return 0;	//s中不存在与t相等的子串
}
```

## （二）、串的链式存储
==**串的块链存储表示**==：链式方式存储
```c
typedef struct StrNode
{
	char data;		//每个节点存一个字符，存储密度低
	struct StrNode *next;
}LinkStrNode;

typedef struct StrNode
{
	char data[4];		//每个节点存多个字符，提高存储密度
	struct StrNode *next;
}LinkStrNode;
```
### 1、StrAssign(&s,cstr)：

```c
//将一个字符串常量c（以‘\0’字符标识结尾）赋给顺序串，即生成一个其值等于cstr的串s
void StrAssign(LinkStrNode *&s,char cstr[])
{
	int i;
	LinkStrNode *r,*p;
	s=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	r=s;		//r始终指向尾结点
	for(i=0;cstr[i]!='\0';i++)
	{
		p=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		p->data=cstr[i];
		r->next=p;
		r=p;
	}
	r->next=NULL;		//尾结点的next域置为空
}
```

### 2、DestroyStr(&s)：

```c
//销毁串，释放为串s分配的存储空间（回收存储空间）。与销毁头结点单链表运算相同
void DestoryStr(LinkStrNode *&s)
{
	LinkStrNode *pre=s,*p=s->next;	//pre指向结点p的前驱节点
	while(p!=NULL)		//扫描链串s
	{
		free(pre);		//释放pre节点
		pre=p;			//pre、p同步后移一个节点
		p=pre->next;
	}
	free(pre);	//循环结束时p为NULL，pre指向尾结点，释放它
}
```

### 3、StrCopy(&s,t)：

```c
//串复制，将串t赋给串s
void StrCopy(LinkStrNode *&s,LinkStrNode *t)
{
	LinkStrNode *p=t->next,*q,*r;
	s=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	r=s;		//r始终指向尾结点
	while(p!=NULL)		//扫描链串t的所有结点
	{
		q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;	//将p节点复制到q节点
		r->next=q;		//将q节点链接到链串s的末尾
		r=q;
		p=p->next;
	}
	r->next=NULL;		//尾结点的next域置为空
}
```

### 4、StrEqual(s,t)：

```c
//若两个串的长度相等且对应位置的字符均相同，则返回真；否则返回假
bool StrEqual(LinkStrNode *s,LinkStrNode *t)
{
	LinkStrNode *p=s->next,*q=t->next;	//p、q分别扫描链串s和t的数据节点
	while(p!=NULL&&q!=NULL&&p->data==q->data)
	{
		p=p->next;
		q=q->next;
	}
	if(p==NULL&&q==NULL)	//s和t的长度相等且对应位置的字符均相同
		return true;
	else
		return false;
}
```

### 5、==StrLen(s)==：

```c
//求串长，返回串s中字符的个数
int StrLen(LinkStrNode *s)
{
	int i=0;	//i用于累计数据节点的个数
	LinkStrNode *p=s->next;		//p指向链串s的首结点
	while(p!=NULL)		//扫描所有数据节点
	{
		i++;
		p=p->next;
	}
	return i;
}
```

### 6、==Strcat(s,t)==：

```c
//串连接，返回由两个串s和t连接在一起形成的新串
LinkStrNode *Strcat(LinkStrNode *s,LinkStrNode *t)
{
	LinkStrNode *str,*p=s->next;*q,*r;
	str=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	r=str;		//r指向结果串的尾结点
	while(p!=NULL)		//用p扫描s的所有数据节点
	{
		q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;	//将p结点复制到q结点
		r->next=q;		//将q结点链接到str的末尾
		r=q;
		p=p->next;
	}
	p=t->next;
	while(p!=NULL)		//用p扫描t的所有数据节点
	{
		q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;		//将p结点复制到q结点
		r->next=q;			//将q结点链接到str的末尾
		r=q;
		p=p->next;
	}
	r->next=NULL;		//尾结点的next域置为空
	return str;
}
```

### 7、SubStr(s,i,j)：

```c
//求子串，返回串s中从第i个字符开始的连续j个字符组成的子串
LinkStrNode *DelStr(LinkStrNode *s,int i,int j)
{
	int k;
	LinkStrNode *str,*p=s->next,*q,*r;
	str=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	str->next=NULL;		//设置结果串str为空串
	r=str;		//r指向结果串的尾结点
	if(i<=0||i>StrLength(s)||j<0||i+j-1>StrLength(s))
		return str;		//参数不正确时返回空串
	for(k=0;k<i-1;k++)		//将s的co第i个节点开始的j个节点复制到str
	{
		q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;		
		r=q;
		p=p->next;
	}
	for(k=0;k<j;k++)		//让p指向链串s的第i个数据节点
		p=p->next;
	r->next=NULL;		//尾结点的next域置为空
	return str;
}
```

### 8、InsertStr(s1,i,s2)：

```c
//子串插入，将串s2插入到串s1的第i个位置，并返回产生的新串
LinkStrNode *RepStr(LinkStrNode *s,int i,int j,LinkStrNode *t)
{
	int k;
	LinkStrNode *str,*p=s->next,p1=t->next,*q,*r;
	str=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	str->next=NULL;		//设置结果串str为空串
	r=str;		//r指向结果串的尾结点
	if(i<=0||i>StrLength(s)||j<0||i+j-1>StrLength(s))
		return str;		//参数不正确时返回空串
	for(k=0;k<i-1;k++)		//将s的前i-1个数据节点复制到str
	{
		q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;		
		r=q;
		p=p->next;
	}
	while(p1!=NULL)		//将t的所有数据节点复制到str
	{
		q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p1->data;
		r->next=q;		
		r=q;
		p1=p1->next;
	}
	while(p!=NULL)		将p节点及其后的节点复制到str
	{
		q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;			
		r=q;
		p=p->next;
	}
	r->next=NULL;		//尾结点的next域置为空
	return str;
}
```

### 9、DelStr(s,i,j)：

```c
//子串删除，从串s中删去从第i个字符开始的长度为j的子串，并返回产生的新串
LinkStrNode *DelStr(LinkStrNode *s,int i,int j)
{
	int k;
	LinkStrNode *str,*p=s->next,*q,*r;
	str=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	str->next=NULL;		//设置结果串str为空串
	r=str;		//r指向结果串的尾结点
	if(i<=0||i>StrLength(s)||j<0||i+j-1>StrLength(s))
		return str;		//参数不正确时返回空串
	for(k=0;k<i-1;k++)		//将s的前i-1个数据节点复制到str
	{
		q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;		
		r=q;
		p=p->next;
	}
	for(k=0;k<j;k++)		//让p沿next跳j个节点
		p=p->next;
	while(p!=NULL)		将p节点及其后的节点复制到str
	{
		q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		r->next=q;			
		r=q;
		p=p->next;
	}
	r->next=NULL;		//尾结点的next域置为空
	return str;
}
```

### 10、RepStr(s,i,j,t)：

```c
//子串替换，在串s中将第i个字符开始的j个字符构成的子串用串t替换，并返回产生的新串
LinkStrNode *RepStr(LinkStrNode *s,int i,int j,LinkStrNode *t)
{
	int k;
	LinkStrNode *str,*p=s->next,p1=t->next,*q,*r;
	str=(LinkStrNode *)malloc(sizeof(LinkStrNode));
	str->next=NULL;		//设置结果串str为空串
	r=str;		//r指向结果串的尾结点
	if(i<=0||i>StrLength(s)||j<0||i+j-1>StrLength(s))
		return str;		//参数不正确时返回空串
	for(k=0;k<i-1;k++)		//将s的前i-1个数据节点复制到str
	{
		q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		q->next=NULL;
		r->next=q;		
		r=q;
		p=p->next;
	}
	for(k=0;k<j;k++)		//让p沿next跳j个节点
		p=p->next;
	while(p1!=NULL)		//将t的所有数据节点复制到str
	{
		q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p1->data;
		q->next=NULL;
		r->next=q;		
		r=q;
		p1=p1->next;
	}
	while(p!=NULL)		将p所指节点及其后的节点复制到str
	{
		q=(LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data=p->data;
		q->next=NULL;
		r->next=q;			
		r=q;
		p=p->next;
	}
	r->next=NULL;		//尾结点的next域置为空
	return str;
}
```

### 11、DispStr(s)：

```c
//串输出，输出串s的所有字符值
void DispStr(LinkStrNode *s)
{
	LinkStrNode *p=s->next;		//p指向链串s的首结点
	while(p!=NULL)		//扫描s的所有数据节点
	{
		printf("%c",p->data);		//输出p结点值
		p=p->next;
	}
	printf("\n");
}
```

# 三、串的模式匹配
**模式匹配即子串定位运算**：在主串中找到与模式串相同的子串，并返回其所在位置
#### ==IndexStr(s,t)==：
定位操作（模式匹配），若主串s中存在域串t值相同的子串，则返回它在主串中第一次出现的位置，否则函数值为0。
## （一）、简单匹配算法（BF算法）
使用k来记录当前检查的子串起始位置，只要有一个字符不同，就可以停止检查当前子串；所有对应位置的字符都相同，则匹配成功，返回k
```c
int BF(SqString s,SqString t)
{
	int k=1;
	int i=k,j=1;
	while(i<s.length&&j<t.length)		//两个串都没有扫描完时循环
	{
		if(s.data[i]==t.data[j])	//当前比较的两个字符相同
		{
			i++;
			j++;	//继续比较后续字符
		}
		else		//当前比较的两个字符不相同
		{
			k++;	//检查下一个子串
			i=k;	//扫描目的串的i回退
			j=1;	//子串从头开始匹配
		}
	}
	if(j>=t.length)		//j超界，表示串t是串s的子串
		return k;		//返回t在s中的位置
	else			//模式匹配失败
		return 0;
}
```
```c
//教材版代码
int BF(SqString s,SqString t)
{
	int i=0,j=0;
	while(i<s.length&&j<t.length)		//两个串都没有扫描完时循环
	{
		if(s.data[i]==t.data[j])	//当前比较的两个字符相同
		{
			i++;
			j++;	//继续比较后续字符
		}
		else		//当前比较的两个字符不相同
		{
			i=i-j+1
			j=0;	//子串从头开始匹配
		}
	}
	if(j>=t.length)		//j超界，表示串t是串s的子串
		return (i-t.length);		//返回t在s中的位置
	else			//模式匹配失败
		return (-1);
}
```
若主串长度为n，模式串长度为m，则
**1**、比较好的情况：每个子串的第1个字符都和模式串不匹配，
匹配成功的最好时间复杂度：O(m)，
匹配失败的最好时间复杂度：O(n-m+1)=O(n-m)=O(n)
**2**、最坏情况：每个子串的前n-1个字符都和模式串匹配，只有第m个字符不匹配，直到匹配成功/匹配失败最多需要（n-m+1）*m次比较，最坏时间复杂度：O(nm)
## （二）、KMP算法
### 1、求模式串t的next数组
==**next数组**==：当模式串的第j个字符匹配失败时，令模式串跳到next[j]再继续匹配
**串的前缀**：包含第一个字符，且不包含最后一个字符的子串
**串的后缀**：包含最后一个字符，且不包含第一个字符的子串
==**计算方法**==：当第j个字符匹配失败，由前1~j-1个字符组成的串记为s，
则：==**next[j]=s的最长相等前后缀长度+1**==，特别的，==next[1]=0==
```c
//求模式串t的next数组
int GetNext(SqString t,int next[])
{
	int i=0,j=-1;	//i记录t，j记录t[i]之前与t开头相同的字符个数
	next[0]=-1;		//设置next[1]的值
	while(i<t.length)	//循环条件或为j<t.length-1，求t所有位置的next值
	{
		if(j=-1||t.data[i]==t.data[j])	//j=-1或比较的字符相等时
		{
			i++;	//i，j依次移到下一个字符
			j++;
			//若pi=pj，则next[j+1]=next[j]+1
			next[i]=j;
		}
		else	//否则令j=next[j]，循环继续
			j=next[j];	//k回退
	}
}
```
### 2、KMP算法
```c
int KMP(SqString s,SqString t)
{
	int i=0,j=0;
	while(i<s.length&&j<t.length)		//两个串都没有扫描完时循环
	{
		if(j=-1||s.data[i]==t.data[j])	//当前比较的两个字符相同
		{
			i++;
			j++;	//继续比较后续字符
		}
		else
			j=next[j];	//i不变，j后退
	}
	if(j>=t.length)		//匹配成功
		return (i-t.length);		//返回t在s中的位置
	else			//模式匹配失败
		return (-1);
}
```

**KMP算法**：当子串和模式串不匹配时，主串指针i不回溯，模式串指针j=next[j]算法平均时间复杂度：O(n+m)
### 3、改进的KMP算法
```c
int GetNext(SqString t,int nextval[])
{
	int i=0,j=-1;	
	nextval[0]=-1;		
	while(j<t.length)	
	{
		if(j=-1||t.data[i]==t.data[j])	
		{
			i++;
			j++;
			if(t.data[i]!=t.data[j])
				nextval[i]=j;
			else
				nextval[i]=nextval[j];
		}
		else	
			j=nextval[j];
	}
}

int KMP(SqString s,SqString t)
{
	int nextval[MaxSize],i=0,j=0;
	GetNext(t,nextval);
	while(i<s.length&&j<t.length)		
	{
		if(j=-1||s.data[i]==t.data[j])
		{
			i++;
			j++;	
		}
		else
			j=nextval[j];	
	}
	if(j>=t.length)		
		return (i-t.length);		
	else
		return  (-1);
}

```



