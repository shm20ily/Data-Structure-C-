数据结构三要素：逻辑结构、数据的运算、存储结构（物理结构）。存储结构不同，运算的实现方式不同。
# 一、栈
## （一）、定义——“逻辑结构”
栈是**只允许在一端进行插入或删除操作**的线性表。逻辑结构与普通线性表相同。是一种操作受限的线性表，==**只能在栈顶插入、删除**==
![在这里插入图片描述](https://img-blog.csdnimg.cn/0e69ecbd4fb84db7b98e0a2a21bd5ab8.png)

**重要术语**：
**栈顶（表尾）**：允许插入和删除的一端
**栈底（表头）**：不允许插入和删除的一端
**空栈**：不含任何元素的空表
**栈顶元素**
**进栈/入栈**：栈的插入操作
**出栈/退栈**：栈的删除操作
**特点**：后进先出（LIFO）或先进后出（FILO）
## （二）、基本操作——“运算”
## **1**、InitStack(&S)：
初始化栈。构造一个空栈S，分配内存空间。

## **2**、DestroyStack(&S)：
销毁栈，并释放栈S所占用的内存空间。

## **3**、PushStack(&S,x)：
进栈，若栈S未满，则将x加入使之成为新栈顶。

## **4**、PopStack(&S,&x)：
出栈，若栈S非空，则弹出栈顶元素，并用x返回。删除栈顶元素

## **5**、GetTop(S,&x)：
获得栈顶元素，不删除栈顶元素。若栈S非空，则用x返回栈顶元素。
相当于**查**：栈的使用场景中大多只访问栈顶元素

## **6**、EmptyStack(S)：
判断一个栈S是否为空。若S为空，则返回true，否则返回false。

# 二、顺序栈
用顺序存储结构实现的栈，即利用一组地址连续的存储单元依次存放自栈底到栈顶的数据元素，同时由于栈的操作的特殊性，还必须设一个**位置指针top（栈顶指针）**来动态地指示栈顶元素在顺序栈中的位置
## （一）、用顺序存储方式实现的栈

```c
//顺序栈的定义
#define MaxSize 10	//定义栈中元素的最大个数

typedef int ElemType;
typedef struct
{
	ElemType data[MaxSize];	//静态数组存放栈中元素
	int top;	//栈顶指针
}SqStack;		//顺序栈类型
```
## （二）、基本操作
两种实现方式：
第一、初始化top=-1
第二、初始化top=0
**栈顶指针**：S.top，初始时设置S.top=-1，**栈顶元素**：S.data[S.top]
### 1、创（初始化）
```c
//初始化操作
void InitStack(SqStack *&S)
{
	S.top=-1;	//初始化栈顶指针
	//S.top=0;
}
```
### 2、销毁栈

```c
void DestroyStack(SqQueue *&S)
{
	free(S);
}
```

### 3、增（进栈）
插入元素到栈顶的操作，称为**入栈**
**入栈口诀**：栈顶指针top“先加后压”：S.data[++S.top]=x;	//top=-1
**进栈操作**：栈不满时，栈顶指针先加1，新元素再进栈顶元素
```c
//新元素进栈
bool Push(SqStack *&S,ElemType x)
{
	if(S.top==MaxSize-1)	//栈满
		return false;
	S.top=S.top+1;	//1-指针先加1，或写成：S.top++;
	S.data[S.top]=x;	//2-新元素进栈
	
	//1和2语句可合并为一个语句
	//S.data[++S.top]=x;	//top=-1

	//S.data[S.top++]=x;	//top=0
	return true;
}
```

### 4、删（出栈）
从栈顶删除最后一个元素的操作，称为**出栈**
**出栈口诀**：栈顶指针top“先弹后减”：//x=S.data[S.top--];	//top=-1
**出栈操作**：栈非空时，先取栈顶元素值，再将栈顶指针减1
```c
//出栈操作
bool Pop(SqStack *&S,ElemType &x)
{
	if(S.top==-1)	//栈空
		return false;
	x=S.data[S.top];	//1-栈顶元素先出栈
	S.top=S.top-1;	//2-指针再减1，或写成：S.top--;

	//1和2语句可合并为一个语句
	//x=S.data[S.top--];	//top=-1

	//x=S.data[--S.top];	//top=0
	return true;
}
```

### 5、查（获取栈顶元素）

```c
//获得栈顶元素
bool GetTop(SqStack *&S,ElemType &x)
{
	if(S.top==-1)	//栈空
		return false;
	x=S.data[S.top];	//top=-1——x记录栈顶元素

	x=S.data[S.top-1];	//top=0
	return true;
}
```

### 6、判空、判满
**栈空**：S.top==-1
**栈满**：S.top==MaxSize-1
**栈长**：S.top+1
```c
//判断栈空
bool EmptyStack(SqStack *S)
{
	if(S.top==-1)	//top=-1
		return true;	//栈空
	else		//不为空
		return false;

	//return (S.top==0);		//top=0
}

//判断栈满
bool FULL(SqStack *S)
{
	if(S.top==MaxSize-1)	//top=-1
		return true;	//栈满
	else		//未满
		return false;

	//return (S.top==MaxSize);		//top=0
}
```
## （三）、共享栈（双端栈）
利用了“栈底位置不变，而栈顶位置动态变化”的特性，首先为两个栈申请一个共享的一维数组空间S[MaxSize]，将两个栈的栈底分别放在数组的两端，分别是0、MaxSize-1。
两个栈共享同一片内存空间，两个栈从两边往中间增长。
![在这里插入图片描述](https://img-blog.csdnimg.cn/236de786f4be48a4b27250287489549b.png#pic_center)
==**注意**==：
**1**、操作需要表明是具体栈（top0还是top1）
**2**、**栈空判断**：栈S0——top0=-1；栈S1——top1=MaxSize
**3**、**栈满判断**：当两个栈迎面相遇时才会溢出，即top0+1=top1
### 1、结构定义
```c
#define MaxSize 10	//定义栈中元素的最大个数

typedef int ElemType;
typedef struct
{
	ElemType data[MaxSize];	//静态数组存放栈中元素
	int top0;	//0号栈栈顶指针
	int top1;	//1号栈栈顶指针
}SqStack;
```
### 2、创（初始化）

```c
//初始化操作
void InitStack(SqStack *&S)
{
	S.top0=-1;	//初始化0号栈栈顶指针
	S.top1=MaxSize;		//初始化1号栈栈顶指针
}
```
### 3、增（进栈）

```c
int Push(SqStack *&S,int i,ElemType x)
{
	if(S.top0+1=S.top1)
		return false;
	switch(i)
	{
		case 0:
			S.top0++;
			S->data[S.top0]=x;
			break;
		case 1:
			S.top1--;
			S->data[S.top1]=x;
			break;
		default:
			return false;
	}
	return true;
}
```

### 4、删（出栈）

```c
int Pop(SqStack *&S,int i,ElemType &x)
{
	switch(i)
	{
		case 0:
			if(S.top0==-1)
				return false;
			x=S->data[S.top0];
			S.top0--;
			break;
		case 1:
			if(S.top1==MaxSize)
				return false;
			x=S->data[S.top1];
			S.top1++;
			break;
		default:
			return false;
	}
	return true;
}
```

# 三、链栈
**链栈的优点**：便于多个栈共享存储空间和提高其效率且不存在栈满溢出的情况。
## （一）、用链式存储方式实现的栈
```c
//顺序栈的定义
#define MaxSize 10	//定义栈中元素的最大个数

typedef int ElemType;
typedef struct LinkNode
{
	ElemType data;		//数据域
	struct LinkNode *next;	//指针域
}LinkStack;		//栈类型定义——链栈节点类型
```
## （二）、重要基本操作（带头结点）
### 1、创（初始化）

```c
void InitStack(LinkStack *&s)
{
	s=(LinkStack *)malloc(sizeof(LinkStack));	//创建链栈头结点
	s->next=NULL;		//将next置为NULL
}
```
### 2、销毁栈

```c
void DestroyStack(LinkStack *&s)
{
	LinkStack *pre=s,*p=s->next;	//pre指向头结点，p指向首结点
	while(p!=NULL)		//循环到p为空
	{
		free(pre);		//释放pre节点
		pre=p;		//pre、p同步后移
		p=pre->next;
	}
	free(pre);		//此时pre指向尾结点，释放其空间
}
```

### 3、增（进栈）

```c
void Push(LinkStack *&s,ElemType e)
{
	LinkStack *p;
	p=(LinkStack *)malloc(sizeof(LinkStack));	//新建节点
	p->data=e;		//存放元素e
	p->next=s->next;	//将p节点插入作为首结点
	s->next=p;
}
```

### 4、删（出栈）

```c
bool Pop(LinkStack *&s,ElemType &e)
{
	LinkStack *p;
	if(s->next==NULL)	//栈空的情况
		return false;
	p=s->next;		//p指向首结点
	e=p->data;		//获取首结点的值
	s->next=p->nexxt;	//删除首结点
	free(p);		//释放被删节点的存储空间
	return true;	//删除成功
}
```

### 5、查（获取栈顶元素）

```c
bool GetTop(LinkStack *s,ElemType &e)
{
	if(s->next==NULL)	//栈空的情况
		reutrn false;
	e=s->next->data;	//获取首结点的值
	return true;
] 
```

### 6、判空、判满
**栈满的条件**：由于只有内存溢出时才出现栈满，通常不考虑这样的情况，所以在链栈中可以看成不存在栈满。

```c
//判断栈是否为空
bool EmptyStack(LinkStack *&s)
{
	return (s->next==NULL);
}
```

# 四、队列
## （一）、定义
队列是**只允许在一端进行插入（入队），在另一端进行删除（出队）**的线性表。是一种操作受限的线性表，==只能在队尾插入、在队头删除==
![在这里插入图片描述](https://img-blog.csdnimg.cn/0dfc13c0e148468cad952733d28f0ddf.png)

**重要术语**：
**队头**：允许删除的一端，又称队首
**队尾**：允许插入的一端
**空队列**：队列中没有元素
**队头元素**
**队尾元素**
**入队（进队）**：插入操作
![在这里插入图片描述](https://img-blog.csdnimg.cn/999b4a2cbe104c4aa977a47834ad69f1.png)

**出队（离队）**：删除操作
![在这里插入图片描述](https://img-blog.csdnimg.cn/24986d3abd694443a3c9ac300fdd098a.png)

**特点**：先进先出（FIFO）或后进后出（LILO）
## （二）、基本操作
## **1**、InitQueue(&Q)：
初始化队列。构造一个空队列，分配内存空间。

## **2**、DestroyQueue(&Q)：
销毁队列，并释放队列Q所占用的内存空间。

## **3**、EnQueue(&Q,x)：
入队，若队列Q未满，则将x加入使之成为新的队尾。

## **4**、DeQueue(&Q,&x)：
出队，若队列Q非空，则删除队头元素，并用x返回。

## **5**、GetHead(Q,&x)：
获得队头元素，不删除队头元素。若队列Q非空，则将队头元素赋值给x。
相当于**查**：队列的使用场景中大多只访问队头元素

## **6**、EmptyStack(Q)：
判断一个队列Q是否为空。若队列Q为空，则返回true，否则返回false。
# 五、队列的顺序实现
## （一）、用顺序存储实现队列
队列元素个数：(Q.rear-Q.front+MaxSize)%MaxSize
用静态数组存放数据元素，设置队头（front）、队尾（rear）指针
队列的顺序存储
**第一种方式**：
**1**、队头指针指向队列中队头元素的前一个位置
**2**、队尾指针指向队列中队尾元素位置
**第二种方式**：
**1**、队头指针指向队列中队头元素位置
**2**、队尾指针指向队列中队尾元素的下一个位置

```c
#define MaxSize 10	//定义队列中元素的最大个数

typedef int ElemType;
typedef struct
{
	ElemType data[MaxSize];	//用静态数组存放队列元素
	int front,rear;		//队头指针和队尾指针
}SqQueue;
```
## （二）、基本操作(顺序队列)
### 1、创（初始化）
```c
void InitQueue(SqQueue *&Q)
{
	Q=(SqQueue *)malloc(sizeof(SqQueue));
	Q.front=Q.rear=-1;
}
```
### 2、销毁队列

```c
void DestroyQueue(SqQueue *&Q)
{
	free(Q);
}
```

### 3、增（入队）
**进队操作**：队不满时，新元素先进到队尾元素，再将队尾指针加1
```c
//入队操作（只能从队尾入队即插入）
bool EnQueue(SqQueue *&Q,ElemType e)
{
	if(Q.rear==MaxSize-1)	//队满
		return false;
	Q.rear]++;		//队尾加1
	Q.data[Q.rear]=e;	//rear位置插入元素e
	return true;
}
```

### 4、删（出队）
**出队操作**：队不空时，先取队头元素值，再将队头指针加1
```c
//出队操作（只能让队头元素出队）——删除一个队头元素，并用x返回
bool DeQueue(SqQueue *&Q,ElemType &x)
{
	//队空条件：Q.rear==Q.front
	if(Q.rear==Q.front)		//判断队空
		return false;
	Q.front++;
	e=Q.data[Q.front];
	return true;
}
```

### 5、查（获取队头元素）

```c
//获得队头元素的值，用x返回
bool GetHead(SqQueue *Q,ElemType &x)
{
	if(Q.rear==Q.front)		//判断队空
		return false;
	x=Q.data[Q.front];
	return true;
}
```

### 6、判空、判满（进行增删查操作前的必要判断）
```c
//判断队列是否为空
bool EmptyQueue(SqQueue *Q)
{
	if(Q.rear==Q.front)
		return true;
	else;
		return false;
}
```
不能用Q.rear==MaxSize作为队满的条件
```c
//判断队列是否已满
bool FULLQueue(SqQueue *Q)
{
	return (Q.rear-Q.front=MaxSize);
}
```
### 7、“假溢出”的概念及解决方法
在顺序队列中，当尾指针已经到了数组的上界，不能再又入队操作，但其实数组中还要空位置，这就是“假溢出”。**解决假溢出的途径——采用循环队列。**
## （三）、基本操作（循环队列）
**循环队列**：用模运算（取余）将存储空间再逻辑上变为“环状”。把存储队列元素的表从逻辑上视为一个环，称为**循环队列**。
当队首指针Q.front=MaxSize-1后再前进一个位置就自动到0，者可以利用除法取余运算（%）来实现。
==**确定front、rear指针的指向**==：
**第一种方式**：
**1**、队头指针front——指向队列中队头元素的前一个位置
**2**、队尾指针rear——指向队列中队尾元素位置
**第二种方式**：
**1**、队头指针front——指向队列中队头元素位置
**2**、队尾指针rear——指向队列中队尾元素的下一个位置

> ==**注意**==：队头、队尾指针初始值不同，下面两个语句顺序不同
如果Q.front=Q.rear=0（第一种方式）
则队尾指针进1（入队操作——插入）：
1——Q.rear=(Q.rear+1)%MaxSize;2——Q.data[Q.rear]=x;
队头指针进1（出队操作——删除）：
1——Q.front=(Q.front+1)%MaxSize;2——x=Q.data[Q.front];

>如果Q.front=Q.rear=-1（第二种方式）
则队尾指针进1（入队操作——插入）：
1——Q.data[Q.rear]=x;2——Q.rear=(Q.rear+1)%MaxSize;
队头指针进1（出队操作——删除）：
1——x=Q.data[Q.front];2——Q.front=(Q.front+1)%MaxSize;
### 1、创（初始化）
```c
void InitQueue(SqQueue *&Q)
{
	Q=(SqQueue *)malloc(sizeof(SqQueue));
	Q.front=Q.rear=0;
}
```
### 2、销毁队列

```c
void DestroyQueue(SqQueue *&Q)
{
	free(Q);
}
```

### 3、增（入队）

```c
//入队操作（只能从队尾入队即插入）
bool EnQueue(SqQueue *&Q,ElemType e)
{
	//队列已满的条件：队尾指针的再下一个位置是队头
	//即(Q.rear+1)%MaxSize==Q.front
	
	if((Q.rear+1)%MaxSize==Q.front)	//队满
		return false;
	Q.rear=(Q.rear+1)%MaxSize;	//队尾指针后移——队尾指针加1取模
	Q.data[Q.rear]=x;	//将新元素x插入队尾
	return true;
}
```

### 4、删（出队）

```c
//出队操作（只能让队头元素出队）——删除一个队头元素，并用x返回
bool DeQueue(SqQueue *&Q,ElemType &x)
{
	//队空条件：Q.rear==Q.front
	if(Q.rear==Q.front)		//判断队空
		return false;
	Q.front=(Q.front+1)%MaxSize;	//队头指针后移
	x=Q.data[Q.front];
	return true;
}
```

### 5、查（获取队头元素）

```c
//获得队头元素的值，用x返回
bool GetHead(SqQueue *Q,ElemType &x)
{
	if(Q.rear==Q.front)		//判断队空
		return false;
	x=Q.data[Q.front];
	return true;
}
```

### 6、判空、判满（进行增删查操作前的必要判断）
==**循环队列中判空、判满的方法**==：
**第一、牺牲一个存储单元（少用一个存储单元）**
队空条件：Q.rear=Q.front
队满条件：(Q.rear+1)%MaxSize=Q.front
队列长度：L=(Q.rear-Q.front+MaxSize)%MaxSize
**第二、增加count变量记录队列长度（设置一个计数器）**
队空条件：count=0
队满条件：count=MaxSize
**第三、增加tag=0/1用于标记最近的一次操作是入队/出队（设置一个标志）**
队空条件：Q.rear=Q.front&&tag=0
队满条件：Q.rear=Q.front&&tag=1
```c
//判断队列是否为空
bool EmptyQueue(SqQueue *Q)
{
	if(Q.rear==Q.front)
		return true;
	else;
		return false;
}
```
# 六、队列的链式实现
队列的链式表示称为链队，实际上是一个同时带有队头指针和队尾指针的单链表。头指针指向队头节点，尾指针指向队尾节点，即单链表的最后一个节点。
## （一）、用链式存储实现队列
### 1、带头结点
```c
typedef int ElemType;
typedef struct LinkNode		//链式队列节点
{
	ElemType data;		//存放元素
	struct LinkNode *next;	//下一个节点指针
}LinkNode;	//链队数据节点的类型

typedef struct		//链式队列
{
	LinkNode *front,*rear;	//指向队头和队尾指针
}LinkQueue;		//链队头结点的类型
```
### 2、不带头结点
```c
typedef int ElemType;
typedef struct LinkNode		//链式队列节点
{
	ElemType data;		//存放元素
	struct LinkNode *next;	//下一个节点指针
}LinkNode;	//链队数据节点的类型
```

## （二）、基本操作
### 1、创（初始化）
```c
//初始化队列（带头结点）
void InitQueue(LinkQueue *&Q)
{
	//初始化时 front、rear都指向头结点
	Q.front=Q.rear=(LinkQueue *)malloc(sizeof(LinkQueue));
	Q.front->next=NULL;
}
```
```c
//初始化队列（不带头结点）
void InitQueue(LinkQueue *&Q)
{
	//初始化时 front、rear都指向NULL
	Q.front=NULL;
	Q.rear=NULL;
}
```
### 2、销毁链队
```c
void Destory(LinkQueue *&Q)
{
	LinkNode *pre=Q->front,*p;	//pre指向队首节点
	if(pre!=NULL)
	{
		p=pre->next;	//p指向节点pre的后继节点
		while(p!=NULL)	//循环到p为空
		{
			free(pre);		//释放pre节点的存储空间
			pre=p;		//pre、p同步移动
			p=p->next;
		}
		free(pre);	//释放最后一个数据节点
	}
	free(Q);		//释放链队节点
} 
```
### 3、增（入队）
==**注意**==：第一个元素入队（尾部插入）
```c
//新元素入队（带头结点）
void EnQueue(LinkQueue *&Q,ElemType x)
{
	LinkNode *s=(LinkNode *)malloc(sizeof(LinkNode));	//创建新节点
	s->data=x;
	s->next=NULL;
	Q.rear->next=s;		//新节点s插入到rear之后,并将rear指向它
	Q.rear=s;		//修改队尾指针
}
```
```c
//新元素入队（不带头结点）
void EnQueue(LinkQueue *&Q,ElemType x)
{
	LinkNode *s=(LinkNode *)malloc(sizeof(LinkNode));
	s->data=x;
	s->next=NULL;
	
	if(Q.front==NULL)	//在空队列中插入第一个元素
	{
		Q.front=s;	//修改队头队尾指针
		Q.rear=s;
	}
	else
	{
		Q.rear->next=s;		//新节点插入到rear指针之后
		Q.rear=s;		//修改rear指针
	}
}
```

### 4、删（出队）
==**注意**==：最后一个元素出队（头部删除）
```c
//队头元素出队（带头结点）
bool DeQueue(LinkQueue *&Q,ElemType &x)
{
	if(Q.front==Q.rear)		//链队为空
		return false;
	LinkNode *p=Q.front->next;	//p指向首结点

	if(Q.front==Q.rear)		//链队中只有一个数据节点
		Q.front=Q.rear=NULL;
	else			//链队中有两个及两个以上节点
		Q.front=Q.front->next;	//删除节点
	x=p->data;	//用变量x返回队头元素
	free(p);		//释放节点空间
	return true;
}

//队头元素出队（带头结点）
bool DeQueue(LinkQueue *&Q,ElemType &x)
{
	if(Q.front==Q.rear)		//空队
		return false;
	LinkNode *p=Q.front->next;
	x=p->data;		//用变量x返回队头元素
	Q.front->next=p->next;	//删除——修改头结点的next指针
	
	if(Q.rear==p)	//此次是最后一个节点出队
		Q.rear==Q.front;		//修改rear指针
	free(p);		//释放节点空间
	return true;
}
```

```c
//队头元素出队（不带头结点）
bool DeQueue(LinkQueue *&Q,ElemType &x)
{
	if(Q.front==Q.rear)		//空队
		return false;
	LinkNode *p=Q.front;	//p指向此次出队的节点
	x=p->data;		//用变量x返回队头元素
	Q.front=p->next;	//删除——修改头结点的next指针
	
	if(Q.rear==p)	//此次是最后一个节点出队
	{
		Q.front==NULL;		//front指向NULL
		Q.rear==NULL;		//rear指向NULL
	}
	free(p);		//释放节点空间
	return true;
}
```

### 5、查（获取队头元素）

### 6、判空、判满（进行增删查操作前的必要判断）
空链队的特征：front=rear。不考虑链队满的情况，因为删除时又free动作，除非内存不足。
```c
//判断队列是否为空（带头结点）
bool EmptyQueue(LinkQueue *Q)
{
	if(Q.front==NULL)	//Q.rear==NULL
		return true;
	else
		return false;
	
	//return (Q.front==Q.rear);
}
```

```c
//判断队列是否为空（不带头结点）
bool EmptyQueue(LinkQueue *Q)
{
	if(Q.front==NULL)	//Q.rear==NULL
		return true;
	else
		return false;
}
```
# 七、双端队列
**双端队列**：只允许从==两端插入==、==两端删除==的线性表，是指两端都可以进行入队和出队操作的队列。
**输入受限的双端队列**：只允许从==一端插入==、==两端删除==的线性表
**输出受限的双端队列**：只允许从==两端插入==、==一端删除==的线性表
## （一）、从队尾删除
```c
bool DeQueue(SqQueue *&Q,ElemType &x)
{
	if(Q.front==Q.rear)		队空
		return false;
	x=Q.data[Q.rear];	//获取队尾元素
	Q.rear=(Q.rear-1+MaxSize)%MaxSize;	//修改队尾指针
	return true;
}
```
## （二）、从队头插入
```c
bool EnQueue(SqQueue *&Q,ElemType x)
{
	if((Q.rear+1)%MaxSize==Q.front)		//队满
		return false;
	Q.data[Q.front]=x;		//元素x入队
	Q->front=(Q.front-1+MaxSize)%MaxSize;	//修改队头指针
	return  true;
}
```
# 八、线性表、栈、队的异同点
## （一）、相同点
逻辑结构相同，都是线性的；都可以用顺序存储或链式存储；栈的队列是两种特殊的线性表，即受限的线性表（只是队插入、删除运算加以限制）。
## （二）、不同点
### 1、运算规则不同
线性表为随机存取；而栈是只允许在一端进行插入和删除运算，因而是后进先出表LIFO；队列是只允许在一端进行插入、另一端进行删除运算，因而是先进先出表FIFO。
### 2、用途不同
线性表比较通用；栈用于函数调用、递归和简化设计等；队列用于离散事件模拟、OS作业调度和简化设计等。
# 九、栈的应用
## （一）、括号匹配
**规律**：最后出现的左括号最先匹配（后进先出——LIFO）
**思路**：依次扫描所有字符，遇到左括号入栈；遇到右括号则“==消耗==”一个左括号，即弹出栈顶元素检查是否匹配。
**1**、凡出现左括号，则进栈；
**2**、凡出现右括号，⾸先检查栈是否为空；
若栈空，则表明该“右括弧”多余，否则和栈顶元素比较；
若相匹配，则“左括号出栈” ，否则表明不匹配；
**3**、表达式检验结束时，若栈空，则表明表达式中匹配正确，否则表明“左括号”有余；
**匹配失败的情况**：
**1**、扫描到还存在右括号且栈空——**右括号单身**
**2**、处理完所有括号后，栈非空——**左括号单身**
**3**、左右括号不匹配
```c
#define MaxSize 10	//定义栈中元素的最大个数

typedef struct
{
	char data[MaxSize];		//具体数组存放栈中元素
	int top;	//栈顶指针
}SqStack;	

bool bracketCheck(char str[],int length)
{
	SqStack S;
	InitStack(S);	//初始化一个栈
	for(inti=0;i<length;i++)
	{
		if(str[i]=='('||str[i]=='['||str[[i]=='{')
			Push(S,str[i]);		//扫描的左括号，入栈
		else
		{
			if(EmptyStack(S))	//扫描的右括号且当前栈空
				return false;	//匹配失败
			char topElem;
			Pop(S,topElem);		//栈顶元素出栈
			if(str[i]=='('&&topElem!='(')
				return false;
			if(str[i]=='['&&topElem!='[')
				return false;
			if(str[i]=='{'&&topElem!='{')
				return false;
		}
	}
	return EmptyStack(S);	//检索完全部括号后，栈空说明匹配成功
}
```
## （二）、表达式求值
表达式的标识⽅法：Exp = S1 + OP + S2
由三部分组成：操作数、运算符、界限符
### 1、三种算术表达式
#### （1）、中缀表达式：
S1+OP+S2[==左操作数 运算符 右操作数==]——运算符在两个操作数中间
如：a+b；a+b-c；a+b-c*d
#### （2）、后缀表达式：
S1+S2+OP[==左操作数 右操作数 运算符==]——运算符在两个操作数后面
如：ab+；ab+c-；ab+cd*-
#### （3）、前缀表达式：
OP+S1+S2[==运算符 左操作数 右操作数==]——运算符在两个操作数前面
如：+ab；-+abc；-+ab*cd
### 2、中缀表达式
#### （1）、中缀式转后缀式
从左往右处理各个元素，直到末尾。
**三种特殊情况**：
**1**、遇到操作数，直接加入后缀表达式。
**2**、遇到界限符，遇到‘（’直接入栈；遇到‘）’则依次弹出栈内运算符并加入后缀表达式，直到弹出‘（’为止。==注意：‘（’不加入后缀表达式。==
**3**、遇到运算符，依次弹出栈中优先级高于或等于当前运算符的所有运算符，并加入后缀表达式；若碰到‘（’或栈空则停止。之后再把当前运算符入栈。
处理完所有字符后，将栈中剩余运算符依次弹出，并加入后缀表达式。
#### （2）、中缀表达式求值
初始化两个栈，操作数栈和运算符栈
**1**、若扫描到操作数，压入操作数栈
**2**、若扫描到运算符或界限符，则按照“中缀转后缀”相同的逻辑压入运算符栈（==每当弹出一个运算符时，就需要再弹出两个操作数栈的栈顶元素并执行相应运算，运算结果再压回操作数栈==）
### 3、后缀表达式求值
从左往右扫描，每遇到一个运算符，就让运算符前面最近的两个操作数执行对应运算，合体为一个操作数。**注意**：两个操作数的左右顺序
**步骤一**：==从左往右==扫描下一个元素，直到处理完所有元素
**步骤二**：若扫描到操作数则压入栈，并回到步骤一；否则执行步骤三
**步骤三**：若扫描到运算符，则弹出两个栈顶元素（==注意：先出栈的是“右操作数”==），执行相应运算，运算结果压回栈顶，回到步骤一。
### 4、前缀表达式求值
**步骤一**：==从右往左==扫描下一个元素，直到处理完所有元素
**步骤二**：若扫描到操作数则压入栈，并回到步骤一；否则执行步骤三
**步骤三**：若扫描到运算符，则弹出两个栈顶元素（==注意：先出栈的是“左操作数”==），执行相应运算，运算结果压回栈顶，回到步骤一。
## （三）、栈的应用——递归
**函数调用特点**：最后被调用的函数最先执行结束（LIFO）
函数调用时需要用一个栈存储：
**1**、调用返回地址
**2**、实参
**3**、局部变量


