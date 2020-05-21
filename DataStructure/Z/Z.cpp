#include<bits/stdc++.h>
using namespace std;
int n,m;
//n 节点数
//m 操作数
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
struct ODT{
	int l,r;
	mutable int v;
    //这里要加mutable，以便可以使用const iterator修改
	ODT(const int& _l,const int& _r=0,const int& _v=0)
	:l(_l),r(_r),v(_v)
	{
		
	}
	bool operator<(const ODT& other) const{
		return l<other.l;
	}
};
set<ODT> odt;
typedef set<ODT>::iterator IT;
void initODT(){
	n=read();
	for(int i=1;i<=n;++i){
		odt.insert(ODT(i,i,read()));
        //一个节点，一个区间
	}
}
IT split(int pos){
    //the core
    
	IT it=odt.lower_bound(ODT(pos));
    //大于等于改节点的第一个节点
	if(it!=odt.end()&&it->l==pos)return it;//等于的情况，不修改，直接返回
	--it; //否则一定在前一个节点
	int L=it->l,R=it->r,V=it->v;
	odt.erase(it);
	odt.insert(ODT(L,pos-1,V));
	return odt.insert(ODT(pos,R,V)).first;
    //将当前区间一分为二，并返回pos处的区间
}
int query_assign(int l,int r,int c){
	int res=0;
	IT itr=split(r+1),itl=split(l);
    //顺序很重要，因为itr的获取可能会让itl失效
	IT old=itl;
	for(;itl!=itr;++itl){
        //暴力遍历
		if(itl->v!=c){
			res+=(itl->r-itl->l+1);
		}
	}
	odt.erase(old,itr);
	odt.insert(ODT(l,r,c));
    //推平为大区间
	return res;
}
signed main(){
	initODT();
	m=read();
	int tmpl,tmpr,tmpc;
	while(m--){
		tmpl=read(),tmpr=read(),tmpc=read();
		printf("%d\n",query_assign(tmpl,tmpr,tmpc));
	}
	return 0;
}
