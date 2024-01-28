#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int xi[N], yi[N], wi[N], n;
int begint;
double ansx, ansy, ansf = 1e18;

double H(double x, double y){
    double ans = 0;
    for(int i = 1; i <= n; i++)
        ans += wi[i] * sqrt((xi[i]-x)*(xi[i]-x) + (yi[i]-y)*(yi[i]-y));
    if(ans < ansf){
        ansx = x;
        ansy = y;
        ansf = ans;
    }
    return ans;
}

double RAND(){
    return (double) rand() / RAND_MAX;
}

bool accept(double dta, double tem){
    return dta < 0 || RAND() < exp(-dta/tem);
}

void anneal(double init, double delta, double end){
    double px = 0, py = 0, tem = init, cur = H(px,py);
    while(tem > end){
        double nextpx = px + (RAND() * 2 - 1) * tem;
        double nextpy = py + (RAND() * 2 - 1) * tem;
        double nxt = H(nextpx, nextpy);
        if(accept(nxt-cur, tem)){
            px = nextpx;
            py = nextpy;
            cur = nxt;
        }
        tem *= delta;
    }
}

bool TLE(){
    return (double) (clock() - begint) / CLOCKS_PER_SEC > 0.85;
}

int main(){
    srand(time(0));
    begint = clock();
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d%d%d", xi+i, yi+i, wi+i);
    while(!TLE()) anneal(10000, 0.9999, 1e-4);
    printf("%.3lf %.3lf\n", ansx, ansy);
    return 0;
}