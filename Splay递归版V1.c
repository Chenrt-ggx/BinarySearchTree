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
	now->siz+=size(now->ls);
	now->siz+=size(now->rs);
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
		*now=(ptr)malloc(sizeof(stu));
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
			free(cng),pushup(root);
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
	scanf("%d",&t);
	while (t--)
	{
		scanf("%d",&x);
		if (x==1) {scanf("%d",&y),ins(&root,y); continue;}
		if (x==2) {scanf("%d",&y),del(root,y); continue;}
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