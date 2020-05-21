#include<bits/stdc++.h>
#define N 1000001 
using namespace std;
int n,t;
//n是节点数，t是临时值
bool vis[N];int cnt;
//最后使用，用来判断有多少个不同的集合

int par[N];
int find(int x){
	if(x==par[x])return x;
	return par[x]=find(par[x]);
}
inline void uni(int x,int y){
	par[find(x)]=find(y);
}
//路径压缩并查集

int main(){

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin>>n;
	for(int i=1;i<=n;++i)par[i]=i;
    //并查集初始化
	for(int i=1;i<=n;++i){
		cin>>t;
		uni(i,t);
	}
    //Union
	for(int i=1;i<=n;++i){
		t=find(i);
		if(!vis[t]){
			vis[t]=1;
			++cnt;
            //一个新的集合
		}
	}
	cout<<cnt;
	return 0;
}
