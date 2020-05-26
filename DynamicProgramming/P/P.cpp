#include<bits/stdc++.h>
using namespace std;
const int N=505;
inline int read(){
	int x=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+c-48,c=getchar();
	return x;
}
int dp[N][N],val[N][N],n;
//区间DP
//dp[l][r] 表示[l,r]最少需要多少次暴击
//val[l][r] 表示区间[l,r]被合并后的数值
signed main(){
	n=read();
	memset(dp,0x3f,sizeof dp);
	for(int i=1;i<=n;++i){
		dp[i][i]=1;
		val[i][i]=read();
		//初始化[i,i]
	}
	for(int len=2;len<=n;++len){
		//按照长度枚举，这样可以保证子区间（长度小于原区间的区间）已经被处理
		for(int b=1;(b+len-1)<=n;++b){
			//b是区间开始位置
			int e=b+len-1;
			//e是对应结束位置
			//[b,e]
			for(int k=b;k<e;++k){
				//划分子区间 [b][k] 和 [k+1][e]
				if(dp[b][k]==1&&dp[k+1][e]==1&&val[b][k]==val[k+1][e]){
					//如果可以合并
					dp[b][e]=1;
					val[b][e]=val[b][k]+1;
				}
				else{
					//否则选择最小的
					dp[b][e]=min(dp[b][e],dp[b][k]+dp[k+1][e]);
				}
			}
		}
	}
	printf("%d",dp[1][n]);
	return 0;
}