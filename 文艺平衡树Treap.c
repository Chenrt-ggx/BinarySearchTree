#include <time.h>
#include <stdio.h>
#include <stdlib.h>

struct tree
{
	struct tree* ls;
	struct tree* rs;
	int data,val,tag,siz;
};

typedef struct tree stu;
typedef struct tree* ptr;

int tot;
stu pol[100010];

inline int size(ptr now)
{return now?now->siz:0;}

inline void pushup(ptr now)
{now&&(now->siz=1+size(now->ls)+size(now->rs)); return;}

inline ptr newnode(int num)
{
	ptr out=&pol[tot++];
	out->siz=1,out->data=num;
	out->tag=0,out->val=rand();
	out->ls=out->rs=NULL; return out;
}

inline void spread(ptr now)
{
	ptr tmp=now->ls;
	now->ls=now->rs,now->rs=tmp;
	if (now->ls) now->ls->tag^=1;
	if (now->rs) now->rs->tag^=1;
	now->tag=0; return;
}

void split(ptr now,int k,ptr* lt,ptr* rt)
{
	if (now==NULL) {*lt=*rt=NULL; return;}
	if (now->tag) spread(now);
	if (k<=size(now->ls)) *rt=now,split(now->ls,k,lt,&(now->ls));
	else *lt=now,split(now->rs,k-size(now->ls)-1,&(now->rs),rt);
	pushup(now); return;
}

ptr merge(ptr* lt,ptr* rt)
{
	if (*lt==NULL) return *rt;
	if (*rt==NULL) return *lt;
	if ((*lt)->val<(*rt)->val)
	{
		if ((*lt)->tag) spread(*lt);
		(*lt)->rs=merge(&(*lt)->rs,rt);
		pushup(*lt); return *lt;
	}
	if ((*rt)->tag) spread(*rt);
	(*rt)->ls=merge(lt,&(*rt)->ls);
	pushup(*rt); return *rt;
}

void solve(ptr* now,int l,int r)
{
	ptr x,y,z,tmp;
	split(*now,l-1,&x,&y);
	split(y,r-l+1,&y,&z);
	if (y) y->tag^=1;
	tmp=merge(&x,&y);
	*now=merge(&tmp,&z);
	return;
}

void print(ptr now)
{
	if (now->tag) spread(now);
	if (now->ls) print(now->ls);
	printf("%d ",now->data);
	if (now->rs) print(now->rs);
	return;
}

int main()
{
	int n,m,l,r;
	srand(time(0));
	ptr tmp,root=NULL;
	scanf("%d %d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		tmp=newnode(i);
		root=merge(&root,&tmp);
	}
	while (m--)
	{
		scanf("%d %d",&l,&r);
		solve(&root,l,r);
	}
	print(root),puts("");
	return 0;
}