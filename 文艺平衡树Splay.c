#include <stdio.h>
#include <stdlib.h>
#define INF 2147483647

struct tree
{
	struct tree* fa;
	struct tree* ch[2];
	int siz,tag,data;
};

typedef struct tree stu;
typedef struct tree* ptr;

stu pol[100010];
int tot; ptr root;

inline int size(ptr now)
{return now?now->siz:0;}

inline void pushup(ptr now)
{now&&(now->siz=1+size(now->ch[0])+size(now->ch[1])); return;}

inline void spread(ptr now)
{
	ptr tmp=now->ch[0];
	now->ch[0]=now->ch[1],now->ch[1]=tmp;
	if (now->ch[0]) now->ch[0]->tag^=1;
	if (now->ch[1]) now->ch[1]->tag^=1;
	now->tag=0; return;
}

int whichson(ptr son,ptr father)
{
	if (father==NULL) return 0;
	return father->ch[1]==son;
}

void buildfather(ptr son,ptr father,int flag)
{
	if (son) son->fa=father;
	if (father) father->ch[flag]=son;
	else root=son; return;
}

void rotate(ptr now)
{
	ptr f=now->fa,g=f->fa;
	if (f->tag) spread(f);
	if (now->tag) spread(now);
	int flag=whichson(now,f);
	buildfather(now,g,whichson(f,g));
	buildfather(now->ch[!flag],f,flag);
	buildfather(f,now,!flag);
	pushup(f); return;
}

void splay(ptr src,ptr dst)
{
	ptr f,g;
	while (src->fa!=dst)
	{
		f=src->fa,g=f->fa;
		if (src->fa->fa!=dst)
		whichson(src,f)^whichson(f,g)?
		rotate(src):rotate(f);
		rotate(src);
	}
	pushup(src); return;
}

void ins(ptr* now,ptr f,int num)
{
	if (*now==NULL)
	{
		*now=&pol[tot++],(*now)->tag=0;
		(*now)->siz=1,(*now)->data=num;
		(*now)->ch[0]=(*now)->ch[1]=NULL;
		(*now)->fa=f,splay(*now,NULL); return;
	}
	ins(&(*now)->ch[!((*now)->data>num)],*now,num);
	pushup(*now); return;
}

ptr find(int num)
{
	ptr now=root;
	while (now)
	{
		if (now->tag) spread(now);
		if (size(now->ch[0])+1==num)return now;
		else if (size(now->ch[0])+1<num)
		num-=size(now->ch[0])+1,now=now->ch[1];
		else now=now->ch[0];
	}
	return NULL;
}

void solve(int l,int r)
{
	ptr x=find(l-1);
	ptr y=find(r+1);
	splay(x,NULL),splay(y,x);
	if (root->ch[1]->ch[0])
	root->ch[1]->ch[0]->tag^=1;
	return;
}

void print(ptr now)
{
	if (now->tag) spread(now);
	if (now->ch[0]) print(now->ch[0]);
	if (now->data!=-INF && now->data!=INF)
	printf("%d ",now->data);
	if (now->ch[1]) print(now->ch[1]);
	return;
}

int main()
{
	int n,m,l,r;
	scanf("%d %d",&n,&m);
	ins(&root,root,INF);
	ins(&root,root,-INF);
	for (int i=1;i<=n;i++)
	ins(&root,root,i);
	while (m--)
	{
		scanf("%d %d",&l,&r);
		solve(l+1,r+1);
	}
	print(root),puts("");
	return 0;
}