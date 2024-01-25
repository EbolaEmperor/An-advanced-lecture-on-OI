#include <bits/stdc++.h>
using namespace std;

const int N = 10000010;
char a[N];
int z[N];

void get_z(char s[], int z[]){
    int n = strlen(s+1);
    int l = 1, r = 1;
    for(int i = 2; i <= n; i++){
        z[i] = (i <= r) ? min(z[i-l+1], r-i+1) : 0;
        // 注意：当 i<=r 且 z[i-l+1]<r-i+1 时，while 循环一定不会执行
        while(i+z[i] <= n && s[1+z[i]] == s[i+z[i]]) z[i]++;
        if(i+z[i]-1 > r) l = i, r = i+z[i]-1;
    }
    z[1] = n;
}

int main(){
    int T;
    scanf("%d", &T);
    for(int t = 1; t <= T; t++){
        scanf("%s", a+1);
        get_z(a, z);
        int n = strlen(a+1);
        for(int i = 1; i <= n; i++){
            if(n % i) continue;
            if(i == n || i + z[i+1] == n){
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}