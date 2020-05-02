#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define INF 2147483647

struct tree
{
	struct tree* ls;
	struct tree* rs;
	int data,val,siz;
};

typedef struct tree stu;
typedef struct tree* ptr;

int size(ptr now)
{
	if (now==NULL) return 0;
	return now->siz;
}

void pushup(ptr now)
{
	if (now==NULL) return;
	now->siz=1;
	now->siz+=size(now->ls);
	now->siz+=size(now->rs);
	return;
}

ptr max(ptr now)
{
	while (now)
	if (now->rs) now=now->rs;
	else break; return now;
}

ptr min(ptr now)
{
	while (now)
	if (now->ls) now=now->ls;
	else break; return now;
}

void splitval(ptr now,int k,ptr* lt,ptr* rt)
{
	if (now==NULL) {*lt=*rt=NULL; return;}
	if (now->data<=k) *lt=now,splitval(now->rs,k,&(now->rs),rt);
	else *rt=now,splitval(now->ls,k,lt,&(now->ls));
	pushup(now); return;
}

void splitsiz(ptr now,int k,ptr* lt,ptr* rt)
{
	if (now==NULL) {*lt=*rt=NULL; return;}
	if (k<=size(now->ls)) *rt=now,splitsiz(now->ls,k,lt,&(now->ls));
	else *lt=now,splitsiz(now->rs,k-size(now->ls)-1,&(now->rs),rt);
	pushup(now); return;
}

ptr merge(ptr* lt,ptr* rt)
{
	if (*lt==NULL) return *rt;
	if (*rt==NULL) return *lt;
	if ((*lt)->val>(*rt)->val)
	{
		(*lt)->rs=merge(&(*lt)->rs,rt);
		pushup(*lt); return *lt;
	}
	(*rt)->ls=merge(lt,&(*rt)->ls);
	pushup(*rt); return *rt;
}

void ins(ptr* now,int num)
{
	ptr l,r,p,tmp;
	splitval(*now,num,&l,&r);
	p=(ptr)malloc(sizeof(stu));
	p->siz=1,p->data=num;
	p->ls=p->rs=NULL,p->val=rand();
	tmp=merge(&l,&p);
	*now=merge(&tmp,&r);
	return;
}

void del(ptr* now,int num)
{
	ptr l,r,mid,p,tmp;
	splitval(*now,num-1,&l,&r);
	splitval(r,num,&mid,&r);
	if (mid==NULL)
	{
		*now=merge(&l,&r);
		return;
	}
	p=mid,mid=merge(&mid->ls,&mid->rs);
	tmp=merge(&l,&mid),free(p);
	*now=merge(&tmp,&r); return;
}

int fnd(ptr *now,int num)
{
	ptr l,r; splitval(*now,num-1,&l,&r);
	int ans=size(l); *now=merge(&l,&r);
	return ans;
}

int kth(ptr *now,int num)
{
	ptr l,r; splitsiz(*now,num,&l,&r);
	int ans=max(l)->data; *now=merge(&l,&r);
	return ans;
}

void qan(ptr *now,int num)
{
	ptr l,r; splitval(*now,num-1,&l,&r);
	printf("%d\n",max(l)->data);
	*now=merge(&l,&r); return;
}

void hou(ptr *now,int num)
{
	ptr l,r; splitval(*now,num,&l,&r);
	printf("%d\n",min(r)->data);
	*now=merge(&l,&r); return;
}

void print(ptr p)
{
	printf("data:%d,siz:%d,",p->data,p->siz);
	printf("val:%d  ",p->val);
	return;
}

void printfst(ptr now)
{
	if (now)
	{
		print(now);
		if (now->ls) printfst(now->ls);
		if (now->rs) printfst(now->rs);
	}
	else printf("NULL");
	return;
}

void printmid(ptr now)
{
	if (now)
	{
		if (now->ls) printmid(now->ls);
		print(now);
		if (now->rs) printmid(now->rs);
	}
	else printf("NULL");
	return;
}

void printlst(ptr now)
{
	if (now)
	{
		if (now->ls) printlst(now->ls);
		if (now->rs) printlst(now->rs);
		print(now);
	}
	else printf("NULL");
	return;
}

int main()
{
	int t,x,y;
	ptr root=NULL;
	srand(time(0));
	scanf("%d",&t);
	while (t--)
	{
		scanf("%d",&x);
		if (x==1) {scanf("%d",&y),ins(&root,y); continue;}
		if (x==2) {scanf("%d",&y),del(&root,y); continue;}
		if (x==3) {scanf("%d",&y),printf("%d\n",fnd(&root,y)+1); continue;}
		if (x==4) {scanf("%d",&y),printf("%d\n",kth(&root,y)); continue;}
		if (x==5) {scanf("%d",&y),qan(&root,y); continue;}
		if (x==6) {scanf("%d",&y),hou(&root,y); continue;}
		if (x==7) {printfst(root),puts(""); continue;}
		if (x==8) {printmid(root),puts(""); continue;}
		if (x==9) {printlst(root),puts(""); continue;}
	}
	return 0;
}