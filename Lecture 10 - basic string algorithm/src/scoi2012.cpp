#include<bits/stdc++.h>
using namespace std;

const int N = 100010;
unordered_map<int,int> ch[N];
int fail[N],sz=0;
int idx[N], tag[N];
int cnt[N], last[N];
vector<int> miao[50010];
int s[N];
int sum[N];

void insert(int *s,int len,int k)
{
	int p=0;
	for(int i=0;i<len;i++)
	{
		int j=s[i];
		if(!ch[p].count(j)) ch[p][j]=++sz;
		p=ch[p][j];
	}
	tag[p]++;idx[k]=p;
}

void getfail()
{
	queue<int> q;
	q.push(0);
	while(!q.empty())
	{
		int u=q.front();
		for(auto it : ch[u])
		{
			int i=it.first,v=it.second,k=fail[u];
			while(ch[k].count(i)==0&&k) k=fail[k];
			if(u) fail[v]=ch[k].count(i)==0?0:ch[k][i];
			q.push(v);
		}
		q.pop();
	}
}

int serch(vector<int> s,int k)
{
	int p=0,len=s.size(),res=0;
	for(int i=0;i<len;i++)
	{
		int j=s[i];
		while(p&&ch[p].count(j)==0) p=fail[p];
		if(ch[p].count(j)) p=ch[p][j];
        int f=p;
        while(f && last[f]!=k)
            cnt[f]++, last[f]=k, res+=tag[f], f=fail[f];
	}
	return res;
}

int read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}

int main()
{
	int n,m,l;
	n=read();m=read();
	for(int i=1;i<=n;i++)
	{
		l=read();
		for(int j=1;j<=l;j++) miao[i].push_back(read());
		miao[i].push_back(-1);
		l=read();
		for(int j=1;j<=l;j++) miao[i].push_back(read());
	}
	for(int i=1;i<=m;i++)
	{
		l=read();
		for(int j=0;j<l;j++) s[j]=read();
		insert(s,l,i);
	}
	getfail();
	for(int i=1;i<=n;i++) sum[i]=serch(miao[i],i);
	for(int i=1;i<=m;i++) printf("%d\n",cnt[idx[i]]);
	for(int i=1;i<=n;i++) printf("%d ",sum[i]);
	return 0;
}