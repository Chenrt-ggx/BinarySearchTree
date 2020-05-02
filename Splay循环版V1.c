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
		*now=(ptr)malloc(sizeof(stu));
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
			free(now),pushup(root);
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
		if (x==1) {scanf("%d",&y),ins(&root,root,y); continue;}
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