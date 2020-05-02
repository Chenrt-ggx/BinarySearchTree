//P6136 10.5s
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

int a[100010];
stu pol[1600000];
int tmp; ptr* doit;

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

int total(ptr now)
{return now?now->tsiz:0;}

int cmp(const void *a,const void *b)
{return *(int*)a-*(int*)b;}

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

int main()
{
	ptr root=NULL;
	int n,m,x,y,ans=0,last=0;
	n=read(),m=read();
	for (int i=0;i<n;i++) a[i]=read();
	qsort(a,n,4,cmp),tmp=0,x=1;
	for (int i=0;i<n;i++)
	{
		if (a[i]!=a[i+1])
		{
			pol[tmp].data=a[i];
			pol[tmp].con=x,x=1,tmp++;
		}
		else x++;
	}
	root=bulid(0,tmp);
	while (m--)
	{
		x=read(),y=read(),y^=last;
		if (x==1)
		{
			doit=NULL,ins(&root,y);
			if (doit) rebulid(doit);
			continue;
		}
		if (x==2)
		{
			doit=NULL,del(&root,y);
			if (doit) rebulid(doit);
			continue;
		}
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
			last=kth(root,fnd(root,y));
			ans^=last; continue;
		}
		if (x==6)
		{
			last=kth(root,fnd(root,y+1)+1);
			ans^=last; continue;
		}
	}
	printf("%d\n",ans);
	return 0;
}