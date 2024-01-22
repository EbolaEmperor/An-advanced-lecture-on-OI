// [JSOI2018] 战争
#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
const double eps=1e-6;
struct Point{
	int x, y;
	Point(int x=0, int y=0): x(x), y(y) {}
    long long len2() const{
        return (long long) x * x + (long long) y * y;
    }
};

Point operator + (const Point &a, const Point &b){
    return Point(a.x + b.x, a.y + b.y);
}

Point operator - (const Point &a, const Point &b){
    return Point(a.x - b.x, a.y - b.y);
}

bool operator < (const Point &a, const Point &b){
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

long long cross(const Point &a, const Point &b){
    return (long long) a.x * b.y - (long long) a.y * b.x;
}

bool cmpPolar(const Point &a, const Point &b){
    const long long c = cross(a, b);
    return c > 0 || c == 0 && a.len2() < b.len2();
}

int ConvexHull(Point a[], const int &n, Point b[]){
    sort(a, a + n);
    int m = -1;
    for(int i = 0; i < n; i++){
        while(m >= 1 && cross(b[m]-b[m-1], a[i]-b[m-1]) <= 0) --m;
        b[++m] = a[i];
    }
    int k = m;
    for(int i = n-2; i >= 0; i--){
        while(m > k && cross(b[m]-b[m-1], a[i]-b[m-1]) <= 0) --m;
        b[++m] = a[i];
    }
    return m;
}

int Minkovski(Point A[], Point ch1[], Point ch2[], const int &n, const int &m){
    for(int i = 0; i < n; i++)
        A[i+1] = ch1[(i+1)%n] - ch1[i];
    for(int i = 0; i < m; i++)
        A[n+i+1] = ch2[(i+1)%m] - ch2[i];
    A[0] = ch1[0] + ch2[0];
    inplace_merge(A+1, A+n+1, A+n+m+1, &cmpPolar);
    for(int i = 1; i <= n+m; i++)
        A[i] = A[i-1] + A[i]; // 把向量恢复成顶点

    // 去除共线顶点
    int tot = 2;
    for(int i = 2; i <= n+m; i++){
        if(cross(A[tot-1]-A[tot-2], A[i]-A[tot-1]) == 0) tot--;
        A[tot++] = A[i];
    }
    return tot - 1;
}

// 判断 p 是否在凸包 ch 内，要求 ch 的第一个顶点是原点
bool inconvex(Point ch[], const int &n, const Point &p){
    assert(ch[0].x == 0 && ch[0].y == 0);
    if(cross(ch[1], p) < 0 || cross(ch[n-1], p) > 0) return false;
    
    int i = lower_bound(ch+1, ch+n, p, cmpPolar) - ch;
    assert(i >= 1 && i < n);
    if(cross(ch[i], p) == 0) return p.len2() <= ch[i].len2();
    else return cross(ch[i] - ch[i-1], p - ch[i-1]) >= 0;
}

int main(){
    int n, m, q;
    static Point p1[N], p2[N], ch1[N], ch2[N], preA[N], A[N];
    scanf("%d%d%d", &n, &m, &q);
    for(int i = 0; i < n; i++)
        scanf("%d%d", &p1[i].x, &p1[i].y);
    for(int i = 0; i < m; i++){
        scanf("%d%d", &p2[i].x, &p2[i].y);
        p2[i].x = -p2[i].x;
        p2[i].y = -p2[i].y;
    }
    int chn = ConvexHull(p1, n, ch1);
    int chm = ConvexHull(p2, m, ch2);
    int sz = Minkovski(A, ch1, ch2, chn, chm);

    Point origin = A[0];
    for(int i = 0; i < sz; i++)
        A[i] = A[i] - origin;

    Point p;
    for(int i = 0; i < q; i++){
        scanf("%d%d", &p.x, &p.y);
        p = p - origin;
        puts(inconvex(A, sz, p) ? "1" : "0");
    }
    return 0;
}