#include<bits/stdc++.h>
#define N 200005 
using namespace std;
typedef long long ll;

ll n,k,all,cnt;
//n是生物数目，k是目标能力值，all是所有区间取法的数目，cnt是符合要求的区间数目
ll arr[N],tr[N];
//arr是前缀和数组，tr是树状数组
struct Node{
	int idx;
	ll num;
} node[N];
//用来排序求逆序对
bool myCompare(const Node& a,const Node& b){
	if(a.num==b.num)return a.idx<b.idx; 
    //因为是逆序对，如果两者值相同，要考虑排序稳定。
	return a.num>b.num;
    //从大到小
}
ll gcd(ll x,ll y){
	return y?gcd(y,x%y):x;
}
inline int lowbit(int x){
	return x&-x;
}
ll sum(int x){
	ll res=0;
	while(x){
		res+=tr[x];
		x-=lowbit(x);
	}
	return res;
}
void add(ll k,int x){
	while(x<=(n+1)){
        //前缀和一共要维护n+1项
		tr[x]+=k;
		x+=lowbit(x);
	}
}
int main(){

	ios::sync_with_stdio(0);
	cin.tie(0); 

	cin>>n>>k;
	all=(n*(n+1))>>1;

	for(int i=1;i<=n;++i){
		cin>>arr[i];
		arr[i]-=k;
        //预处理减去k
		arr[i]+=arr[i-1];
        //前缀和
        
		node[i].idx=i;
		node[i].num=arr[i];
        //用来排序
	}
	sort(node,node+1+n,myCompare);
    //[1,n]的子区间值需要0-n的前缀和,故有n+1项
    
	for(int i=0;i<=n;++i){
		cnt+=sum(node[i].idx+1);
		add(1,node[i].idx+1);
        //树状数组的下标应该从1开始，右移1位
	}
	if(cnt){
		ll t=gcd(cnt,all);
		cout<<cnt/t<<"/"<<all/t;
	}
	else cout<<0<<"/"<<1;
    //不是很懂出题人的想法，就按照题目特判一下，出题人是大爷
	return 0;
}
