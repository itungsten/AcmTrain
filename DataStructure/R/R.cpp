#include<bits/stdc++.h>
#define rep(i,n) for(register int i=1;i<=n;++i)
using namespace std;
const int N=1e6+5;
const int M=1e5+5;
int n,m,cnt=0,root=0;
//cnt是内存池计数器
//root是版本号计数器
int T[M];
//用来记录各版本的root
int V[N<<5],L[N<<5],R[N<<5];
//节点的值 V   此处，线段树中间节点的值没有意义，只是利用了线段树的二分能力
//节点的左儿子 L
//节点的右儿子 R
int a[N];
//原生数组 用来读入

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

int query(int now,int pos,int l,int r){
	if(l==r)return V[now];
	int mid=(l+r)>>1;
	if(pos<=mid)return query(L[now],pos,l,mid);
	else return query(R[now],pos,mid+1,r);
}
int update(int pre,int val,int pos,int l,int r){
    //pre是旧版本的对应节点
	int rt=++cnt;
	if(l==r){
		V[rt]=val;
		return rt;
	}
	else{
		int mid=(l+r)>>1;
		if(pos<=mid){
			R[rt]=R[pre];
            //连接旧版本
			L[rt]=update(L[pre],val,pos,l,mid);
            //连接新版本
		}
		else
		{
			L[rt]=L[pre];
            //连接旧版本
			R[rt]=update(R[pre],val,pos,mid+1,r);
            //连接新版本
		}
		return rt;
	}
    //无pushup，因为中间节点V无意义
}
int build(int l,int r){
	int rt=++cnt;
	if(l==r){
		V[rt]=a[l];
		return rt;
	}
	int mid=(l+r)>>1;
	L[rt]=build(l,mid);
	R[rt]=build(mid+1,r);
	return rt;
}
int main(){
	n=read(),m=read();
	rep(i,n)a[i]=read();
	T[0]=build(1,n);
    //创建初始版本
	int opt,version,x,y;
	rep(i,m){
		opt=read(),version=read(),x=read();
		if(1==opt){
			y=read();
			T[++root]=update(T[version],y,x,1,n);
            //生成新版本
		}
		else{
			printf("%d\n",query(T[version],x,1,n));
		}
	}
}
