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

long long area(const Point &A, const Point &B, const Point &P){
    return cross(B-A, P-A);
}

int main(){
    const int N = 50010;
    static Point p[N], ch[N];
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d%d", &p[i].x, &p[i].y);
    int m = getconvex(p, n, ch);

    int j = 2, nxj = j % m + 1;
    long long ans = 0;
    for(int i = 1; i <= m; i++){
        int nxi = i % m + 1;
        // while(area(ch[i],ch[nxi],ch[nxj]) > area(ch[i],ch[nxi],ch[j])){
        while(cross(ch[nxi]-ch[i], ch[nxj]-ch[j]) > 0){
            j = nxj;
            nxj = j % m + 1;
        }
        ans = max(ans, (ch[i]-ch[j]).len2());
        ans = max(ans, (ch[nxi]-ch[j]).len2());
    }
    cout << ans << endl;
    return 0;
}