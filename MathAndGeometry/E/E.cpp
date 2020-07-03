#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD=1e9+7;
const int INV2=500000004;
const int INV3=333333336;
//预先计算的逆元
inline int Mod(long long a,long long b){
	return ((a%MOD)*(b%MOD))%MOD;
}
int power(int base,int idx){
	int res=1;
	int i=0;
	while((1LL<<i)<=idx){
		//记得加LL
		if((1LL<<i)&idx)res=Mod(res,base);
		base=Mod(base,base);
		++i;
	}
	return res;
}
//slow power
int m;
bool flag; //用于判断-1项的正负号
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>m;
	int tmp;
	int base=2;
	while(m--){
		cin>>tmp;
		if(!(tmp&1))flag=1; //如果存在偶数
		base=power(base,tmp);	//快速幂 并更新答案和底数
	}
	int lower=Mod(base,INV2);
	int t=lower+(flag?1:-1);
	int upper=Mod( t%MOD ,INV3);
	cout<<upper<<'/'<<lower;
	return 0;
}