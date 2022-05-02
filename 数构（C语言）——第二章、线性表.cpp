数据结构三要素：逻辑结构、数据的运算、存储结构（物理结构）。存储结构不同，运算的实现方式不同。

# 一、线性表的定义——逻辑结构
线性表是具有相同（每个数据元素所占空间一样大）数据类型的$n(n\geq 0)$个数据元素的有限序列（有次序），其中n为表长，当n=0时线性表是一个空表。
若用L命名线性表，则其一般表示为$L=(a_{1},a_{2},...,a_{i},a_{i+1},...,a_{n})$

概念：

1、$a_{i}$是线性表中的“第i个”元素线性表中的位序。注意：位序从1开始，数组下标从0开始

2、$a_{1}$是表头元素，$a_{n}$是表尾元素。

3、线性表中，第一个元素没有直接前驱，最后一个元素没有直接后继。

4、除第一个元素外，每个元素有且仅有一个直接前驱；除最后一个元素外，每个元素有且仅有一个直接后继。

# 二、线性表的基本操作（记忆思路：创销增删改查）——运算
## **1**、InitList(&L)：
初始化线性表。构造一个空的线性表L，分配内存空间。

## **2**、DestroyList(&L)：
销毁线性表，并释放线性表L所占的内存空间。（从无到有，从有到无）

## **3**、InsertList(&L,i,e)：
插入操作。在线性表L中的第i个位置上插入指定元素e。
 **实现步骤**：
 ①将第 n 至第 i 位的元素向后移动一个位置；
 ②将要插入的元素写到第 i 个位置；
 ③表长加 1。
== 注意==：事先应判断: 插入位置 i 是否合法?表是否已满? 
 应当符合条件： 1≤i≤n+1 或 i=[1, n+1]

```c
//核心语句：
			for (j=n; j>=i; j--)
				a[j+1]=a[ j ]; 
			a[ i ]=x; 
			n++;
```

## **4**、DeleteList(&L,i,&e)：
删除操作。删除线性表L中第i个位置的元素，并用e返回删除元素的值。
**实现步骤**：
 ①将第 i+1 至第 n 位的元素向前移动一个位置；
 ②表长减 1。
== 注意==：事先需要判断，删除位置 i 是否合法?
 应当符合条件：1≤i≤n 或 i=[1, n]

```c
//核心语句：
			for ( j=i+1; j<=n; j++ )
				a[j-1]=a[j]; 
			n--;
```

## **5**、LocateElem(L,e)：
按值查找。在线性表L中查找具有给定关键字值的元素。

## **6**、GetElem(L,i)：
按位查找。获取线性表L中第i个位置的元素的值。

## **7**、LengthList(L)：
求线性表长度，即L中数据元素的个数。

## **8**、DispList(L)：
输出操作。按前后顺序输出线性表L的所有元素值。

## **9**、EmptyList(L)：
判空操作。若L为空表，则返回true，否则返回false。

**==重点重点重点！！！==**理解什么时候要传入参数的引用符号“&”——对参数的修改结构需要“带回来”


```c
#include<stdio.h>

void test(int &x)  // 传入引用符号“&”
{
    x=1024;
    printf("test函数内部x=%d\n",x);
}

int main()
{
    int x=1;
    printf("调用test前 x=%d\n",x);
    test(x);
    printf("调用test后 x=%d\n",x)
    return 0;
}
```

```c
调用test前 x=1
test函数内部x=1024
调用test后 x=1024
```

```c
#include<stdio.h>

void test(int x)  //当不使用引用符号“&”时
{
    x=1024;
    printf("test函数内部x=%d\n",x);
}

int main()
{
    int x=1;
    printf("调用test前 x=%d\n",x);
    test(x);
    printf("调用test后 x=%d\n",x)
    return 0;
}
```

```c
调用test前 x=1
test函数内部x=1024
调用test后 x=1
```

# 三、顺序表
## （一）、定义
线性表的顺序存储是指在内存中用地址连续的一块存储空间顺序存放线性表的各元素，用这种存储形式的线性表称为**顺序表**。

特点：用顺序存储的方式实现线性表顺序存储。把逻辑上相邻的元素存储在物理位置上也相邻的存储单元中，元素之间的关系由存储单元的邻接关系来体现。

每个节点中只存放数据元素

## （二）、静态分配

```c
#include<stdio.h>
//顺序表的实现

//静态分配——大小一旦确定就无法改变
#define MaxSize 10    //定义顺序表的最大长度
typedef int ElemType;    //假定表中数据元素类型是int
typedef struct
{
    int data[MaxSize];    //用静态的“数组”存放数据元素--ElemType表示数据元素的类型int
    int length;    //顺序表的当前长度
}SqList;    //顺序表的类型定义（静态分配方式）

//初始化一个顺序表
void InitList(SqList &L)
{
    L.length=0;
}
```

## （三）、动态分配
==key==:动态申请malloc和释放free内存空间
动态分配语句：L.data=(ElemType *)malloc(sizeof(ElemType)*InitSize); 

malloc函数返回一个指针，需要强制转型为你定义的数据元素类型指针；malloc函数的参数，指明要分配多大的连续内存空间。

