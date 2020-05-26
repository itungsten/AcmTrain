#include<bits/stdc++.h>
using namespace std;
const int N=1005;
const int M=10;
const int C=1005;
int n,m,c,f[C];
//n是普通物品个数
//m是神奇物品个数
//c是背包总体积
inline int read(){
    int x=0,f=1;char c=getchar();
    while(!isdigit(c))c=='-'&&(f=-1),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+c-48,c=getchar();
    return x*f;
}
signed main(){
    n=read(),m=read(),c=read();
    while(n--){
        int vi=read(),wi=read(),di=read(),i;// vi：volume   wi：wealth   di是最多个数

        //二进制拆分，把多重背包拆分为多个01背包
        for(i=0;(1<<(i+1))-1<=di;++i){
            for(int j=c;j>=(vi<<i);--j){
                f[j]=max(f[j],f[j-(vi<<i)]+(wi<<i));
                //要或者不要
            }
        }
        int resi=di-(1<<i)+1;
        //值得注意的是，这里的应该是i，而不是i+1，应为在最后一次成功拆分后i自动加上了1
        if(resi){
            vi*=resi,wi*=resi;
            for(int j=c;j>=vi;--j)f[j]=max(f[j],f[j-vi]+wi);
            //处理余留下来的数值，都是套路
        }
    }
    while(m--){
        //神奇物品
        //这里就要利用分组背包和泛化物品的概念
        int x=read(),y=read(),z=read();
        for(int i=c;i>=0;--i){
            //注意这里一定要倒序，否则滚动数组就会出错
            for(int j=0;j<=c;++j){
                //注意这里j一定要包含0，因为这题反人类地让z可以不为0
                int wi=x*j*j+y*j+z;
                if(i>=j)f[i]=max(f[i],f[i-j]+wi);
                else break;
            }
        }
    }
    printf("%d",f[c]);
    return 0;
}
