#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
vector<int> g[N];
int ch[N][26], fail[N], idx[N], tot = 0;
long long cnt[N];
char s[N*10];

void insert(char s[], int id){
    int n = strlen(s+1), u = 0;
    for(int i = 1; i <= n; i++){
        int c = s[i] - 'a';
        if(!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c];
    }
    idx[id] = u;
}

void getfail(){
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

void traval(char s[]){
    int n = strlen(s+1), u = 0;
    for(int i = 1; i <= n; i++){
        int c = s[i] - 'a';
        u = ch[u][c];
        cnt[u]++;
    }
}

void dfs(int u){
    for(int v : g[u])
        dfs(v), cnt[u] += cnt[v];
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%s", s+1);
        insert(s, i);
    }
    getfail();
    scanf("%s", s+1);
    traval(s);

    for(int i = 1; i <= tot; i++)
        g[fail[i]].push_back(i);
    dfs(0);

    for(int i = 1; i <= n; i++)
        printf("%lld\n", cnt[idx[i]]);
    return 0;
}