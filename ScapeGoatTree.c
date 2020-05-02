#include <stdio.h>
#include <stdlib.h>
#define INF 2147483647

const double beta=0.70;
const double alpha=0.80;

struct tree
{
	struct tree* ls;
	struct tree* rs;
	int siz,con,tsiz,data;
};

typedef struct tree stu;
typedef struct tree* ptr;

stu pol[100100];
int tmp; ptr* doit;

int size(ptr now)
{
	if (now==NULL) return 0;
	return now->siz;
}

int total(ptr now)
{
	if (now==NULL) return 0;
	return now->tsiz;
}

void pushup(ptr now)
{
	if (now==NULL) return;
	now->tsiz=1;
	now->siz=now->con;
	now->siz+=size(now->ls);
	now->siz+=size(now->rs);
	now->tsiz+=total(now->ls);
	now->tsiz+=total(now->rs);
	return;
}

int isbad(ptr now)
{
	if (now==NULL) return 0;
	if (now->ls && 1.0*total(now->ls)>total(now)*alpha+5) return 1;
	if (now->rs && 1.0*total(now->rs)>total(now)*alpha+5) return 1;
	if (total(now)*beta>1.0*size(now)) return 1; return 0;
}

void dfs(ptr now)
{
	if (now==NULL) return;
	dfs(now->ls);
	if (now->con)
	pol[tmp++]=*now;
	dfs(now->rs);
	free(now); return;
}

ptr bulid(int l,int r)
{
	if (l>=r) return NULL;
	int mid=(l+r)>>1;
	ptr now=(ptr)malloc(sizeof(stu));
	*now=pol[mid];
	now->ls=bulid(l,mid);
	now->rs=bulid(mid+1,r);
	pushup(now); return now;
}

void rebulid(ptr *now)
{
	tmp=0,dfs(*now);
	*now=bulid(0,tmp);
	return;
}

void ins(ptr* now,int num)
{
	if (*now==NULL)
	{
		*now=(ptr)malloc(sizeof(stu));
		(*now)->data=num,(*now)->ls=(*now)->rs=NULL; 
		(*now)->tsiz=(*now)->siz=(*now)->con=1; return;
	}
	if ((*now)->data==num)
	{
		(*now)->con++;
		pushup(*now); return;
	}
	if ((*now)->data>num) ins(&(*now)->ls,num);
	else ins(&(*now)->rs,num); pushup(*now);
	if (isbad(*now)) doit=now; return;
}

void del(ptr* now,int num)
{
	if (*now==NULL) return;
	if ((*now)->data==num)
	{
		if ((*now)->con)
		(*now)->con--;
	}
	else
	{
		if ((*now)->data>num) del(&(*now)->ls,num);
		else del(&(*now)->rs,num);
	}
	pushup(*now); if (isbad(*now))
	doit=now; return;
}

int fnd(ptr now,int num)
{
	if (now==NULL) return 0;
	if (now->con && now->data==num) return size(now->ls);
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

void print(ptr p)
{
	printf("data:%d,con:%d,",p->data,p->con);
	printf("siz:%d,tsiz:%d   ",p->siz,p->tsiz);
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
	ptr root=NULL;
	scanf("%d",&t);
	while (t--)
	{
		scanf("%d",&x);
		if (x==1) {scanf("%d",&y),doit=NULL,ins(&root,y); if (doit) rebulid(doit); continue;}
		if (x==2) {scanf("%d",&y),doit=NULL,del(&root,y); if (doit) rebulid(doit); continue;}
		if (x==3) {scanf("%d",&y),printf("%d\n",fnd(root,y)+1); continue;}
		if (x==4) {scanf("%d",&y),printf("%d\n",kth(root,y)); continue;}
		if (x==5) {scanf("%d",&y),printf("%d\n",kth(root,fnd(root,y))); continue;}
		if (x==6) {scanf("%d",&y),printf("%d\n",kth(root,fnd(root,y+1)+1)); continue;}
		if (x==7) {printfst(root),puts(""); continue;}
		if (x==8) {printmid(root),puts(""); continue;}
		if (x==9) {printlst(root),puts(""); continue;}
	}
	return 0;
}