#include<bits/stdc++.h>
using namespace std;
const double eps=1e-9;

int n,f;

double pie[10005];

bool check(double mid){
    int cnt=0;
    for(int i=1;i<=n;++i){
        cnt+=(int)(pie[i]/mid);
    }
    return cnt>=f;
}

int main(){
    int T;
    scanf("%d",&T);
	while(T--){
        scanf("%d%d",&n,&f);
        f++;
        double l=0,r=0,mid;

        for(int i=1;i<=n;i++){
            scanf("%lf",&pie[i]);
            pie[i]=pie[i]*pie[i]*3.141592653;
            r=max(r,pie[i]);
        }

        double ans;

        while(l+eps<=r){
            mid=(l+r)/2;
            check(mid)?l=mid,ans=mid:r=mid;
        }
        printf("%.4lf\n",ans+eps);
	}
    return 0;
}
