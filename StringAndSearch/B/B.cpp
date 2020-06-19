#include<bits/stdc++.h>
const int N = 1e3+5;
const int M = 2e6+5;
const int Mod=1e9+7;
using namespace std;
int nxt[N][26];
//状态转移函数
string str;
int dp[2][N];
//滚动数组，N代表状态数目，被滚动的参数是阶段
int suffix[M];
//后缀积
int n,m;
//n the length of pattern
//m the number of text
int Add(int a,int b){
	return (a%Mod+b%Mod)%Mod;
	//害怕
}
int Mul(long a,long b){
	return ( (a%Mod) * (b%Mod) )%Mod;
	//害怕极了
}
inline int char2int(char x){
    return x-'a';
}
void kmp(string &s){
    for(int i = 1, fail = 0; i <= n; ++i) {
        fail = nxt[fail][char2int(s[i-1])];
        //充分利用前面已有的转移函数
        nxt[i - 1][char2int(s[i-1])] = i;
        //把匹配成功的改回正常，对于n，当然依然是全部fail
        for(int j = 0; j < 26; j ++)
            nxt[i][j] = nxt[fail][j];
        //全部视作fail
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>str;
    n=str.size();
  
    cin>>m;
    for(int i=1;i<=m;++i)cin>>suffix[i];
    for(int i=m;i>=2;--i)suffix[i-1]=Mul(suffix[i],suffix[i-1]);
    suffix[m+1]=1; //pay attention plz
	//维护后缀积

    kmp(str);

    dp[0][0]=1;
    //0阶段只有0这一个状态
    int sum=0;
    for(int i=1;i<=m;++i){
        //各个阶段
        cin>>str;
        int len=str.size();
        memset(dp[i&1],0,sizeof dp[i&1]);
        //给我清空啊，kora
        for(int k=0;k<=n;++k){
            //枚举状态
            for(int j=0;j<len;++j){
                //枚举读入的字符串
                int ch=char2int(str[j]);

                int t=nxt[k][ch];
                //转移到的新状态

                dp[i&1][t]=Add(dp[i&1][t],dp[1-(i&1)][k]);
                //滚动数组，不然会MLE
            }
        }
        sum=Add(sum,Mul(dp[i&1][n],suffix[i+1]));
        //后缀积...因为后面无论选什么都可以
    }
    cout<<sum;
    return 0;
}