**malloc函数和free函数的头文件——># include <stdlib.h>**
```c
#include<stdio.h>
# include <stdlib.h>  //包含了malloc函数和free函数

//动态分配
#define InitSize 10    //默认的最大长度

typedef int ElemType;
typedef struct
{
    int *data;    //指示动态分配数组的指针
    int MaxSize;    //顺序表的最大容量
    int length;    //顺序表的当前长度
}SdqList;

//初始化一个顺序表

//顺序表存满时，可再用malloc动态拓展顺序表的最大容量
void InitList(SdqList *&L)
{
    //用malloc函数申请一片连续的存储空间
    L.data=(int *)malloc(sizeof(int)*InitSize);	//分配存放顺序表的空间
    L.length=0;		//置空顺序表的长度为0
    L.MaxSize=InitSize;
}

//增加动态数组的长度——需要将数据元素复制到新的区域，并用free函数释放原区域
void IncreaseSize(SdqList *&L,int len)
{
    int *p=L.data;
    L.data=(int *)malloc(sizeof(int)*(L.length+len));
    for(int i=0;i<L.length;i++)
    {
        L.data[i]=p[i];    //将数据复制到新区域
    }
    L.MaxSize=L.MaxSize+len;    //顺序表最大长度增加len
    free(p);    //释放原来的内存空间
}
```

## （四）、顺序表的特点
### 1、优点：

(1)、随机访问，即可以在O(1)时间内找到第i个元素。代码实现：data[i-1];(静态、动态都一样)

(2)、存储密度较高，每个节点只存储数据元素

(3)、拓展容量不方便（即便采用动态分配的方式实现，拓展长度的时间复杂度也比较高）

(4)、插入、删除操作不方便，需要移动大量元素

### 2、缺点：

(1)、要求大片连续空间，改变容量不方便
## （五）、顺序表的建立、销毁、判空、求长及输出
### 1、建立顺序表

```c
void CreateList(SdqList *&L,ElemType a[],int n)	//由a中的n个元素建立顺序表
{
	int i=0,k=0;	//k表示L中元素个数，初始值为0
	L=(SDqList *)malloc(sizeof(SDqList));	//分配存放顺序表的空间
	while(i<n)	//i扫描数组a的元素
	{
		L->data[k]=a[i];	//将元素a[i]存放到L中
		k++;
		i++;
	}
	L->length=k;	//设置L的长度为k
}
```
### 2、销毁顺序表

```c
void DestoryList(SdqList *&L)
{
	free(L);	//释放L所指的顺序表空间
}
```

### 3、判断顺序表是否为空

```c
bool EmptyList(SdqList *L)
{
	return (L->length==0);
}
```

### 4、求顺序表长度

```c
int LengthList(SdqList *L)
{
	return (L->length);
}
```

### 5、输出顺序表

```c
void DispList(SdqList *L)
{
	for(int i=0;i<L->length;i++)
		printf("%d",L->data[i]);
	printf("\n");
}
```

## （六）、顺序表的插入删除
在长度为n的顺序表中，插入一个新元素平均需要移动表中n/2个元素，删除一个元素平均需要移动（n-1）/2个元素。
### 1、插入操作
InsertList(&L,i,e)：插入操作。在线性表L中的第i个位置（位序）上插入指定元素e。

插入位置之后的元素都要后移。
顺序表的插入：n 个元素在 i 位插入，应移动（n-i+1）位元素。

时间复杂度：最好O(1)、最坏O(n)、平均O(n)


```c
//用静态分配方式实现顺序表

//插入操作——注意位序、数组下标的关系，并从后面的元素依次移动
bool InsertList(SqList *&L,int i,ElemType e)
{
    if(i<1||i>L.length+1)    //判断i的范围是否有效
        return false;
    if(L.length>=MaxSize)    //当前存储空间已满，不能插入
        return false;
    for(int j=L.length;j>=i;j--)    //将第i个元素及之后的元素后移
        L.data[j]=L.data[j-1];
    L.data[i-1]=e;    //在位置i处放入e
    L.length++;    //长度+1
    return true;	//插入成功
}
```

### 2、删除操作
DeleteList(&L,i,&e)：删除操作。删除线性表L中第i个位置的元素，并用e返回删除元素的值。

删除位置之前的元素都要前移

时间复杂度：最好O(1)、最坏O(n)、平均O(n)

```c
bool DeleteList(SqList *&L , int i ,Elemtype &e)    //注意引用符号“&”
{
    if(i<1 || i>=L.length) 
        return false;    // 判断 i 的范围是否有效 
    e = L.data[i];    //将被删除的元素赋值给e 
    for(int j=i ; j<=L.length ; j++)    //将第 i 个 位置之后的元素前移 
    {    
        L.data[j]=L.data[j+1];     //注意位序、数组下标的关系，并从前面的元素依次移动
    }
    L.length--; // 线性表长度减1 
    return true; 	//删除成功
}
```

### 3、总结注意要点：

1、代码中注意位序i和数组下标的区别

2、注意判断i的合法性

3、移动元素时，从靠前的元素开始？还是从表尾元素开始？

4、理解为什么有的参数需要使用加引用符号“&”

## （七）、顺序表的查找
### 1、按位查找

GetElem(L,i)：按位查找。获取线性表L中第i个位置的元素的值。

用数组下标即可得到第i个元素L.data[i-1]

时间复杂度：最好、最坏、平均都是O(1)

由于顺序表的各个数据元素在内存中连续存放，因此可以根据起始地址和数据元素大小立即找到第i个元素——“随机存取”特性。

