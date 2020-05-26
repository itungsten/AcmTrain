#include<bits/stdc++.h>
#define int long long
//懒人写法
using namespace std;
const int N=1e5+5;
int n,dp[1<<20],w[21][21],cnt[21];
//w和cnt按照出题人题解命名，即w[i][j]表示有多少对i类特种兵在j类特种兵之前，cnt是一个动态的数组，存放目前出现了多少个某类特种兵
inline int read(){
	int x=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+c-48,c=getchar();
	return x;
}
signed main(){
    n=read();
    int tmp;
    for(int i=1;i<=n;++i){
        tmp=read();
        ++cnt[tmp];
        //出现数目加1
        for(int j=1;j<=20;++j)w[j][tmp]+=cnt[j];
        //由于tmp特种兵的出现，又新增了一些组合
    }
    memset(dp,0x3f,sizeof dp);
    dp[0]=0;
    //初始化
    for(int S=1;S<(1<<20);++S){
    	//按照这种方式，子问题一定比原问题提前求解完毕
    	for(int i=0;i<20;++i){
    		if(S&(1<<i)){
    			//枚举所有可能的子问题
    			int cnt=0;
            	for(int j=0;j<20;++j){
           	    	if((S&(1<<j))&&i!=j)cnt+=w[i+1][j+1];
           	    	//这里是统计逆序对数目
           	    	//注意状态参数下标从0开始，w下标从1开始，需要平移
            	}
    			dp[S]=min(dp[S-(1<<i)]+cnt,dp[S]);
			}
		}
	}
    printf("%lld",dp[(1<<20)-1]);
    //注意是lld
    return 0;
}