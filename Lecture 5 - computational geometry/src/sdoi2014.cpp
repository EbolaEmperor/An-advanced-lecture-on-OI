#include <bits/stdc++.h>
using namespace std;

struct Point{
    int x, y;
    Point(int x=0, int y=0): x(x), y(y){}
};
#define Vector Point

inline int decode(int x, long long lastans) {    
    return x ^ (lastans & 0x7fffffff);
}

const int N = 400010;
Point p[N];
vector<int> up[N<<2];
vector<int> down[N<<2];

Vector operator - (const Point &a, const Point &b){
    return Vector(a.x-b.x, a.y-b.y);
}

long long dot(const Point &a, const Point &b){
    return (long long) a.x * b.x + (long long) a.y * b.y;
}

long long cross(const Point &a, const Point &b){
    return (long long) a.x * b.y - (long long) a.y * b.x;
}

bool operator < (const Point &a, const Point &b){
    return a.x<b.x || a.x==b.x && a.y<b.y;
}

bool cmp(int idx, int idy){
    return p[idx] < p[idy];
}

#define top ((int)up[u].size()-1)
#define topd ((int)down[u].size()-1)

void merge(int u){
    static int tmp[N];
    int tot = 0;
    for(int x : up[u<<1]) tmp[++tot] = x;
    int s = tot;
    for(int x : up[u<<1|1]) tmp[++tot] = x;
    inplace_merge(tmp+1, tmp+1+s, tmp+1+tot, cmp);
    for(int i = 1; i <= tot; i++){
        while(top >= 1 && cross(p[up[u][top]] - p[up[u][top-1]],
                                p[tmp[i]] - p[up[u][top-1]]) >= 0) up[u].pop_back();
        up[u].push_back(tmp[i]);
    }

    tot = 0;
    for(int x : down[u<<1]) tmp[++tot] = x;
    s = tot;
    for(int x : down[u<<1|1]) tmp[++tot] = x;
    inplace_merge(tmp+1, tmp+1+s, tmp+1+tot, cmp);
    for(int i = 1; i <= tot; i++){
        while(topd >= 1 && cross(p[down[u][topd]] - p[down[u][topd-1]],
                                p[tmp[i]] - p[down[u][topd-1]]) <= 0) down[u].pop_back();
        down[u].push_back(tmp[i]);
    }
}

void insert(int u, int l, int r, int k){
    if(l == r){
        up[u].push_back(k);
        down[u].push_back(k);
        return;
    }
    int mid = (l + r) / 2;
    if(k <= mid) insert(u<<1, l, mid, k);
    else insert(u<<1|1, mid+1, r, k);
    if(k == r) merge(u);
}

long long query(int u, int l, int r, int ql, int qr, const Point &q){
    if(l >= ql && r <= qr){
        int L = 0, R = top, M1, M2;
        while(R - L > 2){
            M1 = L + (R-L+1) / 3;
            M2 = R - (R-L+1) / 3;
            if( dot(p[up[u][M1]], q) < dot(p[up[u][M2]], q)) L = M1;
            else R = M2;
        }
        long long res = -(1ll<<62);
        for(int i = L; i <= R; i++)
            res = max(res, dot(p[up[u][i]], q));
        
        L = 0, R = topd;
        while(R - L > 2){
            M1 = L + (R-L+1) / 3;
            M2 = R - (R-L+1) / 3;
            if( dot(p[down[u][M1]], q) < dot(p[down[u][M2]], q)) L = M1;
            else R = M2;
        }
        for(int i = L; i <= R; i++)
            res = max(res, dot(p[down[u][i]], q));
        
        return res;
    }
    int mid = (l + r) / 2;
    long long ans = -(1ll<<62);
    if(ql <= mid) ans = max(ans, query(u<<1, l, mid, ql, qr, q));
    if(qr > mid) ans = max(ans, query(u<<1|1, mid+1, r, ql, qr, q));
    return ans;
}

int main(){
    int n, x, y, l, r, pid=0;
    char online[5], op[5];
    scanf("%d%s", &n, online);
    long long lastans = 0;
    for(int i = 1; i <= n; i++){
        scanf("%s%d%d", op, &x, &y);
        if(online[0] != 'E'){
            x = decode(x, lastans);
            y = decode(y, lastans);
        }
        Point q(x, y);
        if(op[0]=='Q'){
            scanf("%d%d", &l, &r);
            if(online[0] != 'E'){
                l = decode(l, lastans);
                r = decode(r, lastans);
            }
            lastans = query(1, 1, n, l, r, q);
            printf("%lld\n", lastans);
        } else {
            p[++pid] = q;
            insert(1, 1, n, pid);
        }
    }
    return 0;
}