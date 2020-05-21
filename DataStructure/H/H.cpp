#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int B=318;
//B是最大块数目，B*B近似等于N

int a[N],n,m,k;
//a是被操作数组，n是节点数，m是操作次数，k是模数

int tot,block,lazy[B],sta[B][N],L[B],R[B],bel[N];
//tot 总块数
//block 块大小
//lazy 区间懒标记
//sta 即status，整块取模余数统计
//L 块的左端点
//R 块的右端点
//bel 节点属于的块

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

inline int Mod(int x){
    //不会翻车取模法
	return (x%k+k)%k;
}
void initBlock(){
	block=sqrt(n);
	tot=n/block;
	if(n%block)++tot;//不是倍数关系，补一个块

	for(int i=1;i<=n;++i){
		bel[i]=(i-1)/block+1;
		++sta[bel[i]][a[i]];
	}
    //init bel and sta

	for(int i=1;i<=tot;++i){
		L[i]=(i-1)*block+1;
		R[i]=i*block;
	}
    //init L and R
	R[tot]=n;
    //无论是否补了一个块，最后的块的右端点一定是n
}
int query2modify(int l,int r,int c,int d){
    //和在一起，可能常数会小一点(x
    //其实是方便一点
	c=Mod(c),d=Mod(d);
    //不写这个爆int，谁爆谁知道
	int res=0,tar;
	if(bel[l]==bel[r]){
        //特判同一个块，暴力
		tar=Mod(c-lazy[bel[l]]);
        //减去偏移量
		for(int i=l;i<=r;++i){
			if(a[i]==tar)++res;
			--sta[bel[l]][a[i]];
			a[i]=Mod(a[i]+d);
			++sta[bel[l]][a[i]];
            //更新sta
		}
		return res;
	}
    //此时块的个数一定大于等于二
    //左散块
	tar=Mod(c-lazy[bel[l]]);
	for(int i=l;i<=R[bel[l]];++i){
		if(a[i]==tar)++res;
		--sta[bel[l]][a[i]];
		a[i]=Mod(a[i]+d);
		++sta[bel[l]][a[i]];
	}
    //右散块
	tar=Mod(c-lazy[bel[r]]);
	for(int i=L[bel[r]];i<=r;++i){
		if(a[i]==tar)++res;
		--sta[bel[r]][a[i]];
		a[i]=Mod(a[i]+d);
		++sta[bel[r]][a[i]];
	}
    //如果有的话，中间的块
	for(int i=bel[l]+1;i<bel[r];++i){
		tar=Mod(c-lazy[i]);
		res+=sta[i][tar];
		lazy[i]=Mod(lazy[i]+d);
        //打lazy
	}
	return res;
}
signed main(){
	n=read(),k=read();
	for(int i=1;i<=n;++i)a[i]=Mod(read());
	initBlock();
	int l,r,c,d;
	m=read();
	while(m--){
		l=read(),r=read(),c=read(),d=read();
		printf("%d\n",query2modify(l,r,c,d));
	}
	return 0;
}
