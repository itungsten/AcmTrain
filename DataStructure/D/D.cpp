#include<bits/stdc++.h>
#define N 1000001
using namespace std;
int n,pos;
//n是操作总次数，pos是当前写指针的位置
struct Node{
	int prefixMax;
    //前缀和的最大值（最大嵌套层数）
	int prefixMin;
    //前缀和的最小值（合法性）
	int sum;
    //区间和（合法性）
} node[N<<3];
//考虑极限情况，n取N，全部操作左移或者全部操作右移，所以要开两倍空间
//线段树自带4倍，所以一共8倍
inline int ls(int p){
	return p<<1;
}
inline int rs(int p){
	return p<<1|1;
}
void pushUp(int p){
	int lson=ls(p);
	int rson=rs(p);
	
	node[p].sum=node[lson].sum+node[rson].sum;
	node[p].prefixMin=min(node[lson].prefixMin,node[lson].sum+node[rson].prefixMin);
	node[p].prefixMax=max(node[lson].prefixMax,node[lson].sum+node[rson].prefixMax);
    //前缀和最值具有区间可加性
}
void update(int p,int l,int r,char val){
	if(l==r){
		switch(val){
			case '(':
				node[p].prefixMax=node[p].prefixMin=node[p].sum=1;
				break;
			case ')':
				node[p].prefixMax=node[p].prefixMin=node[p].sum=-1;
				break;
			default:
				node[p].prefixMax=node[p].prefixMin=node[p].sum=0;
		}
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)update(ls(p),l,mid,val);
	else update(rs(p),mid+1,r,val);
	pushUp(p);
}
int query(){
	if(node[1].sum||node[1].prefixMin<0)return -1;
    //不合法:总和不等，或者右括号在左括号左边
	return node[1].prefixMax;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin>>n;
	pos=n+1;
    //初始化写指针在中部
	char temp;
	for(int i=1;i<=n;++i){
		cin>>temp;
		switch(temp){
			case 'L':
				--pos;
				break;
			case 'R':
				++pos;
				break;
			default:
				update(1,1,(N<<3)-1,temp);
		}
		cout<<query()<<" ";
	}
	return 0;
}
