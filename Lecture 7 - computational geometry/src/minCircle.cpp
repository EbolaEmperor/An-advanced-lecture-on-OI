#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-13;
struct Point{
	double x, y;
	Point(double x=0, double y=0): x(x), y(y) {}
} Q[100010];
int n;

inline double sqr(const double &x){return x*x;}
Point operator - (Point a,Point b){return Point(a.x-b.x,a.y-b.y);}

int dcmp(double x){
    if(fabs(x) <= eps) return 0;
    else if(x<0) return -1;
    else return 1;
}

double Length(const Point &a){return sqrt(a.x*a.x+a.y*a.y);}

void geto(const Point &a, const Point &b, const Point &c, Point &ans, double &r) {
  double a1, a2, b1, b2, c1, c2;
  a1 = 2 * (b.x - a.x), b1 = 2 * (b.y - a.y),
  c1 = sqr(b.x) - sqr(a.x) + sqr(b.y) - sqr(a.y);
  a2 = 2 * (c.x - a.x), b2 = 2 * (c.y - a.y),
  c2 = sqr(c.x) - sqr(a.x) + sqr(c.y) - sqr(a.y);
  if (dcmp(a1) == 0) {
    ans.y = c1 / b1;
    ans.x = (c2 - ans.y * b2) / a2;
  } else if (dcmp(b1) == 0) {
    ans.x = c1 / a1;
    ans.y = (c2 - ans.x * a2) / b2;
  } else {
    ans.x = (c2 * b1 - c1 * b2) / (a2 * b1 - a1 * b2);
    ans.y = (c2 * a1 - c1 * a2) / (b2 * a1 - b1 * a2);
  }
  r = Length(a-ans);
}

bool in_circle(const Point &A, const Point &O, const double &r){
    return dcmp(Length(A-O) - r) <= 0;
}

// 计算 MC(Q[i],Q[j];  Q[1],...,Q[j-1])
void getMC_fix2(int i, int j, Point &ans, double &r){
    ans.x = 0.5 * (Q[i].x + Q[j].x);
    ans.y = 0.5 * (Q[i].y + Q[j].y);
    r = Length(Q[i] - Q[j]) / 2;

    for(int k = 1; k < j; k++){
        if(in_circle(Q[k], ans, r)) continue;
        geto(Q[i], Q[j], Q[k], ans, r);
    }
}

// 计算 MC(Q[i];  Q[1],...,Q[i-1])
void getMC_fix1(int i, Point &ans, double &r){
    ans.x = 0.5 * (Q[i].x + Q[1].x);
    ans.y = 0.5 * (Q[i].y + Q[1].y);
    r = Length(Q[i] - Q[1]) / 2;

    for(int j = 2; j < i; j++){
        if(in_circle(Q[j], ans, r)) continue;
        getMC_fix2(i, j, ans, r);
    }
}

// 计算 MC(空;  Q[1],...,Q[n])
void getMC_fix0(Point &ans, double &r){
    ans = Q[1];
    r = 0;
    for(int i = 2; i <= n; i++){
        if(in_circle(Q[i], ans, r)) continue;
        getMC_fix1(i, ans, r);
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%lf%lf", &Q[i].x, &Q[i].y);
    random_shuffle(Q+1, Q+1+n);
    Point ans;
    double r;
    getMC_fix0(ans, r);
    printf("%.10lf\n%.10lf %.10lf\n", r, ans.x, ans.y);
    return 0;
}