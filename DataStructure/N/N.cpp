#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int M=2*N;
//无向边转换为有向边
int mod=170001,n,m;
inline int Mod(int x){
    //防翻车取模法
	return (x%mod+mod)%mod;
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
struct Edge{
	int to,next;
}edge[M];
int tot=0,head[N];
void addEdge(int u,int v){
	edge[tot].to=v;
	edge[tot].next=head[u];
	head[u]=tot++;
	edge[tot].to=u;
	edge[tot].next=head[v];
	head[v]=tot++; 
}
//链式前向星

int siz[N],son[N],fa[N],dep[N];
//第一次dfs获取以上值
//子树节点数siz
//重儿子下标son
//父节点下标fa
//节点深度dep，相对于1
void dfs1(int u,int f){
	siz[u]=1;
	fa[u]=f;
	dep[u]=dep[f]+1;
	int maxsize=-1;
	for(int i=head[u];~i;i=edge[i].next){
		int v=edge[i].to;
		if(v==f)continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>maxsize){
			maxsize=siz[v];
			son[u]=v;
		}
	}
}
int v[N],w[N],tim,dfn[N],top[N];
//第二次dfs获取以上值
//dfn  dfs序
//top  链头 真正剖分出重链的地方
//tim  时间戳
//w    按照dfs序重新映射的序列   把树拆分为链
void dfs2(int u,int t){
	dfn[u]=++tim;
	w[tim]=v[u];
	top[u]=t;
	if(!son[u])return;
	dfs2(son[u],t);
	for(int i=head[u];~i;i=edge[i].next){
		int v=edge[i].to;
		if(v==fa[u] || v==son[u])continue;
		dfs2(v,v);	
	}
}
void init(){
	n=read(),m=read();
	for(int i=1;i<=n;++i)v[i]=Mod(read());
	memset(head,-1,sizeof(head));
	int t1,t2;
	for(int i=1;i<n;++i){
		t1=read(),t2=read();
		addEdge(t1,t2);
	}
}

//维护区间和的线段树，不是重点
int sgt[N<<2],lazy[N<<2];
inline int ls(int p){
	return p<<1;
}
inline int rs(int p){
	return p<<1|1;
}
inline void pushup(int p){
	sgt[p]=Mod(sgt[ls(p)]+sgt[rs(p)]);
}
inline void pushdown(int p,int l,int r){
	int mid=(l+r)>>1;
	lazy[ls(p)]=Mod(lazy[ls(p)]+lazy[p]); 
	lazy[rs(p)]=Mod(lazy[rs(p)]+lazy[p]);
	sgt[ls(p)]=Mod( sgt[ls(p)]+Mod( Mod(mid-l+1)* lazy[p] ) );
	sgt[rs(p)]=Mod( sgt[rs(p)]+Mod( Mod(r-mid)* lazy[p] ) );
	lazy[p]=0;
}
int query(int p,int l,int r,int tL,int tR){
	if(l==r){
		return sgt[p]=Mod(sgt[p]);
	}
	if(tL<=l&&r<=tR)return sgt[p]=Mod(sgt[p]);
	int res=0,mid=(l+r)>>1;
	pushdown(p,l,r);
	if(tL<=mid)res=Mod( res+query(ls(p),l,mid,tL,tR) );
	if(tR>mid)res=Mod( res+query(rs(p),mid+1,r,tL,tR) );
	return res;
}
void modify(int p,int l,int r,int tL,int tR,int k){
	if(l==r){
		sgt[p]=Mod(sgt[p]+k);
		return;
	}
	if(tL<=l&&r<=tR){
		lazy[p]=Mod(lazy[p]+k);
		sgt[p]=Mod( Mod(Mod(r-l+1)*k) + sgt[p] );
		return;
	}
	int mid=(l+r)>>1;
	pushdown(p,l,r);
	if(tL<=mid)modify(ls(p),l,mid,tL,tR,k);
	if(tR>mid)modify(rs(p),mid+1,r,tL,tR,k);
	pushup(p);
}

void mchain(int x, int y, int z)
{
    z%=mod;
    while (top[x]!=top[y])
    {
        //不在一条链上时
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        modify(1,1,n,dfn[top[x]],dfn[x],z);
        x=fa[top[x]];
        //往上方跳转，最终会会和
    }
    //在一条链上时
    if(dep[x]>dep[y])swap(x,y);
    modify(1,1,n,dfn[x],dfn[y],z);
}
int qchain(int x,int y){
    //复读 mchain
	int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		res=Mod(res+query(1,1,n,dfn[top[x]],dfn[x]));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return Mod(res+query(1,1,n,dfn[x],dfn[y]));
}

void build(int p,int l,int r){
	if(l==r){
		sgt[p]=w[l];
		return;
	}
	int mid=(l+r)>>1;
	build(ls(p),l,mid);
	build(rs(p),mid+1,r);
	pushup(p);
}
signed main(){
	init();

    //无根树，因为1总是存在，就取1为根了
	dfs1(1,1);
	dfs2(1,1);
    //树剖基操
    
	build(1,1,n);
	int opt,x,y,z;
	while(m--){
		opt=read(),x=read(),y=read();
		if(opt==1){
			z=read();
			mchain(x,y,z);
		}
		else{
			printf("%d\n",qchain(x,y));
		}
	}
	return 0;
}
