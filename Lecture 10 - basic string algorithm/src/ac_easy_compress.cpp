#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
int ch[N][26], fail[N], idx[N], tot = 0;
bool appear[N];
char s[N];

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
        appear[u] = true;
        int f = fail[u];
        while(f && !appear[f])
            appear[f] = true, f = fail[f];
    }
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

    int ans = 0;
    for(int i = 1; i <= n; i++)
        if(appear[idx[i]]) ans++;
    printf("%d\n", ans);
    return 0;
}