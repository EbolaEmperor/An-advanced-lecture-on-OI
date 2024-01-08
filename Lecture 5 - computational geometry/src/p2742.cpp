#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const double eps=1e-6;
struct Point
{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y){}
} p[100010],ch[100010];

Point operator - (Point a,Point b){return Point(a.x-b.x,a.y-b.y);}
bool operator < (const Point &a,const Point &b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}
double cross(Point a,Point b){return a.x*b.y-a.y*b.x;}
void read(Point &x){scanf("%lf%lf",&x.x,&x.y);}
double length(const Point &a){return sqrt(a.x*a.x+a.y*a.y);}

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

int main()
{
	int n;
	double ans=0.0;
	cin>>n;
	for(int i=1;i<=n;i++) read(p[i]);
	int m=ConvexHull(p,n,ch);
	for(int i=1;i<=m;i++) 
        ans += length(ch[i+1] - ch[i]);
	printf("%.2lf\n",ans);
	//system("pause");
	return 0;
}
