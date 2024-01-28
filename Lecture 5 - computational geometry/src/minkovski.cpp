#include <bits/stdc++.h>
using namespace std;

struct Point{
    int x, y;
    Point(int x=0, int y=0): x(x),y(y) {}
    long long len2(){
        return (long long) x * x + (long long) y * y;
    }
};
#define Vector Point

Vector operator + (const Point &a, const Point &b){
    return Vector(a.x+b.x, a.y+b.y);
}

Vector operator - (const Point &a, const Point &b){
    return Vector(a.x-b.x, a.y-b.y);
}

long long cross(const Point &a, const Point &b){
    return (long long) a.x * b.y - (long long) a.y * b.x;
}

bool operator < (const Point &a, const Point &b){
    return a.x<b.x || a.x==b.x && a.y<b.y;
}

bool cmp(const Vector &v1, const Vector &v2){
    return cross(v1, v2) > 0;
}

int getconvex(Point p[], int n, Point ch[]){
    sort(p+1, p+1+n);
    int m = 0;
    for(int i = 1; i <= n; i++){
        while(m >= 2 && cross(ch[m]-ch[m-1], p[i]-ch[m-1]) <= 0) m--;
        ch[++m] = p[i];
    }
    int k = m;
    for(int i = n-1; i >= 1; i--){
        while(m > k && cross(ch[m]-ch[m-1], p[i]-ch[m-1]) <= 0) m--;
        ch[++m] = p[i];
    }
    if(m == 1) return 1;
    return m-1;
}

int Minkovski(Point ch1[], int n1, Point ch2[], int n2, Point mink[]){
    for(int i = 1; i < n1; i++)
        mink[i] = ch1[i+1] - ch1[i];
    mink[n1] = ch1[1] - ch1[n1];
    for(int i = 1; i < n2; i++)
        mink[n1+i] = ch2[i+1] - ch2[i];
    mink[n1+n2] = ch2[1] - ch2[n2];
    inplace_merge(mink+1, mink+1+n1, mink+1+n1+n2, cmp);

    int tot = 1;
    for(int i = 2; i <= n1+n2; i++){
        if(cross(mink[i], mink[tot]) == 0)
            mink[tot] = mink[tot] + mink[i];
        else
            mink[++tot] = mink[i];
    }

    mink[0] = ch1[1] + ch2[1];
    for(int i = 1; i <= tot; i++)
        mink[i] = mink[i-1] + mink[i];
    return tot;
}

bool inconvex(Point ch[], int m, Point w){
    assert(ch[1].x == 0 && ch[1].y == 0);
    if(cross(ch[2],w) < 0 || 
       cross(ch[2],w) == 0 && ch[2].len2() < w.len2()) return false;
    if(cross(ch[m],w) > 0 || 
       cross(ch[m],w) == 0 && ch[m].len2() < w.len2()) return false;
    
    int j = lower_bound(ch+2, ch+1+m, w, cmp) - ch;
    assert(j >= 2 && j <= m);
    return cross(ch[j] - ch[j-1], w - ch[j-1]) >= 0;
}

int main(){
    // freopen("jsoi.in", "r", stdin);
    const int N = 100010;
    static Point p1[N], p2[N], ch1[N], ch2[N], mink[N];
    int n1, n2, q;
    scanf("%d%d%d", &n1, &n2, &q);
    for(int i = 1; i <= n1; i++)
        scanf("%d%d", &p1[i].x, &p1[i].y);
    for(int i = 1; i <= n2; i++){
        scanf("%d%d", &p2[i].x, &p2[i].y);
        p2[i].x = -p2[i].x;
        p2[i].y = -p2[i].y;
    }
    int m1 = getconvex(p1, n1, ch1);
    int m2 = getconvex(p2, n2, ch2);
    int m = Minkovski(ch1, m1, ch2, m2, mink);

    Point origin = mink[1];
    for(int i = 1; i <= m; i++)
        mink[i] = mink[i] - origin;

    while(q--){
        Point w;
        scanf("%d%d", &w.x, &w.y);
        w = w - origin;
        puts(inconvex(mink, m, w) ? "1" : "0");
    }
    return 0;
}