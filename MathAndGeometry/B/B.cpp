#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll miu(ll x)
{
    //按照定义求
    int k=0;//质因数个数
    for(ll j=2;j*j<=x;++j)
    {
        //表面上看这里不一定是质数，有问题
        //但是如果其不是质数，其因子已经在x中被消去了，所以该合数会被忽略掉
        if(x%j==0){
            int now=0;
            while(x%j==0)++now,x/=j;//质因子j个数为now
            if(now>1)return 0;//如果有两个及以上相同的质因子，返回0
            ++k;
        }
    }
    if(x!=1)++k;//现在的x是一个质数
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