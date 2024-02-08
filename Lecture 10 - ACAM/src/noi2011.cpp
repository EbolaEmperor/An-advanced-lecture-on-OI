#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;

const int N = 100010;
struct Type_XY{int x, y, id;} qry[N];
int ch[N][26], sz=0;
int father[N], val[N], fail[N];
int word[N], cnt[N], ans[N];
char s[N];
int bit[N];
vector<int> g[N];
int h[N], sum=0;
int in[N], out[N], dfn=0;

void add(int p, int k){
	for(; p <= dfn; p+=lowbit(p))
		bit[p] += k;
}

int query(int p){
	int res = 0;
	for(; p > 0; p -= lowbit(p))
		res += bit[p];
	return res;
}

bool operator < (const Type_XY &t1, const Type_XY &t2) {return t1.y < t2.y;}

void insert(){
	scanf("%s",s);
	int n = strlen(s), u = 0, cnt = 0;
	for(int i = 0; i < n; i++){
		if(s[i] >= 'a' && s[i] <= 'z'){
			int idx = s[i] - 'a';
			if(ch[u][idx] == 0)
				ch[u][idx] = ++sz, father[sz] = u;
			u = ch[u][idx];
		}
		if(s[i] == 'B') u = father[u];
		if(s[i] == 'P') word[++cnt] = u, val[u] = cnt;
	}
}

void GetFail(){
    queue<int> q;
    for(int c = 0; c < 26; c++)
        if(ch[0][c]) q.push(ch[0][c]);
    while(!q.empty()){
        int u = q.front(); q.pop();
        int f = fail[u];
        for(int c = 0; c < 26; c++){
            int& v = ch[u][c];
            if(!v) v = ch[f][c];
            else fail[v] = ch[f][c], q.push(v);
        }
    }
}

void dfs(int u){
	in[u] = ++dfn;
	for(int v : g[u]) dfs(v);
	out[u] = dfn;
}

void solve(){
	int p = 0, len = strlen(s), k = 1, cnt = 0;
	for(int i = 0; i < len; i++){
		if(s[i] >= 'a' && s[i] <= 'z')
			p = ch[p][s[i]-'a'], add(in[p], 1);
		if(s[i] == 'B')
			add(in[p], -1), p = father[p];
		if(s[i] == 'P'){
			cnt++;
			for(int j = k; qry[j].y == cnt; j++, k++)
				ans[qry[j].id] = query(out[word[qry[j].x]]) - query(in[word[qry[j].x]] - 1);
		}
	}
}

int main(){
	insert();
	GetFail();
	for(int i=1;i<=sz;i++)
		g[fail[i]].push_back(i);
	dfs(0);
	int T;
	cin >> T;
	for(int tt = 1; tt <= T; tt++){
		scanf("%d%d", &qry[tt].x, &qry[tt].y);
		qry[tt].id = tt;
	}
	sort(qry + 1, qry + 1 + T);
	solve();
	for(int i = 1; i <= T; i++) printf("%d\n", ans[i]);
	return 0;
}