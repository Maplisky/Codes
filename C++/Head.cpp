#include<bits/stdc++.h>
#define ll long long
#define reg register
#define F(i,a,b) for(reg int i=(a);i<=(b);++i)
using namespace std;
bool beginnning;
inline int read();
const int N=1e5+5;
int T,n;
bool ending;
int main(){
    // printf("%.2lfMB\n",1.0*(&beginnning-&ending)/1024/1024);
    T=read();
    while(T--){
        n=read();
    }
    return 0;
}
inline int read(){
    reg int x=0;
    reg bool f=1;
    reg char c=getchar();
    while(!isdigit(c)){
        f=c^45;
        c=getchar();
    }
    while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return f?x:-x;
}