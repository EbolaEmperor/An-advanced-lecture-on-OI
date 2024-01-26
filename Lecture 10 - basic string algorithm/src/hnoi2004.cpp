#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int ch[N][26], fail[N], g[N], len[N], tot = 0;
char T[2000010];

void insert(char s[]){
    int n = strlen(s+1), u = 0;
    for(int i = 1; i <= n; i++){
        int c = s[i] - 'a';
        if(!ch[u][c]) ch[u][c] = ++tot;
        u = ch[u][c];
    }
    len[u] = n;
}

void getfail(){
    queue<int> q;
    for(int c = 0; c < 26; c++){
        int v = ch[0][c];
        if(v) q.push(v), g[v] = 1<<len[v];
    }
    while(!q.empty()){
        int u = q.front(); q.pop();
        int f = fail[u];
        for(int c = 0; c < 26; c++){
            int& v = ch[u][c];
            if(!v) v = ch[f][c];
            else{
                fail[v] = ch[f][c];
                g[v] = g[fail[v]] | (1<<len[v]);
                q.push(v);
            }
        }
    }
}

int traval(char s[]){
    int n = strlen(s+1), u = 0, status = 1, ans = 0;
    for(int i = 1; i <= n; i++){
        int c = s[i] - 'a';
        u = ch[u][c];
        status <<= 1;
        if(status & g[u])
            status |= 1, ans = i;
    }
    return ans;
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    while(n--){
        scanf("%s", T+1);
        insert(T);
    }
    getfail();

    while(m--){
        scanf("%s", T+1);
        printf("%d\n", traval(T));
    }
    return 0;
}