#include <bits/stdc++.h>
using namespace std;

const int N = 3000010;
int ch[N][62], cnt[N], tot = 0;

int mapping(char c){
    if(c>='a' && c<='z') return c-'a';
    else if(c>='A' && c<='Z') return c-'A'+26;
    else return c-'0'+52;
}

void insert(char s[]){
    int n = strlen(s), u = 0;
    for(int i = 0; i < n; i++){
        int j = mapping(s[i]);
        if(!ch[u][j]) ch[u][j] = ++tot;
        u = ch[u][j];
        cnt[u]++;
    }
}

int query(char s[]){
    int n = strlen(s), u = 0;
    for(int i = 0; i < n; i++){
        int j = mapping(s[i]);
        if(!ch[u][j]) return 0;
        u = ch[u][j];
    }
    return cnt[u];
}

int main(){
    int T, n, m;
    static char s[N];
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++){
            scanf("%s", s);
            insert(s);
        }
        for(int i = 0; i < m; i++){
            scanf("%s", s);
            printf("%d\n", query(s));
        }
        memset(ch, 0, sizeof(int) * (62 * (tot + 1)));
        memset(cnt, 0, sizeof(int) * (tot + 1));
        tot = 0;
    }
    return 0;
}