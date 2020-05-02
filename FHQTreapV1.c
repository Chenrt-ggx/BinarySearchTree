#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define INF 2147483647

struct tree
{
	struct tree* ls;
	struct tree* rs;
	int data,val,siz,con;
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
	now->siz=now->con;
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
	if (l && (p=max(l))->data==num)
	{
		splitval(l,num-1,&l,&p);
		p->con++,pushup(p);
	}
	else
	{
		p=(ptr)malloc(sizeof(stu));
		p->siz=p->con=1,p->data=num;
		p->ls=p->rs=NULL,p->val=rand();
	}
	tmp=merge(&l,&p);
	*now=merge(&tmp,&r);
	return;
}

void del(ptr* now,int num)
{
	ptr l,r,mid;
	splitval(*now,num-1,&l,&r);
	splitval(r,num,&mid,&r);
	if (mid && mid->con>1)
	{
		mid->con--;
		pushup(mid);
		r=merge(&mid,&r);
	}
	else if (mid) free(mid);
	*now=merge(&l,&r); return;
}

int fnd(ptr now,int num)
{
	if (now==NULL) return 0;
	if (now->data==num) return size(now->ls);
	if (now->data>num) return fnd(now->ls,num);
	return size(now->ls)+now->con+fnd(now->rs,num);
}

int kth(ptr now,int num)
{
	if (now==NULL) return INF;
	if (size(now->ls)>=num) return kth(now->ls,num);
	if (size(now->ls)+now->con>=num) return now->data;
	return kth(now->rs,num-size(now->ls)-now->con);
}

int qan(ptr now,int num,int ans)
{
	if (now->data>=num)
	{
		if (now->ls==NULL) return ans;
		return qan(now->ls,num,ans);
	}
	if (now->rs==NULL) return now->data;
	return qan(now->rs,num,now->data);
}

int hou(ptr now,int num,int ans)
{
	if (now->data<=num)
	{
		if (now->rs==NULL) return ans;
		return hou(now->rs,num,ans);
	}
	if (now->ls==NULL) return now->data;
	return hou(now->ls,num,now->data);
}

void print(ptr p)
{
	printf("data:%d,con:%d,",p->data,p->con);
	printf("siz:%d,val:%d   ",p->siz,p->val);
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
		if (x==3) {scanf("%d",&y),printf("%d\n",fnd(root,y)+1); continue;}
		if (x==4) {scanf("%d",&y),printf("%d\n",kth(root,y)); continue;}
		if (x==5) {scanf("%d",&y),printf("%d\n",qan(root,y,-INF)); continue;}
		if (x==6) {scanf("%d",&y),printf("%d\n",hou(root,y,INF)); continue;}
		if (x==7) {printfst(root),puts(""); continue;}
		if (x==8) {printmid(root),puts(""); continue;}
		if (x==9) {printlst(root),puts(""); continue;}
	}
	return 0;
}