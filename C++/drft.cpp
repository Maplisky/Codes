#include<cstdio>
#include<string.h>

using namespace std;

bool acc(double a,double b){
	double temp;
	if(a>b)temp=a-b;
	else temp=b-a;
	if(temp<0.0000001)return true;
	return false;
}

double pie[10005];

int main(){
	int n,f;
	long long t,cnt;
	double temp,mid,l,r;
	while(scanf("%lld",&t)!=-1){
		for(int k=1;k<=t;k++){
			scanf("%d%d",&n,&f);
			f++;
			for(int i=1;i<=n;i++){
				scanf("%lf",&pie[i]);
				pie[i]=pie[i]*pie[i]*3.141592654;
			}
			for(int i=1;i<n;i++){
				for(int j=i+1;j<=n;j++){
					if(pie[i]<pie[j]){
						temp=pie[i];pie[i]=pie[j];pie[j]=temp;
					}
				}
			}
			l=0;r=pie[1];
			while(!acc(l,r)){
				cnt=0;
				mid=(l+r)/2;
				for(int i=1;i<=n;i++){
					cnt+=(int)(pie[i]/mid);
				}
				if(cnt>=f)l=mid;
				else r=mid;
			}
			printf("%.4lf\n",l);
		}
	}
    return 0;
}
