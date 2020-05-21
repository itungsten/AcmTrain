#include<bits/stdc++.h>
#include<ext/pb_ds/priority_queue.hpp>
//pbds lib
#define int long long
#define param int, less<int>, binomial_heap_tag
using namespace std;
using namespace __gnu_pbds;
const int N=2e5+5;
int n,L;
//n是节点数目，L是活动区间
int ans[N];
//每个节点的活动范围
struct Node{
	int cnt,fa,dep;
    //cnt记录该节点有多少子节点
    //fa用来记录节点父亲，便于合并
    //dep是该节点到根的绝对深度（相对深度转换为绝对深度
	__gnu_pbds::priority_queue<int> q;
    //每个节点一个堆
}node[N];

int head[N];
struct Edge{
	int to,next,w;
}edge[N];
int edgeCnt=0;
inline void addEdge(int f,int t,int w){
	edge[++edgeCnt].to=t;
	edge[edgeCnt].next=head[f];
	edge[edgeCnt].w=w;
	head[f]=edgeCnt;
}
//链式前向星,用于dfs

void dfs(int now,int dep){
	node[now].dep=dep;
	for(int i=head[now];i;i=edge[i].next){
		dfs(edge[i].to,dep+edge[i].w);
		++node[now].cnt;
	}
}
//dfs,处理了每个节点的绝对深度和子节点数目

void pushup(int x){
	ans[x]=node[x].q.size();
    //更新自己的答案
	int father=node[x].fa;
	if(!father){
        //如果到根节点，结束向上合并
		return;
	}

	node[father].q.join(node[x].q);
	int dep=node[father].dep;
	while(node[father].q.top()>(dep+L))node[father].q.pop();
    //将自己与父节点的堆合并，并去除不合法节点
    
	node[father].cnt--;
    //子节点减少一个
	if(node[father].cnt==0)pushup(father);
    //当自身成为叶节点时，向上合并
}
void build(){
	dfs(1,0);
	for(int i=1;i<=n;++i)node[i].q.push(node[i].dep);
    //节点一定可以到达自己
}

inline int read(){
	int x=0;bool f=1;char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=0;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-48;
		ch=getchar();
	}
	return f?x:-x;
}

signed main(){
	n=read(),L=read();

	int p,d;
	for(int i=2;i<=n;++i){
		p=read(),d=read();
		node[i].fa=p;
		addEdge(p,i,d);
	}

	build();

	for(int i=1;i<=n;++i){
		if(!head[i]){
            //如题解所说，从叶子节点往上做
			pushup(i);
		}
	}

	for(int i=1;i<=n;++i)printf("%d\n",ans[i]);
	return 0; 
}
