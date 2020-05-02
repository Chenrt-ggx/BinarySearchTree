//P6136 8.9s
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

int tot;
stu pol[1600000];

int read()
{
	int q=0,w=1;
	char c=getchar();
	while (c>'9' || c<'0')
	{
		if(c=='-') w=-1;
		c=getchar();
	}
	while (c>='0' && c<='9')
	{
		q=q*10+c-'0';
		c=getchar();
	}
	return w*q;
}

int size(ptr now)
{return now?now->siz:0;}

void pushup(ptr now)
{now&&(now->siz=now->con+size(now->ls)+size(now->rs)); return;}

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
		p=&pol[tot++];
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

int main()
{
	ptr root=NULL;
	srand(time(0));
	int n,m,x,y,ans=0,last=0;
	n=read(),m=read();
	while (n--)
	{
		x=read();
		ins(&root,x);
	}
	while (m--)
	{
		x=read(),y=read(),y^=last;
		if (x==1) {ins(&root,y); continue;}
		if (x==2) {del(&root,y); continue;}
		if (x==3)
		{
			last=fnd(root,y)+1;
			ans^=last; continue;
		}
		if (x==4)
		{
			last=kth(root,y);
			ans^=last; continue;
		}
		if (x==5)
		{
			last=qan(root,y,-INF);
			ans^=last; continue;
		}
		if (x==6)
		{
			last=hou(root,y,INF);
			ans^=last; continue;
		}
	}
	printf("%d\n",ans);
	return 0;
}