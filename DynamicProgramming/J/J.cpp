#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int M=25;
int sum[N][M],n,m,dp[(1<<20)],tot[M],farr[(1<<20)];
//sum是前缀和数组
//n是特种兵数目
//m是最大兵种数
//dp是状态压缩后的DP数组啦
//tot是兵种对应特种兵数目
//farr是用于求一个集合内全部兵种对应特种兵的数目之和,这是f的记忆化数组
int f(int sta){
    //用于求一个集合内全部兵种对应特种兵的数目之和
    if(farr[sta]!=-1)return farr[sta];
    for(int i=0;i<m;++i){
        if(sta&(1<<i)){
            return farr[sta]=f(sta-(1<<i))+tot[i+1];
            //巨水的记忆化，不加也是显然可以过的
            break;
        }
    }
}
int dfs(int sta){
    if(dp[sta]!=-1)return dp[sta];
    //记忆化
    int l,r;
    for(int i=0;i<m;++i){
        if(sta&(1<<i)){
            //枚举元素
            l=f(sta-(1<<i))+1,r=f(sta);
            //当前兵种所在区间
            dp[sta]=max(dp[sta],dfs(sta-(1<<i))+sum[r][i+1]-sum[l-1][i+1]);
            //注意sum对于兵种按1开始计数，状态压缩时从0开始表示状态
        }
    }
    return dp[sta];
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    int tmp;
    for(int i=1;i<=n;++i){
        cin>>tmp;
        ++tot[tmp];
        //tmp兵种特种兵数目+1
        for(int j=1;j<=m;++j)sum[i][j]=sum[i-1][j];
        //前缀和继承前面的和
        ++sum[i][tmp];
    }
    memset(dp,-1,sizeof dp);
    memset(farr,-1,sizeof farr);
    dp[0]=0;
    farr[0]=0;
    //init
    cout<<dfs((1<<m)-1);
    return 0;
}
