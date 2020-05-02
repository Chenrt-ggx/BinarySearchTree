//P6136 4.5s
#include <stdio.h>
#include <stdlib.h>
#define INF 2147483647

struct tree
{
	struct tree* ls;
	struct tree* rs;
	struct tree* fa;
	int siz,con,data,color;
};

typedef struct tree stu;
typedef struct tree* ptr;

int tot;
ptr root,nil;
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

ptr node(int num)
{
	ptr out=&pol[tot++];
	out->siz=out->con=1,out->data=num,out->color=1;
	out->fa=out->ls=out->rs=NULL; return out;
}

void bulidtree()
{
	nil=node(0); nil->color=0;
	nil->siz=nil->con=0;
	root=nil,root->fa=nil; return;
}

void pushup(ptr now)
{
	now->siz=now->con;
	now->siz+=now->ls->siz;
	now->siz+=now->rs->siz;
	return;
}

ptr min(ptr now)
{
	while (now->ls!=nil)
	now=now->ls; return now;
}

ptr max(ptr now)
{
	while (now->rs!=nil)
	now=now->rs; return now;
}

void left(ptr now)
{
	ptr y=now->rs; now->rs=y->ls;
	if (y->ls!=nil) y->ls->fa=now;
	y->fa=now->fa;
	if (now->fa==nil) root=y;
	else if (now==now->fa->rs) now->fa->rs=y;
	else now->fa->ls=y;
	y->ls=now,now->fa=y,y->siz=now->siz;
	pushup(now); return;
}

void right(ptr now)
{
	ptr y=now->ls; now->ls=y->rs;
	if (y->rs!=nil) y->rs->fa=now;
	y->fa=now->fa;
	if (now->fa==nil) root=y;
	else if (now==now->fa->rs) now->fa->rs=y;
	else now->fa->ls=y;
	y->rs=now,now->fa=y,y->siz=now->siz;
	pushup(now); return;
}

void fixins(ptr now)
{
	ptr f,g,u;
	while (now->fa->color)
	{
		f=now->fa,g=f->fa;
		if (f==g->ls)
		{
			u=g->rs;
			if (u->color)
			{
				u->color=f->color=0;
				g->color=1,now=g;
			}
			else
			{
				if (now==f->rs) now=f,left(now);
				now->fa->color=0;
				now->fa->fa->color=1,right(g);
			}
		}
		else
		{
			u=g->ls;
			if (u->color)
			{
				u->color=f->color=0;
				g->color=1,now=g;
			}
			else
			{
				if (now==f->ls) now=f,right(now);
				now->fa->color=0;
				now->fa->fa->color=1,left(g);
			}
		}
	}
	root->color=0; return;
}

void ins(int num)
{
	ptr x=root,y=nil;
	while (x!=nil)
	{
		y=x,y->siz++;
		if (x->data==num) {x->con++; return;}
		if (x->data<num) x=x->rs;
		else x=x->ls;
	}
	x=node(num),x->fa=y;
	x->ls=x->rs=nil;
	if (y==nil) root=x;
	else if (y->data<num) y->rs=x;
	else y->ls=x; fixins(x); return;
}

inline void trans(ptr u,ptr v)
{
	v->fa=u->fa;
	if (u->fa==nil) root=v;
	else if (u==u->fa->rs) u->fa->rs=v;
	else u->fa->ls=v; return;
}

void fixdel(ptr now)
{
	ptr f,c;
	while (now!=root && now->color==0)
	{
		f=now->fa;
		if (now==f->ls)
		{
			c=f->rs;
			if (c->color)
			{
				f->color=1,c->color=0;
				left(f),c=f->rs;
			}
			if (c->ls->color==0 && c->rs->color==0) 
			c->color=1,now=now->fa; else
			{
				if (c->rs->color==0)
				{
					c->color=1,c->ls->color=0;
					right(c),c=f->rs;
				}
				c->color=f->color;
				f->color=c->rs->color=0;
				left(c->fa),now=root;
			}
		}
		else
		{
			c=f->ls;
			if (c->color)
			{
				f->color=1,c->color=0;
				right(f),c=f->ls;
			}
			if (c->ls->color==0 && c->rs->color==0) 
			c->color=1,now=now->fa; else
			{
				if (c->ls->color==0)
				{
					c->color=1,c->rs->color=0;
					left(c),c=f->ls;
				}
				c->color=f->color;
				f->color=c->ls->color=0;
				right(c->fa),now=root;
			}
		}
	}
	now->color=0; return;
}

void del(int num)
{
	int fix; ptr x,y;
	ptr z=root,w=nil,tmp;
	while (z!=nil)
	{
		w=z,w->siz--;
		if (num==z->data) break;
		if (z->data<num) z=z->rs;
		else z=z->ls;
	}
	if (z!=nil)
	{
		if (z->con>1) {z->con--;return;}
		y=z,fix=y->color;
		if (z->ls==nil) x=z->rs,trans(z,z->rs);
		else if (z->rs==nil) x=z->ls,trans(z,z->ls);
		else
		{
			y=min(z->rs);
			fix=y->color,x=y->rs;
			if (y->fa==z) x->fa=y;
			else
			{
				tmp=y;
				while (tmp!=z)
				{
					tmp->siz-=y->con;
					tmp=tmp->fa;
				}
				trans(y,y->rs);
				y->rs=z->rs;
				y->rs->fa=y;
			}
			trans(z,y),y->ls=z->ls,y->ls->fa=y;
			y->color=z->color,pushup(y);
		}
		if (fix==0) fixdel(x);
	}
	else while (w!=nil) w->siz++,w=w->fa;
	return;
}

int fnd(ptr now,int num)
{
	if (now==nil) return 0;
	if (now->data==num) return now->ls->siz;
	if (now->data>num) return fnd(now->ls,num);
	return now->ls->siz+now->con+fnd(now->rs,num);
}

int kth(ptr now,int num)
{
	if (now==nil) return INF;
	if (now->ls->siz>=num) return kth(now->ls,num);
	if (now->ls->siz+now->con>=num) return now->data;
	return kth(now->rs,num-now->ls->siz-now->con);
}

int qan(ptr now,int num,int ans)
{
	if (now->data>=num)
	{
		if (now->ls==nil) return ans;
		return qan(now->ls,num,ans);
	}
	if (now->rs==nil) return now->data;
	return qan(now->rs,num,now->data);
}

int hou(ptr now,int num,int ans)
{
	if (now->data<=num)
	{
		if (now->rs==nil) return ans;
		return hou(now->rs,num,ans);
	}
	if (now->ls==nil) return now->data;
	return hou(now->ls,num,now->data);
}

int main()
{
	bulidtree();
	int n,m,x,y,ans=0,last=0;
	n=read(),m=read();
	while (n--)
	{
		x=read();
		ins(x);
	}
	while (m--)
	{
		x=read(),y=read(),y^=last;
		if (x==1) {ins(y); continue;}
		if (x==2) {del(y); continue;}
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