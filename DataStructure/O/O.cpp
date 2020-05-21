#include<bits/stdc++.h>
using namespace std;
const int N=2e6+5;
int tr[N<<2],a[N],n,m;
//a是普通array
//tr是segment tree
//n是麦穗数
//m是天数
inline int Mod(int x,int y){
    //在环上求距离
	return (x-y+n)%n;
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
//quickread

inline int ls(int p){
	return p<<1;
}
inline int rs(int p){
	return p<<1|1;
}
inline void pushUp(int p){
    //维护区间最值，便于搜索
	tr[p]=max(tr[ls(p)],tr[rs(p)]);
}
void build(int p,int l,int r){
	if(l==r){
		tr[p]=a[l];
        //其实好像是可以直接读进tr里面，但是懒得改了
		return;
	}
	int m=(l+r)>>1;
	build(ls(p),l,m);
	build(rs(p),m+1,r);
	pushUp(p);
}
int query(int p,int l,int r,int pos,int k,bool way){
    //way是bool变量 true是查询pos和右侧，false查询pos左侧
	if(way){
        //剪掉左侧区间
		if(r<pos)return -1;
	}
	else{
        //剪掉右侧区间
		if(l>=pos)return -1;
	}
	if(tr[p]<k)return -1;
    //区间剪枝
	if(l==r){
		tr[p]=INT_MIN;
        //GG
		return l;
	}
	int m=(l+r)>>1;
	int ans=query(ls(p),l,m,pos,k,way);
	if(ans==-1)ans=query(rs(p),m+1,r,pos,k,way);	
	pushUp(p);
    //query & modify together
	return ans;
}
int main(){
	n=read();
	for(int i=1;i<=n;++i)a[i]=read();
	m=read(); 
	build(1,1,n);
	int s,t,ans;
	for(int i=0;i<m;++i){
		s=read(),t=read();
		ans=query(1,1,n,s+1,t-i,1);
        //i是偏移量
		if(ans==-1)ans=query(1,1,n,s+1,t-i,0);
		if(ans==-1)puts("-1");
		else printf("%d\n",Mod(ans,s+1));
	}
	return 0;
}
