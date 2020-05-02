//P6136 9.3s
#include <stdio.h>
#include <stdlib.h>
#define INF 2147483647

struct tree
{
	struct tree* ls;
	struct tree* rs;
	int siz,con,data;
};

typedef struct tree stu;
typedef struct tree* ptr;

int tot;
ptr root;
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

void splay(ptr src,ptr *dst)
{
	if (src==*dst) return;
	else if (src==(*dst)->ls) right(dst);
	else if (src==(*dst)->rs) left(dst);
	else
	{
		if (src->data<(*dst)->data)
		{
			if (src->data<(*dst)->ls->data)
			splay(src,&(*dst)->ls->ls),right(dst),right(dst);
			else splay(src,&(*dst)->ls->rs),
			left(&(*dst)->ls),right(dst);
		}
		else
		{
			if (src->data>(*dst)->rs->data)
			splay(src,&(*dst)->rs->rs),left(dst),left(dst);
			else splay(src,&(*dst)->rs->ls),
			right(&(*dst)->rs),left(dst);
		}
	}
	return;
}

void ins(ptr* now,int num)
{
	if (*now==NULL)
	{
		*now=&pol[tot++];
		(*now)->siz=(*now)->con=1,(*now)->data=num;
		(*now)->ls=(*now)->rs=NULL;
		splay(*now,&root); return;
	}
	if ((*now)->data==num)
	{
		(*now)->con++; pushup(*now);
		splay(*now,&root); return;
	}
	if ((*now)->data>num) ins(&(*now)->ls,num);
	else ins(&(*now)->rs,num);
	pushup(*now); return;
}

void del(ptr now,int num)
{
	if (now==NULL) return;
	if (now->data==num)
	{
		splay(now,&root);
		if (root->con>1) root->con--;
		else if (root->rs)
		{
			ptr cng=root->rs;
			while (cng->ls) cng=cng->ls;
			splay(cng,&root->rs);
			root->rs->ls=root->ls;
			cng=root,root=root->rs;
			pushup(root);
		}
		else root=root->ls;
	}
	else if (now->data>num) del(now->ls,num);
	else del(now->rs,num); return;
}

int fnd(ptr now,int num)
{
	if (now==NULL) return 0;
	if (now->data==num)
	{
		int ans=size(now->ls);
		splay(now,&root); return ans;
	}
	if (now->data>num) return fnd(now->ls,num);
	return size(now->ls)+now->con+fnd(now->rs,num);
}

int kth(ptr now,int num)
{
	if (now==NULL) return INF;
	if (size(now->ls)>=num) return kth(now->ls,num);
	if (size(now->ls)+now->con>=num)
	{splay(now,&root); return root->data;}
	return kth(now->rs,num-size(now->ls)-now->con);
}

int qan(ptr now,int num,int ans)
{
	if (now->data>=num)
	{
		if (now->ls==NULL) return ans;
		return qan(now->ls,num,ans);
	}
	if (now->rs==NULL)
	{
		splay(now,&root);
		return root->data;
	}
	return qan(now->rs,num,now->data);
}

int hou(ptr now,int num,int ans)
{
	if (now->data<=num)
	{
		if (now->rs==NULL) return ans;
		return hou(now->rs,num,ans);
	}
	if (now->ls==NULL)
	{
		splay(now,&root);
		return root->data;
	}
	return hou(now->ls,num,now->data);
}

int main()
{
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
		if (x==2) {del(root,y); continue;}
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