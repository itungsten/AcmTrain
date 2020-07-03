#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int K=1e5+5;
const int MOD=1e9+7;
int head[N],cnt,n,k,son[N];//链式前向星和节点已经被染色的儿子数目
struct{
	int to,nxt;
}edge[N<<1];
void _addEdge(int u,int v){
	edge[++cnt].to=v;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
}
inline int  Mod(long long a,long long b){
	return ((a%MOD)*(b%MOD))%MOD;
}
inline void addEdge(int u,int v){
	_addEdge(u,v);_addEdge(v,u);//bidirectional
}
int dfs(int dep,int pos,int from){
	int res;
	if(dep==1)res=k;
	else if(dep==2)res=k-1-son[from];
	else res=k-2-son[from];
	//特判前两层
	++son[from];
	//该点被染色
	for(int i=head[pos];i;i=edge[i].nxt){
		int to=edge[i].to;
		if(to==from)continue;//无根树变有根树
		res=Mod(res,dfs(dep+1,to,pos));
	}
	return res;
}
int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>k;
	int a,b;
	for(int i=1;i<n;++i){
		cin>>a>>b;addEdge(a,b);
	}
	cout<<dfs(1,1,0);
	return 0;
}