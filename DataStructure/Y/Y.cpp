#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
using namespace std;
const int N=2e5+5;
const int M=4e4+5;
int n,m,T,a[N],b[N];
//T 数据组数
//n 节点数
//m 操作数
//a a数组
//b 异或差分数组
int tr[N],k;
//tr 树状数组，此处其实不是维护a数组，而且a数组的变化值，因为异或运算具有交换律和结合律
inline int read(){
    int x=0;char c=getchar();bool f=1;
    while(!isdigit(c)){
        if(c=='-')f=0;
        c=getchar();
    }
    while(isdigit(c)){
        x=(x<<1)+(x<<3)+c-48;
        c=getchar();
    }
    return f?x:-x;
}
struct Node{
    int bas[31];
    //每个节点的线性基
    void add(int x){
        //板子，动态插入法
        for(int i=29;i>=0;--i){
            if((1<<i)&x){
                if(bas[i]){
                    x ^=bas[i];
                }else{
                    bas[i]=x;
                    return;
                }
            }
        }
    }
    int count(){
        //计算维度
        int cnt=0;
        for(int i=29;i>=0;--i)
            if(bas[i])cnt++;
        return cnt;
    }
    void clear(){
        memset(bas,0,sizeof(bas));
    }
}sgt[N<<2];
Node operator+ (const Node& a ,const Node& b)
{
    //合并两个线性基
    Node res=a;
    for(int i=29;i>=0;--i)
        if(b.bas[i])res.add(b.bas[i]);
    return res;
}
inline void pushup(int p){
    sgt[p]=sgt[ls]+sgt[rs];
    //加法已经overload
}
void build(int p,int l,int r)
{
    if(l==r){
        b[l]=a[l]^a[l+1];
        sgt[p].clear();
        sgt[p].add(b[l]);
        return;
    } 
    int mid=(l+r)>>1;
    build(lson),build(rson);
    pushup(p);
}
void updsgt(int p,int l,int r,int pos)
{
    if(l==r){
        b[l]^=k;
        sgt[p].clear();
        sgt[p].add(b[l]);
        return;
    }
    int mid=(l+r)>>1;
    if(pos<=mid)updsgt(lson,pos);
    if(pos>mid)updsgt(rson,pos);
    pushup(p);
} 
Node qrysgt(int p,int l,int r,int tL,int tR)
{
    if(l==r)return sgt[p];
    if(tL<=l&&r<=tR)return sgt[p];
    int mid=(l+r)>>1;
    Node res;res.clear();
    if(tL<=mid)res=res+qrysgt(lson,tL,tR);
    if(tR>mid)res=res+qrysgt(rson,tL,tR);
    return res;
}
//线段树

inline int lowbit(int x){
    return x&-x;
}
void updtr(int x,int k){
    while(x<=n){
        tr[x]^=k;
        x+=lowbit(x);
    }
}
int qrytr(int x){
    int res=0;
    while(x){
        res^=tr[x];
        x-=lowbit(x);
    }
    return res;
}
//树状数组
int main()
{
	T=read();
	while(T--){
		n=read(),m=read();
	    for(int i=1;i<=n;++i)a[i]=read();

	    build(1,1,n); //建立线段树,而树状数组是每次循环结束后初始化的
	    int opt,l,r;
	    while(m--){
	        opt=read(),l=read(),r=read();
	        if(opt==1){
	            k=read();
	            updtr(l,k),updtr(r+1,k);
                //更新增量
	            if(l>1)updsgt(1,1,n,l-1);
                //0号位置是不存在元素的
	            updsgt(1,1,n,r);
	        }else{
	            int v=a[l]^qrytr(l);
                //a[l]的当前值，是a[l]的初始值和增量的异或
	            if(n==1||l==r)printf("%d\n",v?2:1);  //由于使用了差分，会假设出现一些不存在的节点，要小心
                //比如当n==1时，l只能等于r，此时再求取l到r-1会发生我不想去理解的事情
	            else{
	                Node ans=qrysgt(1,1,n,l,r-1);
	                ans.add(v);
	                printf("%d\n",1<<(ans.count()));
	            }
	        }
	    }
	    if(T)memset(tr,0,sizeof(int)*(n+2));
        //23333
	}
    return 0;
}
