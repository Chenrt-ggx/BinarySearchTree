#include <stdio.h>
#include <stdlib.h>
#define INF 2147483647

struct tree
{
	struct tree* fa;
	struct tree* ch[2];
	int siz,con,data;
};

typedef struct tree stu;
typedef struct tree* ptr;

ptr root;

int size(ptr now)
{
	if (now==NULL) return 0;
	return now->siz;
}

void pushup(ptr now)
{
	if (now==NULL) return;
	now->siz=now->con;
	now->siz+=size(now->ch[0]);
	now->siz+=size(now->ch[1]);
	return;
}

ptr max(ptr now)
{
	while (now)
	if (now->ch[1]) now=now->ch[1];
	else break; return now;
}

ptr min(ptr now)
{
	while (now)
	if (now->ch[0]) now=now->ch[0];
	else break; return now;
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
		*now=(ptr)malloc(sizeof(stu));
		(*now)->siz=(*now)->con=1,(*now)->data=num;
		(*now)->fa=f,(*now)->ch[0]=(*now)->ch[1]=NULL;
		splay(*now,NULL); return;
	}
	if ((*now)->data==num)
	{
		(*now)->con++; pushup(*now);
		splay(*now,NULL); return;
	}
	ins(&(*now)->ch[!((*now)->data>num)],*now,num);
	pushup(*now); return;
}

void del(ptr now,int num)
{
	if (now==NULL) return;
	if (now->data==num)
	{
		splay(now,NULL);
		if (root->con>1) root->con--;
		else if (root->ch[1])
		{
			ptr cng=min(root->ch[1]);
			splay(cng,now);
			buildfather(now->ch[0],cng,0);
			root=cng,cng->fa=NULL;
			free(now),pushup(root);
		}
		else root=now->ch[0],(root)&&(root->fa=NULL,0);
	}
	else del(now->ch[!(now->data>num)],num);
	return;
}

int fnd(int num)
{
	ptr now=root; while (now)
	{
		if (now->data==num) break;
		now=now->ch[!(now->data>num)];
	}
	splay(now,NULL); return size(root->ch[0]);
}

int kth(int num)
{
	ptr now=root; while (now)
	{
		if (size(now->ch[0])+1<=num && size(now->ch[0])+now->con>=num)
		{splay(now,NULL); return root->data;}
		else if (size(now->ch[0])+now->con<num)
		num-=size(now->ch[0])+now->con,now=now->ch[1];
		else now=now->ch[0];
	}
	return INF;
}

int qan(int num)
{
	ptr x=NULL,now=root; while (now)
	{
		x=now; if (now->data==num) break;
		now=now->ch[!(now->data>num)];
	}
	if (now==NULL)
	{
		splay(x,NULL);
		if (root->data<num) return root->data;
		x=max(root->ch[0]); return x?x->data:-INF;
	}
	splay(now,NULL); now=max(root->ch[0]);
	return now?now->data:-INF;
}

int hou(int num)
{
	ptr x=NULL,now=root; while (now)
	{
		x=now; if (now->data==num) break;
		now=now->ch[!(now->data>num)];
	}
	if (now==NULL)
	{
		splay(x,NULL);
		if (root->data>num) return root->data;
		x=min(root->ch[1]); return x?x->data:INF;
	}
	splay(now,NULL); now=min(root->ch[1]);
	return now?now->data:INF;
}

void print(ptr p)
{
	printf("data:%d,con:%d,",p->data,p->con);
	printf("siz:%d   ",p->siz);
	return;
}

void printfst(ptr now)
{
	if (now)
	{
		print(now);
		if (now->ch[0]) printfst(now->ch[0]);
		if (now->ch[1]) printfst(now->ch[1]);
	}
	else printf("NULL");
	return;
}

void printmid(ptr now)
{
	if (now)
	{
		if (now->ch[0]) printmid(now->ch[0]);
		print(now);
		if (now->ch[1]) printmid(now->ch[1]);
	}
	else printf("NULL");
	return;
}

void printlst(ptr now)
{
	if (now)
	{
		if (now->ch[0]) printlst(now->ch[0]);
		if (now->ch[1]) printlst(now->ch[1]);
		print(now);
	}
	else printf("NULL");
	return;
}

int main()
{
	int t,x,y;
	scanf("%d",&t);
	while (t--)
	{
		scanf("%d",&x);
		if (x==1) {scanf("%d",&y),ins(&root,root,y); continue;}
		if (x==2) {scanf("%d",&y),del(root,y); continue;}
		if (x==3) {scanf("%d",&y),printf("%d\n",fnd(y)+1); continue;}
		if (x==4) {scanf("%d",&y),printf("%d\n",kth(y)); continue;}
		if (x==5) {scanf("%d",&y),printf("%d\n",qan(y)); continue;}
		if (x==6) {scanf("%d",&y),printf("%d\n",hou(y)); continue;}
		if (x==7) {printfst(root),puts(""); continue;}
		if (x==8) {printmid(root),puts(""); continue;}
		if (x==9) {printlst(root),puts(""); continue;}
	}
	return 0;
}