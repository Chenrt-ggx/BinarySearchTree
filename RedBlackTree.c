#include <stdio.h>
#include <stdlib.h>

struct tree
{
	struct tree* ls;
	struct tree* rs;
	struct tree* fa;
	int siz,con,data,color;
};

typedef struct tree stu;
typedef struct tree* ptr;

ptr root,nil;

ptr node(int num)
{
	ptr out=(ptr)malloc(sizeof(stu));
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

void trans(ptr u,ptr v)
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
	free(z); return;
}

ptr find(int num)
{
	ptr x=root;
	while (x!=nil)
	{
		if (x->data==num) return x;
		if (x->data<num) x=x->rs;
		else x=x->ls;
	}
	return nil;
}

int fnd(int num)
{
	int ans=0; ptr now=root;
	while (now!=nil) if (now->data>=num) now=now->ls;
	else ans+=now->ls->siz+now->con,now=now->rs;
	return ans;
}

int kth(int num)
{
	ptr now=root;
	while (now!=nil)
	{
		if (now->ls->siz+1<=num && 
		now->ls->siz+now->con>=num) return now->data;
		else if (now->ls->siz+now->con<num)
		num-=now->ls->siz+now->con,now=now->rs;
		else now=now->ls;
	}
	return nil->data;
}

ptr qan(int num)
{
	ins(num); ptr now=find(num),out;
	if (now->ls!=nil) out=max(now->ls);
	else
	{
		while (now->fa->ls==now) now=now->fa;
		out=now->fa;
	}
	del(num); return out;
}

ptr hou(int num)
{
	ins(num); ptr now=find(num),out;
	if (now->rs!=nil) out=min(now->rs);
	else
	{
		while (now->fa->rs==now) now=now->fa;
		out=now->fa;
	}
	del(num); return out;
}

void print(ptr p)
{
	printf("data:%d,con:%d,",p->data,p->con);
	printf("siz:%d,color:%d   ",p->siz,p->color);
	return;
}

void printfst(ptr now)
{
	if (now!=nil)
	{
		print(now);
		if (now->ls!=nil) printfst(now->ls);
		if (now->rs!=nil) printfst(now->rs);
	}
	else printf("NULL");
	return;
}

void printmid(ptr now)
{
	if (now!=nil)
	{
		if (now->ls!=nil) printmid(now->ls);
		print(now);
		if (now->rs!=nil) printmid(now->rs);
	}
	else printf("NULL");
	return;
}

void printlst(ptr now)
{
	if (now!=nil)
	{
		if (now->ls!=nil) printlst(now->ls);
		if (now->rs!=nil) printlst(now->rs);
		print(now);
	}
	else printf("NULL");
	return;
}

int main()
{
	int t,x,y;
	bulidtree();
	scanf("%d",&t);
	while (t--)
	{
		scanf("%d",&x);
		if (x==1) {scanf("%d",&y),ins(y); continue;}
		if (x==2) {scanf("%d",&y),del(y); continue;}
		if (x==3) {scanf("%d",&y),printf("%d\n",fnd(y)+1); continue;}
		if (x==4) {scanf("%d",&y),printf("%d\n",kth(y)); continue;}
		if (x==5) {scanf("%d",&y),printf("%d\n",qan(y)->data); continue;}
		if (x==6) {scanf("%d",&y),printf("%d\n",hou(y)->data); continue;}
		if (x==7) {printfst(root),puts(""); continue;}
		if (x==8) {printmid(root),puts(""); continue;}
		if (x==9) {printlst(root),puts(""); continue;}
	}
	return 0;
}