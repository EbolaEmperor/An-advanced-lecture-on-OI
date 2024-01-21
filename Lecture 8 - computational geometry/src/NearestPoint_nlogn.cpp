#include <bits/stdc++.h>
using namespace std;

const int MAXN = 400010;

struct Point{int x, y;};

long long dist2(const Point &p1, const Point &p2){
    return (long long) (p1.x-p2.x) * (p1.x-p2.x) + (long long) (p1.y-p2.y) * (p1.y-p2.y) ;
}

bool cmpx(const Point &p1, const Point &p2){
    return p1.x < p2.x;
}

bool cmpy(const Point &p1, const Point &p2){
    return p1.y < p2.y;
}

void merge(Point p[], const int &l, const int &r){
    static Point tmp[MAXN];
    int mid = (l + r) / 2;
    int p1 = l, p2 = mid, pc = l;
    while(p1 < mid || p2 < r){
        if(p2 == r) tmp[pc++] = p[p1++];
        else if(p1 == mid) tmp[pc++] = p[p2++];
        else if(p[p1].y < p[p2].y) tmp[pc++] = p[p1++];
        else tmp[pc++] = p[p2++];
    }
    memcpy(p + l, tmp + l, sizeof(Point) * (r - l));
}

long long nearest_dist(Point p[], const int &l, const int &r){
    if(r - l <= 5){
        long long ans = 1ll << 62;
        for(int i = l; i < r; i++)
            for(int j = l; j < i; j++){
                ans = min(ans, dist2(p[i], p[j]));
            }
        sort(p + l, p + r, cmpy);
        return ans;
    }

    int       mid  = (l + r) / 2;
    // 必须在递归进入子过程之前求 midx，否则顺序乱了，求出来的不再是中间的线！
    double    midx = (p[mid-1].x + p[mid].x) / 2.;
    long long ans  = min(nearest_dist(p, l, mid), nearest_dist(p, mid, r));
    double    h    = sqrt(ans);

    merge(p, l, r);
    // 也可以使用库函数：inplace_merge(p + l, p + mid, p + r, &cmpy);

    static Point B[MAXN];
    int pc = l;
    for(int i = l; i < r ; i++)
        if(p[i].x >= midx - h && p[i].x <= midx + h)
            B[pc++] = p[i];
    for(int i = l; i < pc; i++)
        for(int k = i - 1; k >= l && B[k].y >= B[i].y - h; k--)
            ans = min(ans, dist2(B[i], B[k]));

    return ans;
}

int main(){
    int n;
    static Point p[MAXN];

    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d%d", &p[i].x, &p[i].y);
    sort(p, p + n, cmpx);

    long long ans = nearest_dist(p, 0, n);
    cout << ans << endl;
    return 0;
}