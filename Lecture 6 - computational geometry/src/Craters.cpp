#include <bits/stdc++.h>
using namespace std;

const int T = 4000;
const double pi = acos(-1);
struct Point
{
	double x, y;
	Point(double x=0,double y=0):x(x),y(y){}
} p[1000010],ch[1000010];
int tot = 0;

Point operator + (Point a,Point b){return Point(a.x+b.x,a.y+b.y);}
Point operator - (Point a,Point b){return Point(a.x-b.x,a.y-b.y);}
double cross(Point a,Point b){return a.x*b.y-a.y*b.x;}
double length(const Point &a){return sqrt(a.x*a.x+a.y*a.y);}

bool operator < (const Point &a,const Point &b){
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

int ConvexHull(Point a[],int n,Point b[]){
    sort(a+1, a+n+1);
    int m = 0;
    for(int i = 1; i <= n; i++){
        while(m > 1 && cross(b[m]-b[m-1], a[i]-b[m-1]) >= 0) --m;
        b[++m] = a[i];
    }
    int k = m;
    for(int i = n-1; i >= 1; i--){
        while(m > k && cross(b[m]-b[m-1], a[i]-b[m-1]) >= 0) --m;
        b[++m] = a[i];
    }
    return m-1;
}

int main(){
    int m;
    cin >> m;
    for(int i = 0; i < m; i++){
        Point center;
        double r;
        cin >> center.x >> center.y >> r;
        r += 10; // 题目要求输入的半径要加10
        for(int j = 0; j < T; j++)
            p[++tot] = center + Point(r*cos(2*pi*j/T), r*sin(2*pi*j/T));
    }
    int chm = ConvexHull(p, tot, ch);
    double ans = 0;
    for(int i = 1; i <= chm; i++)
        ans += length(ch[i+1] - ch[i]);
    printf("%.8lf\n", ans);
    return 0;
}