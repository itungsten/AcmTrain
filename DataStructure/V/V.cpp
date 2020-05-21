#include<bits/stdc++.h>
#define mid (l+r)/2
using namespace std;

const int N = 1e6+5;
int tr[N<<2];
//tr是线段树

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

inline int ls(int p){
	return p<<1;
}
inline int rs(int p){
	return p<<1|1;
}
void pushUp(int p){
	tr[p]=max(tr[ls(p)],tr[rs(p)]);
    //线段树维护区间最大值，用于线段树上搜索
}
void build(int p,int l,int r){
	if(l==r){
		tr[p]=read();
		return;

	}
	build(ls(p),l,mid);
	build(rs(p),mid+1,r);
	pushUp(p);
}
int query(int p,int l,int r,int i,int j,int d)
{
    if(l==r) 
    {
        if(tr[p]>=d){
			tr[p]-=d;   	
			return l;
		}
        else
            return -1;
    }
    if(i<=l&&r<=j&&tr[p]<d){
        //区间剪枝
    	return -1;
	}
        
    int ans;
	//只有左子区间都有交集 
    if(j<=mid){
    	ans=query(ls(p),l,mid,i,j,d);
    	goto ending;
	}
	//只有右子区间都有交集 
    if(i>=mid+1){
    	ans=query(rs(p),mid+1,r,i,j,d);
    	goto ending;
	}
	//左右子区间都有交集 
    ans=query(ls(p),l,mid,i,j,d);
    if(ans!=-1){
    	goto ending;
	}
    ans=query(rs(p),mid+1,r,i,j,d); 
ending:
	pushUp(p);
    return ans;
}
int main()
{
	int T,n,m,l,r,k;
	T=read();
	while(T--){
		n=read(),m=read();
		build(1,1,n);
		while(m--){
			l=read(),r=read(),k=read();
			printf("%d\n",query(1,1,n,l,r,k));
		}
	}
    return 0;
}
