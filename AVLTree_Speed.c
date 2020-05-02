//P6136 5.5s
#include <stdio.h>
#include <stdlib.h>
#define INF 2147483647

struct tree
{
	struct tree* ls;
	struct tree* rs;
	int siz,con,data,height;
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

int h(ptr now)
{return now?now->height:0;}

void pushup(ptr now)
{
	if (now==NULL) return;
	now->height=1;
	now->siz=now->con;
	now->siz+=size(now->ls);
	now->siz+=size(now->rs);
	if (h(now->ls)>h(now->rs))
	now->height+=h(now->ls);
	else now->height+=h(now->rs);
	return;
}

void left(ptr* now)
{
	ptr tmp=(*now)->rs;
	(*now)->rs=tmp->ls;
	tmp->ls=*now;
	tmp->siz=(*now)->siz;
	pushup(*now),pushup(tmp);
	*now=tmp; return;
}

void right(ptr* now)
{
	ptr tmp=(*now)->ls;
	(*now)->ls=tmp->rs;
	tmp->rs=*now;
	tmp->siz=(*now)->siz;
	pushup(*now),pushup(tmp);
	*now=tmp; return;
}

void balance(ptr *now)
{
	if (*now==NULL) return;
	if (h((*now)->ls)-h((*now)->rs)==2)
	{
		if (h((*now)->ls->ls)>h((*now)->ls->rs)) right(now);
		else left(&(*now)->ls),right(now); return;
	}
	if (h((*now)->rs)-h((*now)->ls)==2)
	{
		if (h((*now)->rs->rs)>h((*now)->rs->ls)) left(now);
		else right(&(*now)->rs),left(now); return;
	}
	return;
}

void ins(ptr* now,int num)
{
	if (*now==NULL)
	{
		*now=&pol[tot++];
		(*now)->siz=(*now)->con=1;
		(*now)->data=num,(*now)->height=0;
		(*now)->ls=(*now)->rs=NULL; return;
	}
	if ((*now)->data==num)
	{
		(*now)->con++;
		pushup(*now); return;
	}
	if ((*now)->data>num) ins(&(*now)->ls,num);
	else ins(&(*now)->rs,num);
	pushup(*now); balance(now); return;
}

void del(ptr* now,int num)
{
	if (*now==NULL) return;
	if ((*now)->data==num)
	{
		if ((*now)->con>1) (*now)->con--;
		else
		{
			ptr cng=*now;
			if ((*now)->ls==NULL) *now=(*now)->rs;
			else if ((*now)->rs==NULL) *now=(*now)->ls;
			else
			{
				cng=(*now)->rs;
				while (cng->ls) cng=cng->ls;
				(*now)->data=cng->data;
				(*now)->con=cng->con,cng->con=1;
				del(&(*now)->rs,cng->data);
			}
		}
	}
	else
	{
		if ((*now)->data>num) del(&(*now)->ls,num);
		else del(&(*now)->rs,num);
	}
	pushup(*now); balance(now); return;
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