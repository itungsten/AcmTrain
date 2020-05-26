#include<bits/stdc++.h>
using namespace std;
const int L=1005;
//最大数位数目
int dp[L][11][11][2],dig[L];
//dp[pos][last2][last1][found]这些加上limit都是描述状态的参数
//dig即digit，用于数位分解
const int MOD = 1e9+7;
//模数
inline int Mod(int a, int b){ return (a%MOD+b%MOD)%MOD; }

int dfs(int cnt,int last2,int last1,bool found,bool limit,bool lead) {
    if(cnt==0)return found;
    //1是最低位
	if(!limit&&dp[cnt][last2][last1][found])return dp[cnt][last2][last1][found];
	//!limit是很重要的，避免状态冲突
	//这里手动把前导零的值设置为10，避免了前导零冲突，所以不用!lead
	int res=0,up=limit?dig[cnt]:9;
	//确定该数位上界
	for(int i=0;i<=up;i++)
		res=Mod(res,dfs(cnt-1,(!i&&lead)?10:last1,(!i&&lead)?10:i,found||i==last1||i==last2,limit&&i==up,lead&&!i));
	//枚举可能的情况
	if(!limit)dp[cnt][last2][last1][found]=res;
	//记忆化
	return res;  
}
int solve(const string& k){
	//求0-k的回文串数目
	int cnt=k.size();
	for(int i=0;i<cnt;i++)dig[i+1]=k[cnt-1-i]-'0';
    return dfs(cnt,10,10,0,1,1);
	//倒序，这有一个好处，题解里会说
}
int check(const string& x){
	//单独给 a 写了个check，主要不想手动模拟减法
    char last2=0,last1=0;
    for(int i=0;i<x.size();++i){
        if(x[i]==last1||x[i]==last2)return 1;
        last2=last1;
        last1=x[i];
    }
    return 0;
}
signed main()
{
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	string a,b;
	cin>>a>>b;
	printf("%d",((solve(b)-solve(a)+check(a))%MOD+MOD)%MOD);
	//这里巨坑，虽然b的数目比a多，但是在模的意义下，可能小于a，这就就要使用(x%MOD+MOD)%MOD大法了
}