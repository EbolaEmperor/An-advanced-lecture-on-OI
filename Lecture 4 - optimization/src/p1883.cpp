#include <bits/stdc++.h>
using namespace std;

char buf[1<<17],*p1=buf,*p2=buf;
inline int gc(){
    return (p1==p2)&&(p2=(p1=buf)+fread(buf,1,1<<17,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
    int x=0,f=1;
    char ac=gc();
    while(ac<'0'||ac>'9'){
        if(ac=='-') f=0;
        ac=gc();
    }
    while(ac>='0'&&ac<='9'){
        x=(x<<3)+(x<<1)+(ac^48);
        ac=gc();
    }
    return f?x:-x;;
}

const double c = (sqrt(5)-1)/2;
const int N = 10000;
int a[N], b[N], cc[N];
int n;

double f(double x){
    double ans = -1e200;
    for(int i = 0; i < n; i++)
        ans = max(ans, a[i]*x*x + b[i]*x + cc[i]);
    return ans;
}

double search(double l, double r){
    double f1 = f(r - c * (r-l));
    double f2 = f(l + c * (r-l));
    while(r-l > 2e-8){
        if(f1 > f2){
            l = r - c * (r-l);
            f1 = f2;
            f2 = f(l + c * (r-l));
        } else {
            r = l + c * (r-l);
            f2 = f1;
            f1 = f(r - c * (r-l));
        }
    }
    return (l+r)/2;
}

int main(){
    int T=read();
    while(T--){
        n = read();
        for(int i = 0; i < n; i++)
            a[i]=read(), b[i]=read(), cc[i]=read();
        printf("%.4lf\n", f(search(0, 1000)));
    }
    return 0;
}