```c
int GetElem(SdqList L,int i)
{
	if(i<1||i>L->length)	//参数i错误时返回false
		return false;
    return L.data[i-1];    //注意位序i与数组下标的关系
}
```

### 2、按值查找

LocateElem(L,e)：按值查找。在线性表L中查找具有给定关键字值的元素。

在顺序表L中查找第一个元素值等于e的元素，并返回其位序，从第一个元素开始依次往后检索。

时间复杂度：
最好O(1)---目标元素在第一个位置
最坏O(n)---目标元素在最后一个位置
平均O(n)---目标元素在每个位置的概率相同

```c
//在顺序表L中查找第一个元素值等于e的元素，并返回其位序
int LocateElem(SdqList &L,int e)
{
    for(int i=0;i<L.length;i++)
    {
        if(L.data[i]=e)
            return i+1;    //数组下标为i的元素值等于e，返回其位序i+1
    }
    return 0;    //退出循环，说明查找失败
}
```

# 四、链表
## （一）、单链表
线性表的链式存储，又称**单链表**，它是指通过一组任意的存储单元来存储线性表中的数据元素。为了建立数据元素之间的线性关系，对每个链表节点，除存放元素自身的信息外，还需要存放一个只需其后继的指针。
**链表节点结构**：
线性表中的数据元素可以用任意的一组存储单元来存储，用指针表示逻辑关系，逻辑相邻的两元素的存储空间可以是不连续的。
用链式存储（存储结构）实现了线性结构（逻辑结构），表中各元素的存储地址不一定连续的

一个节点存储一个数据元素，各节点间的先后关系用一个指针表示

每个节点除了存放数据元素外，还要存储指向下一个节点的指针。

**优点：**不要求大片连续空间，改变容量方便

**缺点：**不可随机存取，要耗费一定空间存放指针

==增加一个新的节点==：在内存中申请一个节点所需空间，并用指针p指向这个节点.

初始化语句：LNode *p=(LNode *)malloc(sizeof(LNode));

要表示一个单链表时，只需声明一个头指针L，指向单链表的第一个节点。有以下两种方式：

第一：LNode *L；        //声明一个指向单链表第一个节点的指针
第二：LinkList L；        //声明一个指向单链表第一个节点的指针

LNode等价于struct LNode；*LinkList等价于struct LNode *

```c
//定义一个单链表

typedef int ElemType;
typedef struct LNode    //定义单链表节点类型
{
    int data;    //data为数据域——每个节点存放一个数据元素
    struct LNode *next;    //next为指针域——指针指向下一个节点，存放其后继节点的地址
}LinkNode,*LinkList;	//单链表节点类型

//单链表的实现

//强调这是一个单链表——使用LinkList
//强调这是一个节点+使用LNode *
LinkNode *GetElem(LinkList L,int i)
{
    int j=1;	//计算，初始为1
    LNode *p=L->next;	//头结点指针域赋给p
    if(i==0)	//若i等于0，则返回头结点
        return L;
    if(i<1)		//若i无效，则返回NULL
        return NULL;
    while(p!=NULL&&j<i)	//从第1个节点开始找，查找第i个节点
    {
        p=p->next;
        j++;
    }
    return p;	//返回第i个节点的指针，若i大于表长则返回NULL
}
//时间复杂度为O(n)
```
一般用头指针来标识一个单链表，如单链表L，头指针为NULL时表示一个空表。为了方便运算的实现，在单链表第一个节点之前附加一个结点，称为头结点。头结点的数据域可以不存放任何信息，头结点的指针域指向线性表的第一个元素节点。
==**头结点与头指针的区分**==：不管带不带头结点，头指针始终指向链表的第一个节点，而头结点是带头结点的链表中第一个节点。
==**引入头结点的优点**==：**1**、由于第一个数据节点的位置被存放在头结点的指针域中，所以在链表的第一个位置上的操作和在表中的其他位置上的操作一样；**2**、无论链表是否为空，其头指针都指向头结点的非空指针（空表中头结点的指针域为空）
==**如何表示空表？**==
（1）无头结点时，当头指针的值为空时表示空表即L==NULL；
（2）有头结点时，当头结点的指针域为空时表示空表即L->next==NULL。
### 1、不带头结点的的单链表

```c
typedef int ElemType;
typedef struct LNode    //定义单链表节点类型
{
    int data;    //数据域——每个节点存放一个数据元素
    struct LNode *next;    //指针域——指针指向下一个节点
}LinkNode,*LinkList;

//初始化一个空的单链表
bool InitList(LinkList &L)
{
    L=NULL;    //空表，暂时还没有任何节点——防止脏数据
    return true;
}

//判断单链表是否为空
bool EmptyList(LinkList L)
{
    if(L==NULL)
        return true;
    else
        return false;
    //return (L==NULL);
}

```

### 2、带头结点的单链表

```c
typedef int ElemType;
typedef struct LNode    //定义单链表节点类型
{
    int data;    //数据域——每个节点存放一个数据元素
    struct LNode *next;    //指针域——指针指向下一个节点
}LinkNode,*LinkList;

//初始化一个单链表（带头结点）
bool InitList(LinkList &L)
{
    L=(LinkNode *)malloc(sizeof(LinkNode));    //分配一个头结点
    if(L==NULL)    //内存不足，分配失败
        return false;
    L->next=NULL;    //创建头结点，其next域置为NULL，头结点之后暂时还没有节点
    return true;
}
```
## （二）、单链表的销毁、判空及输出
### 1、销毁单链表

