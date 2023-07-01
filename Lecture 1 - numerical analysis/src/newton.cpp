#include <bits/stdc++.h>
using namespace std;

double f(double x){
    return pow(x,5) - 2*pow(x,4) + 3*pow(x,3) - 4*pow(x,2) + 5*x - 6;
}

double df(double x){
    return 5*pow(x,4) - 8*pow(x,3) + 9*pow(x,2) - 8*x + 5;
}

int main(){
    double x = 2, x0 = 1.491797988139901;
    cout << setprecision(12) << endl;
    for(int i = 0; i < 8; i++){
        x = x - f(x)/df(x);
        cout << x << " " << fabs(x-x0) << endl;
    }
    cout << endl;

    double l = 0, r = 2, mid;
    for(int i = 0; i < 20; i++){
        mid = (l+r) / 2;
        cout << mid << " " << fabs(mid-x0) << endl;
        if(f(mid) < 0) l = mid;
        else r = mid;
    }
    return 0;
}