//P6136 8.5s
#include <stdio.h>
#include <stdlib.h>
#define INF 2147483647

struct tree
{
	struct tree* ls;
	struct tree* rs;
	struct tree* fa;
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

void buildleft(ptr son,ptr father)
{
	if (son) son->fa=father;
	if (father) father->ls=son;
	else root=son; return;
}

void buildright(ptr son,ptr father)
{
	if (son) son->fa=father;
	if (father) father->rs=son;
	else root=son; return;
}

void rotate(ptr now)
{
	ptr f=now->fa,g=f->fa;
	if (g==NULL || g->ls==f) buildleft(now,g);
	else buildright(now,g);
	if (f==NULL || f->ls==now)
	buildleft(now->rs,f),buildright(f,now);
	else buildright(now->ls,f),buildleft(f,now);
	pushup(f); return;
}

void splay(ptr src,ptr dst)
{
	ptr f,g;
	while (src->fa!=dst)
	{
		f=src->fa,g=f->fa;
		if (src->fa->fa!=dst)
		{
			if (src==f->ls)
			{if (f==g->ls) rotate(f); else rotate(src);}
			else
			{if (f==g->ls) rotate(src); else rotate(f);}
		}
		rotate(src);
	}
	pushup(src); return;
}

void ins(ptr* now,ptr f,int num)
{
	if (*now==NULL)
	{
		*now=&pol[tot++];
		(*now)->siz=(*now)->con=1,(*now)->data=num;
		(*now)->fa=f,(*now)->ls=(*now)->rs=NULL;
		splay(*now,NULL); return;
	}
	if ((*now)->data==num)
	{
		(*now)->con++; pushup(*now);
		splay(*now,NULL); return;
	}
	if ((*now)->data>num) ins(&(*now)->ls,*now,num);
	else ins(&(*now)->rs,*now,num);
	pushup(*now); return;
}

void del(ptr now,int num)
{
	if (now==NULL) return;
	if (now->data==num)
	{
		splay(now,NULL);
		if (root->con>1) root->con--;
		else if (root->rs)
		{
			ptr cng=root->rs;
			while (cng->ls) cng=cng->ls;
			splay(cng,now);
			buildleft(now->ls,cng);
			root=cng,cng->fa=NULL;
			pushup(root);
		}
		else root=now->ls,(root)&&(root->fa=NULL,0);
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
		splay(now,NULL); return ans;
	}
	if (now->data>num) return fnd(now->ls,num);
	return size(now->ls)+now->con+fnd(now->rs,num);
}

int kth(ptr now,int num)
{
	if (now==NULL) return INF;
	if (size(now->ls)>=num) return kth(now->ls,num);
	if (size(now->ls)+now->con>=num)
	{splay(now,NULL); return root->data;}
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
		splay(now,NULL);
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
		splay(now,NULL);
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
		ins(&root,root,x);
	}
	while (m--)
	{
		x=read(),y=read(),y^=last;
		if (x==1) {ins(&root,root,y); continue;}
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