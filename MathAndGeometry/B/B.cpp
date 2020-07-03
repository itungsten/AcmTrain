#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll miu(ll x)
{
    int k=0;
    for(ll j=2;j*j<=x;++j)
    {
        int now=0;
        if(x%j==0){
            while(x%j==0)++now,x/=j;//质因子j个数为now
            if(now>1)return 0;//如果有两个及以上相同的质因子，不符合第二种情况，返回0
            ++k;//所有的质因子个数
        }
    }
    if(x!=1)++k;//本身为质因子
    return (k&1)?-1:1;//k为奇数还是偶数
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int T;cin>>T;
	ll tmp;
	while(T--){
		cin>>tmp;
		cout<<miu(tmp)<<endl;
	}
	return 0;
}