#include<bits/stdc++.h>
using namespace std;
const int N=5005;
int n;
//原字符串长度
int dp[N][N];
char a[N],b[N];
//a为正向存储字符串，b为反向字符串
signed main(){
    //题目中虽然说了给出字符串长度n，但实际上根本不需要，手动求出也只需要O(n)的时间，显然这不是算法复杂度的主要构成。最初考虑到给出了n，使用getchar读入字符串，结果遇到各种换行符问题，所以结论就是，使用getchar的时候要搞清楚换行符问题，如果没必要getchar就不要直接用，不容易出错
    scanf("%d",&n);
    scanf("%s",a+1);
    for(int i=1;i<=n;++i){
        b[n+1-i]=a[i];
        //b为逆序字符串
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j)
        {
            //由状态转移方程可知，这样的递推方式，可以保证子问题已经被求解
            if(a[i]==b[j]){
                dp[i][j]=dp[i-1][j-1]+1;
                //如果两端点相同，那么最优解一定不大于共用两端点的情况
            }
            else{
                dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
                //否则只能与前端的字符串匹配
            }
        }
    }
    //求出最长公共子序列，那么答案就是补充上非共同部分。
    printf("%d\n",n-dp[n][n]);
    return 0;
}
