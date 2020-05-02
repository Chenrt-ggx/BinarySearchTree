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

int size(ptr p)
{return p?p->siz:0;}
int pushup(ptr now)
{return now?now->con+size(now->ls)+size(now->rs):0;}

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

void ins(ptr* now,int num)
{
	if (*now==NULL)
	{
		*now=(ptr)malloc(sizeof(stu));
		(*now)->siz=(*now)->con=1,(*now)->data=num;
		(*now)->ls=(*now)->rs=NULL; return;
	}
	(*now)->siz++;
	if ((*now)->data==num)
	{
		(*now)->con++;
		return;
	}
	if ((*now)->data>num) ins(&(*now)->ls,num);
	else ins(&(*now)->rs,num);
	return;
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
			if ((*now)->ls==NULL) *now=(*now)->rs,free(cng);
			else if ((*now)->rs==NULL) *now=(*now)->ls,free(cng);
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
		if ((*now)->data<num) del(&(*now)->rs,num);
	}
	if (*now) (*now)->siz=pushup(*now);
	return;
}

void printfst(ptr now)
{
	if (now)
	{
		printf("%d ",now->data);
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
		printf("%d ",now->data);
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
		printf("%d ",now->data);
	}
	else printf("NULL");
	return;
}

int main()
{
	int t,x,y;
	ptr head=NULL;
	scanf("%d",&t);
	while (t--)
	{
		scanf("%d",&x);
		if (x==1) {scanf("%d",&y),ins(&head,y); continue;}//插入y
		if (x==2) {scanf("%d",&y),del(&head,y); continue;}//删除y
		if (x==3) {scanf("%d",&y),printf("%d\n",fnd(head,y)+1); continue;}//查询y的排名
		if (x==4) {scanf("%d",&y),printf("%d\n",kth(head,y)); continue;}//查询排名y的数
		if (x==5) {scanf("%d",&y),printf("%d\n",qan(head,y,-INF)); continue;}//查询y的前驱
		if (x==6) {scanf("%d",&y),printf("%d\n",hou(head,y,INF)); continue;}//查询y的后继
		if (x==7) {printfst(head),puts(""); continue;}//先序遍历输出树
		if (x==8) {printmid(head),puts(""); continue;}//中序遍历输出树
		if (x==9) {printlst(head),puts(""); continue;}//后序遍历输出树
	}
	return 0;
}