```c
void Destroy(LinkNode *&L)
{
	LinkNode *pre=L,*p=L->next;	//pre（头结点）指向节点p（首结点）的前驱节点
	while(p!=NULL)	//扫描单链表L
	{
		free(pre);	//释放pre节点
		pre=p;		//pre、p同步后移一个节点
		p=pre->next;
	}
	free(pre);	//循环结束时p为NULL，pre指向尾结点，释放它
}
```

### 2、判断单链表是否为空

```c
bool EmptyList(LinkNode *L)
{
	return (L->next==NULL);
}
```

### 3、输出单链表

```c
void DispList(LinkList *L)
{
	LinkNode *p=L->next;	//p指向首结点
	while(p!=NULL)	//p不为空，输出p节点的data域
	{
		printf("%d",p->data);
		p=p->next;		//p移向下一个节点
	}
	printf("\n");
}
```

## （三）、单链表的插入删除
### 1、插入操作
InsertList(&L,i,e)：插入操作。在线性表L中的第i个位置（位序）上插入指定元素e。找到第i-1个节点，将新节点插入其后。
将值为x的新节点插入到单链表的第i个位置上。先检查插入位置的合法性，然后找到待插入位置的前驱节点，即第i-1个节点，再在其后插入新节点。

```c
//顺序不能颠倒
s->next=p->next;//1
p->next=s;//2
```

![在这里插入图片描述](https://img-blog.csdnimg.cn/d8782d1d6f0742e0994b968dbfe175ce.png)
#### ​(1)、按位序插入
##### 带头结点
```c
typedef int ElemType;
typedef struct LNode    //定义单链表节点类型
{
    int data;    //数据域——每个节点存放一个数据元素
    struct LNode *next;    //指针域——指针指向下一个节点
}LinkNode,*LinkList;

//在第i个位置插入元素e（带头结点）
bool InsertList(LinkList &L,int i,ElemType e)
{
	if(i<1)
		return false;
	//按位查找
	LinkNode *p;	//指针p指向当前扫描到的节点
	int j=0;	//当前指针p指向的是第几个节点
	p=L;	//L指向头结点，头结点是第0个节点（不存数据）
	while(p!=NULL&&j<i-1)	//循环找到第i-1个节点
	{
		p=p->next;
		j++;
	}
	//后插操作
	if(p==NULL)	//i值不合法
		return false;
	LinkNode *s=(LinkNode *)malloc(sizeof(LinkNode));
	s->data=e;
	s->next=p->next;//1
	p->next=s;	//2-将节点s连到p之后
	return 0;	//插入成功
}
```
##### 不带头结点
```c
typedef int ElemType;
typedef struct LNode    //定义单链表节点类型
{
    int data;    //数据域——每个节点存放一个数据元素
    struct LNode *next;    //指针域——指针指向下一个节点
}LinkNode,*LinkList;

//在第i个位置插入元素e（不带头结点）
bool InsertList(LinkList &L,int i,ElemType e)
{
	if(i<1)
		return false;
	if(i==1)	//插入第1个节点的操作与其他节点操作不同
	{
		LinkNode *s=(LinkNode *)malloc(sizeof(LinkNode));
		s->data=e;
		s->next=L;
		L=s;	//头结点指向新节点
		return true;	//插入成功
	}
	LinkNode *p;	//指针p指向当前扫描到的节点
	int j=1;	//当前指针p指向的是第几个节点
	p=L;	//L指向头结点，头结点是第0个节点（不存数据）
	while(p!=NULL&&j<i-1)	//循环找到第i-1个节点
	{
		p=p->next;
		j++;
	}
	//后插操作
	if(p==NULL)	//i值不合法
		return false;
	LinkNode *s=(LinkNode *)malloc(sizeof(LinkNode));
	s->data=e;
	s->next=p->next;
	p->next=s;	//将节点s连到p之后
	return 0;	//插入成功
}
```
==**算法思路**==： **1**.取指向插入位置的前驱结点 的指针 ① p=GetElem(L,i-1); **2**.令新结点*s的指针域指 向*p 的后继结点 ② s->next=p->next; **3**.令结点*p 的指针域指 向新插入的结点*s③ p->next=s;
```c
bool InsertList(LInkList &L , int i ,ElemType e)
{ 
	if( i<1 || i>=L.length) 
		return false; 
	int j = 1; 
	LinkNode *p = L->next , *s; 
	s = (LinkNode*)malloc(sizeof(LinkNode)); 
	while (p!=NULL&&j<i-1) 
	{ 
		p=p->next; 
		j++; 
	}
	s->next = p->next; //2
	p->next = s; //3
	return true; 
}
```
#### (2)、指定节点的后插操作
对于一个具有n个节点的单链表，在已知所指节点后插入一个新节点的时间复杂度是（O(1)）；在给定值为x的节点后插入一个新节点的时间复杂度是（O(n)）.
```c
typedef int ElemType;
typedef struct LNode    //定义单链表节点类型
{
    int data;    //数据域——每个节点存放一个数据元素
    struct LNode *next;    //指针域——指针指向下一个节点
}LinkNode,*LinkList;

//后插操作：在p节点之后插入元素e
bool InsertNextList(LinkNode *p,ElemType e)
{
	if(p==NULL)
		return false;
	LinkNode *s=(LinkNode *)malloc(sizeof(LinkNode));
	if(s==NULL)	//内存分配失败
		return false;
	s->data=e;	//用节点s保存数据元素e
	s->next=p->next;
	p->next=s;	//将节点s连到p之后
	return true;	//插入成功
}
```
#### (3)、指定节点的前插操作
前插操作是指在某节点的前面插入一个新节点。仍然*s插入到*p的后面，然后将p->data和s->data交换，这样实现了新节点*s插入到了节点*p的前面。
```c
typedef int ElemType;
typedef struct LNode    //定义单链表节点类型
{
    int data;    //数据域——每个节点存放一个数据元素
    struct LNode *next;    //指针域——指针指向下一个节点
}LinkNode,*LinkList;

//前插操作：在p节点之前插入元素e
bool InsertNextList(LinkNode *p,ElemType e)
{
	if(p==NULL)
		return false;
	LinkNode *s=(LinkNode *)malloc(sizeof(LinkNode));
	if(s==NULL)	//内存分配失败
		return false;
	s->next=p->next;//1
	p->next=s;	//2-将节点s连到p之后

	//交换两个值
	e=p->data;//3
	p->data=s->data;//4
	s->data=e;//5
	//s->data=p->data;	//将p中元素值复制到s中
	//p->data=e;	//p中元素值覆盖到e
	return true;	//插入成功
}
```
### 2、删除操作
DeleteList(&L,i,&e)：删除操作。删除线性表L中第i个位置的元素，并用e返回删除元素的值。找到第i-1个节点，将其指针指向第i+1个节点并释放第i个节点。
将单链表的第i个节点删除。先检查删除位置的合法性，后查找表中第i-1个节点，即被删除节点的前驱节点，再将其删除。
![在这里插入图片描述](https://img-blog.csdnimg.cn/0f8553dee9c1421f9021e7f2eef40ddd.png)

#### (1)、按位序删除（带头结点）
```c
typedef int ElemType;
typedef struct LNode    //定义单链表节点类型
{
    int data;    //数据域——每个节点存放一个数据元素
    struct LNode *next;    //指针域——指针指向下一个节点
}LinkNode,*LinkList;

bool DeleteList(LinkList &L,int i,ElemType &e)	//引用符号“&”
{
	if(i<1)
		return false;
	LinkNode *p;	//指针p指向当前扫描到的节点
	int j=0;	//当前指针p指向的是第几个节点
	p=L;	//L指向头结点，头结点是第0个节点（不存数据）
	while(p!=NULL&&j<i-1)	//循环找到第i-1个节点
	{
		p=p->next;
		j++;
	}
	if(p==NULL)	//i值不合法
		return false;
	if(p->next==NULL)	//第i-1个节点之后已无其他节点
		return false;
	LinkNode *q=p->next;	//1-令q指向被删除节点——首先保存b的指针q，靠它才能找到c
	e=q->data;	//用e返回元素的值
	p->next=q->next;	//2-将*q节点从链中断开，将a、c两节点相连
	free(q);	//释放节点b的存储空间
	return true;	//删除成功
}
```
==**算法思路**==： **1**.取指向删除位置的前驱结点 的指针 p=GetElem(L,i-1); **2**.取指向删除位置的指针 q=p->next; **3**.p 指向结点的后继指向被删除结 点的后继 p->next=q->next ;**4**.释放删除结点 free(q)

```c
bool LinkListDelete(LInkList &L , int i ,ElemType &e)
{ 
	if( i<1 || i>=L.length) 
		return false; 
	int j = 1; 
	LinkNode *p = L->next ，*q ;
	while (p!=NULL&&j<i-1) 
	{ 
		p=p->next; 
		j++; 
	}
	q = p->next; 	//1-令q指向被删除的节点——q临时保存被删节点
	p->next = q->next; 	//2-将*q节点从链中断开
	e = q->data; //3
	free(q); 	//4-释放节点的内存空间
	return true; 
}
```

#### (2)、指定节点的删除
删除指定节点靠一根指针没有办法完成的，必须要借助第二根指针。
```c
typedef int ElemType;
typedef struct LNode    //定义单链表节点类型
{
    int data;    //数据域——每个节点存放一个数据元素
    struct LNode *next;    //指针域——指针指向下一个节点
}LinkNode,*LinkList;

//删除指定节点p
bool DeleteNode(LNode *p)
{
	if(p==NULL)	//i值不合法
		return false;
	LinkNode *q=p->next;	//1-令q指向被删除节点
	p->data=p->next->data;	//2-和后继节点交换数据域
	p->next=q->next;	//3-将*q节点从链中断开
	free(q);	//4-释放节点的存储空间
	return true;	//删除成功
}
```
## （四）、单链表的查找及求长度
### 1、按位查找
GetElem(L,i)：按位查找。获取线性表L中第i个位置的元素的值。
在单链表中从第一个结点出发，顺指针next域逐个往下搜索，直到找到第i个节点为止，否则返回最后一个指针域NULL
```c
//按位查找，返回第i个元素（带头结点）
LNode *GetElem(LinkList L,int i)
{
	if(i<0)		 //若i无效，则返回 NULL
		return NULL;
	LinkNode *p;	//指针p指向当前扫描到的节点
	int j=0;	//当前指针p指向的是第几个节点
	p=L;	//L指向头结点，头结点是第0个节点（不存数据）
	while(p!=NULL&&j<i)	//循环找到第i个节点
	{
		p=p->next;
		j++;
	}
	return p;	//返回第i个结点的指针，如果i大于表长，直接返回p即可
}
//时间复杂度为O(n)
```
### 2、按值查找
LocateElem(L,e)：按值查找。在线性表L中查找具有给定关键字值的元素。
从单链表的第一个结点开始，由前往后依次比较表中各节点数据域的值，若某节点数据域的值等于给定值e，则返回该节点的指针，若整个单链表中没有这样的节点，则返回NULL
```c
//按值查找，找到数据域==e的节点
LNode *LocateElem(LinkList L,ElemType e)
{
	LinkNode *p=L->next;
	//从第1个结点开始查找 data 域为 e 的结点
	while(p!=NULL&&p->data!=e)
		p=p->next;
	return p;	//找到后返回该节点指针，否则返回NULL
}
//时间复杂度为O(n)
```
### 3、求链表的长度
LengthList(L)：求线性表长度，即L中数据元素的个数。
```c
//求表的长度
int LengthList(LinkList L)
{
	int len=0;
	LinkNode *p=L;	//p指向头结点，len置为0（即头结点的序号为0）
	while(p->next!=NULL)
	{
		p=p->next;
		len++;
	}
	return len;	//循环结束，p指向尾结点，其序号len为节点个数
}
```
## （五）、单链表的建立
如果有很多个数据元素，要把它们存到应该单链表里，则先初始化一个单链表，再每次取一个数据元素，插入到表头或表尾。
==核心操作==：初始化操作、指定节点的后插操作
初始化单链表
设置变量length记录链表长度
while循环
{
	每次取一个数据元素e;
	InsertList(L,length+1,e);	插到尾部
	length++;
}
### 1、尾插法
在链表的尾部插入节点建立单链表，数据元素读入顺序和线性表中的逻辑顺序正好相同
增加一个尾指针r，使之指向当前单链表的表尾
```c
LinkList CreatLinkListR(LinkNode *&L)	//正向建立单链表
{ 
	int x;	//设ElemType为整型
	L=(LinkNode)malloc(sizeof(LNode)); 	//建立头结点
	LinkNode *s ,*r = L;	 //r为表尾指针指向表尾——始终指向尾结点，初始时指向头结点
	scanf("%d" , x) ;	 //输入结点的值 
	while(x != 9999)	//输入 9999 表示结束——循环建立数据节点s
	{
		s=(LNode*)malloc(sizeof(LNode)); 
		s->data = x; 
		r->next = s; 	//将节点s插入到节点r之后
		r= s;	//r 指向新的表尾结点 
		scanf("%d" , x); 
	}
	r->next = NULL;		// 尾结点指针置空 
	return L;
```
### 2、头插法
在链表的头部插入节点建立单链表，数据元素读入顺序和线性表中的逻辑顺序正好相反
头插法的重要应用：链表的逆置
```c
LinkList CreatLinkListF(LinkNode *&L,)
{ 
	LinkNode *s ; 	//辅助指针 
	int x ; 
	L=(LinkNode *)malloc(sizeof(LinkNode)) ; 	//创建头结点
	L->next = NULL ;	//初始为空链表 
	scanf("%d" , &x) ;	//输入结点的值 
	while(x != 9999)	//输入 9999 表示结束——循环建立数据节点s
	{ 
		s= (LinkNode*)malloc(sizeof(LinkNode)); // 创建新结点
		s->data = x ; 
		s->next = L->next ;	//将节点s插入到原首节点之前，头结点之后
		L->next = s ;	// 将新结点插入表中，L为头指针
		scanf("%d" , &x) ;		//读入下一个结点值 
	}
	return L; 
}
```
## （六）、双链表
### 1、初始化
**定义**：在单链表的每个节点里再增加一个指向其前驱的指针域prior，这样形成的链表中就有两条方向不同的链，称之为双链表。
双链表节点中有两个指针prior和next，分布指向其前驱节点和后继节点，**头结点的prior、next都指向NULL**
```c
typedef int ElemType;
typedef struct DNode	//定义双链表节点类型
{
	int data;	//数据域
	struct DNode *prior,*next;	//前驱和后继指针
}DLinkNode,*DLinkList;

//初始化双链表（带头结点）
bool InitDLinkList(DLinkList &L)
{
	L=(DLinkNode *)malloc(sizeof(DLinkNode));	//分配一个头结点
	if(L==NULL)	//内存不足，分配失败
		return false;
	L->prior=NULL;	//头结点的prior永远指向NULL
	L->next=NULL;	//头结点之后暂时还没有其他节点
	return true;
}

//判断双链表是否为空（带头结点）
bool EmptyDLinkList(DLinkList L)
{
	if(L->next==NULL)
		return true;
	else
		return false;
	//return (L->next==NULL);
}
```
### 2、建立双链表
#### （1）、尾插法

```c
void CreateListR(DLinkNode *&L,ElemTypea[],int n)
{		//由含有n个元素的数组a创建带头结点的双链表L
	DLinkNode*s,*r;
	L=(DLinkNode *)malloc(sizeof(DLinkNode));	//创建头结点
	r=L;	//r始终指向尾结点，开始时指向头结点
	for(int i=1;i<n;i++)	//循环建立数据节点
	{
		s=(DLinkNode *)malloc(sizeof(DLinkNode));
		s->data=a[i];	//创建数据节点s
		r->next=s;		//将s节点插入到r节点之后
		s->prior=r;
		r=s;		//r指向尾结点
	}
	r->next=NULL;	//尾结点的next域置为NULL
}
```

#### （2）、头插法

```c
void CreateListF(DLinkNode *&L,ElemTypea[],int n)
{		//由含有n个元素的数组a创建带头结点的双链表L
	DLinkNode*s;
	L=(DLinkNode *)malloc(sizeof(DLinkNode));	//创建头结点
	L->prior=L->next=NULL;		//前后指针域置为NULL
	for(int i=1;i<n;i++)	//循环建立数据节点
	{
		s=(DLinkNode *)malloc(sizeof(DLinkNode));
		s->data=a[i];	//创建数据节点s
		s->next=L->next;	//将s节点插入到头结点之后
		if(L->next!=NULL)	//若L存在数据节点，修改L->next的前驱指针
			L->next->prior=s;
		L->next=s;
		s->prior=L;
	}
}
```

### 3、插入操作
#### （1）、后插操作
在双链表中p所指的节点之后插入节点*s
注意新插入节点、前驱节点、后继节点的指针修改
边界情况：新插入节点再最后一个位置
![在这里插入图片描述](https://img-blog.csdnimg.cn/4d9cdb81aef14a9d84b2181b67b23529.png)

```c
//在p节点之后插入s节点
bool InsertDLinList(DLInkList *p,DLInkList *s )
{ 
	if( p==NULL||s==NULL)	//非法参数 
		return false; 
	s->next = p->next; //1
	if(p->next!=NULL)	//如果p节点有后继节点
		p->next->prior = s;//2 
	s->prior = p; //3
	p->next = s; //4
	return true; 
}
```
#### （2）、前插操作
==**注意**==：代码中1和2、3和4的语句顺序可以颠倒，但1、2、3、4之间不能颠倒。
```c
//在p节点之前插入s节点
bool InsertDLinList(DLInkList *p,DLInkList *s )
{ 
	if( p==NULL||s==NULL)	//非法参数 
		return false; 
	s->prior = p->prior; //1
	if(p->prior!=NULL)	//如果p节点有前驱节点
		p->prior->next = s;//2 
	s->next = p; //3
	p->prior = s; //4
	return true; 
}
```

### 4、删除操作（后删）
删除双链表中节点*p的后继结点*q
注意删除节点的前驱节点、后继节点的指针修改
边界情况：如果被删除节点是最后一个数据节点
![在这里插入图片描述](https://img-blog.csdnimg.cn/f3fc80abed5d4bd0a2af9cc61aee8a62.png)

```c
//删除p的后继节点q
bool DeleteNextDLinkList(DLinkList *p)
{ 
	if(p==NULL) 
		return false; 	
	DLinkNode *q = p->next; 	//找到p的后继节点q
	if(p==NULL)		//p没有后继 
		return false;	
	p->next=q->next; //1
	if(q->next!=NULL)	//q节点不是最后一个节点
		q ->next->prior = p;//2 
	free(q); //3
	return true; 
	
	//p->prior->next=p->next;//1
	//p->next->prior=p->prior;//2
	//free(p);//3
}
```
### 5、销毁操作
```c
void DestroyList(DLinkList &L)
{
	//销毁释放各个数据节点
	while(L->next!=NULL)
		DeleteNextDLinkList(L);
	free(L);	//释放头结点
	L=NULL;	//头指针指向NULL
}
```
### 6、遍历
链表不具备随机存取特性，查找操作只能通过顺序遍历实现
#### （1）、后向遍历
```c
while(p!=NULL)
	p=p->next;
```
#### （2）、前向遍历
```c
while(p!=NULL)
	p=p->prior;
```
#### （3）、前向遍历（跳过头结点）
```c
while(p->prior!=NULL)
	p=p->prior;
```
## （七）、循环链表
**循环链表中每一个元素都有后继**
### 1、循环单链表
**单链表**：表尾节点的next指针指向NULL,从一个节点出发只能找到后续的各个节点
**循环单链表**：表尾节点的next指针指向头结点，从一个节点出发可以找到其他任何一个节点
在循环单链表中，若为节点*r的next域指向L，故表中没有指针域为NULL的节点，因此，循环单链表的判空条件表示头结点的指针是否为空，而是它是否等于头指针L。
![在这里插入图片描述](https://img-blog.csdnimg.cn/86a2ae6e26564994b710c1bc0782fed2.png)
==**特点**==：将单链表最后一个节点的指针域由NULL改为指向头结点或线性表中的第一个节点，就得到了单链表形式的循环链表，并称为循环单链表。
分别有带头结点的空循环单链表、带头指针的循环单链表和带尾指针的循环单链表三种。
```c
typedef int ElemType;
typedef struct LNode    //定义单链表节点类型
{
    int data;    //数据域——每个节点存放一个数据元素
    struct LNode *next;    //指针域——指针指向下一个节点
}LinkNode,*LinkList;

//初始化循环单链表
bool InitList(LinkList &L)
{
    L=(LinkNode *)malloc(sizeof(LinkNode));    //分配一个头结点
    if(L==NULL)    //内存不足，分配失败
        return false;
    L->next=L;    //头结点next指向头结点
    return true;
}

//判断循环单链表是否为空
bool EmptyList(LinkList L)
{
	if(L->next==L)
		return true;
	else
		return false;
	//return (L->next==L);
}

//判断节点p是否为循环单链表的表尾节点
//**使用后向/前向遍历实现判断节点p是否是表尾/表头结点**
bool isTail(LinkList L,LinkNode *p)
{
	if(p->next==L)
		return true;
	else
		return false;
}
```
**特点**：**1**、从表中任一节点出发都能访问到表中所有节点；**2**、循环链表是对称的，为了判断起始位置，一般设置头结点；头结点的设置也可将空表和非空表的逻辑状态及运算统一起来。
### 2、循环双链表
**双链表**：表头结点的prior指向NULL，表尾结点的next指向NULL
**循环双链表**：表头结点的prior指向表尾结点，表尾结点的next指向头结点
在循环双链表L中，某节点*p为尾节点时，p->next=L;当循环双链表为空表时某头结点的prior域和next域都等于头指针L。
![在这里插入图片描述](https://img-blog.csdnimg.cn/080e76d30e514e1caa88dc46e243829c.png)
```c
typedef int ElemType;
typedef struct DNode	//定义双链表节点类型
{
	int data;	//数据域
	struct DNode *prior,*next;	//前驱和后继指针
}DLinkNode,*DLinkList;

//初始化空的循环双链表
bool InitDLinkList(DLinkList &L)
{
	L=(DLinkNode *)malloc(sizeof(DLinkNode));	//分配一个头结点
	if(L==NULL)	//内存不足，分配失败
		return false;
	L->prior=L;	//头结点的prior指向头结点
	L->next=L;	//头结点的next指向头结点
	return true;
}

//判断双链表是否为空
bool EmptyDLinkList(DLinkList L)
{
	if(L->next==L)
		return true;
	else
		return false;
	//return (L->next==L);
}

//判断节点p是否为循环双链表的表尾结点
//**使用后向/前向遍历实现判断节点p是否是表尾/表头结点**
bool isTail(DLinkList L,DLinkNode *p)
{
	if(p->next==L)
		return true;
	else
		return false;
}

//插入操作——在p节点之后插入s节点
bool InsertDLinList(DLInkList *p,DLInkList *s )
{ 
	s->next = p->next; 	//将节点*s插入到节点*p之后
	p->next->prior = s; 
	s->prior = p; 
	p->next = s; 
}

//删除p的后继节点q
bool DeleteNextDLinkList(DLinkList *p)
{ 
	p->next=q->next; 
	q ->next->prior = p; 
	free(q); 
}
```
## （八）、静态链表
### 1、什么是静态链表
静态链表：分配一整片连续的内存空间，各个节点集中安置。用数组的方式实现的链表
**优点**：增、删操作不需要大量移动元素
**缺点**：不能随机存取，只能从头结点开始依次往后查找；==容量固定不可变==
### 2、如何定义一个静态链表
```c
#define MaxSize 50 // 静态链表的最大长度
typedef int ElemType // 静态链表的数据类型假定为 int 
typedef struct // 静态链表结构类型的定义 
{ 
	ElemType data; 	//数据域：存储数据元素 
	int next;	//指针域：下一个元素的数组下标
}SLinkList[MaxSize];
```
### 3、基本操作的实现
#### （1）、初始化静态链表
把头结点的next设为-1，把其他节点的next设为特殊值用来表示空节点
#### （2）、查找操作
从头结点出发挨个往后遍历节点
#### （3）、插入操作
插入位序为i的节点：
找到一个空的节点，存入数据元素，从头结点出发找到位序为i-1的节点，修改新节点的next，修改第i-1和节点的next
#### （4）、删除操作
从头结点出发找到前驱节点，修改前驱节点的游标，被删除节点next设为特殊值
# 五、顺序表和链表的比较（总结）
## （一）、逻辑结构
都属于线性表，都是线性结构。
## （二）、物理结构/存储结构
### 1、顺序表（顺序存储）
**优点**：支持随机存取、存储密度高
**缺点**：大片连续空间分配不方便，改变容量不方便
### 2、链表（链式存储）
**优点**：离散的小空间分配方便，改变容量方便
**缺点**：不可随机存取，存储密度低
## （三）、数据的运算/基本操作（创销、增删改查）
### 1、创
**顺序表**：静态分配——静态数组（容量不可改变）；动态分配——动态数组（malloc、free；容量可改变，但需要移动大量元素）
**链表**：只需分配一个头结点（也可以不要头结点，只声明一个头指针）
### 2、销
**顺序表**：静态数组——系统自动回收空间；动态数组——需要手动free
**链表**：依次删除各个节点（free）
==注意==：malloc和free必须成对出现——># include <stdlib.h> 
**创（malloc）**：L.data=(ElemType *)malloc(sizeof(ElemType)*InitSize); 
**销（free）**：free(L.data);
### 3、增删
若线性表的主要操作是在最后一个元素之后插入一个元素，或删除最后一个元素，则采用**顺序表**存储结构最节省运算时间。
**顺序表**：插入/删除元素要将后续元素都后移/前移
**链表**：插入/删除元素只需修改指针即可
### 4、查
**顺序表**：按位查找——O(1)；按值查找——O(n)，若表内元素有序，可在$O(log_{2}n)$时间内找到
**链表**：按位查找——O(n)；按值查找——O(n)
## （四）、用顺序 or 链表
**顺序表**：表长可预估、查询（搜索）操作较多
**链表**：表长难以预估、经常要增加/删除元素


