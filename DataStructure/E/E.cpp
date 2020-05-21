#include<bits/stdc++.h>
const int N=500+5;
using namespace std;
int st[N][N][10];
//二维st表
int n,m;
//rows and columns

int L,R,Mid,Last=-1;
//L,R,Mid用来二分，Last算是一个patch吧，因为我在奇数上二分写残了

inline int gcd(int x,int y){
	return y?gcd(y,x%y):x;
}
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
inline int lowOdd(int x){
	return x&1?x:x-1;
}
//将Mid转换为奇数
int getGcd(int i,int j,int siz){
    //二维st表的查询，分成4块
	int temp,k=log2(siz);
	temp=gcd(st[i][j+siz-(1<<k)][k],st[i][j][k]);
	temp=gcd(temp,st[i+siz-(1<<k)][j][k]);
	temp=gcd(temp,st[i+siz-(1<<k)][j+siz-(1<<k)][k]);
	return temp;
}
bool check(int ci,int cj,int siz){
	int center=st[ci][cj][0];
    //开采中心
	siz>>=1;
    //类似半径
	if(getGcd(ci-siz,cj-siz,siz<<1|1)==center)return true;
    //都被整除
	else return false;
}
void init(){
    //打表
	for(int k=1;k<10;++k){
		for(int i=1;(i+(1<<k)-1)<=n;++i){
			for(int j=1;(j+(1<<k)-1)<=m;++j){
				st[i][j][k]=gcd(st[i][j+(1<<(k-1))][k-1],st[i][j][k-1]);
				st[i][j][k]=gcd(st[i][j][k],st[i+(1<<(k-1))][j][k-1]);
				st[i][j][k]=gcd(st[i][j][k],st[i+(1<<(k-1))][j+(1<<(k-1))][k-1]);
			}
		}
	}
}
void bisearch(){
	L=1;
	R=lowOdd(n);
	while(L<R){
		
		Mid=lowOdd((L+R)>>1);
		if(Last==Mid){
			Mid+=2;
		}
		else Last=Mid;
		
		int siz=Mid>>1;
		bool flag=false;
		for(int i=siz+1;i<=(n-siz);++i){
			for(int j=siz+1;j<=(m-siz);++j){
				if(check(i,j,Mid)){
					flag=true;
					goto outlet;
				}
			}
		}
	outlet:
		if(flag){
			L=Mid;
		}
		else{
			R=Mid-2;
		}
	}
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j)st[i][j][0]=read();
	}
	init();
	bisearch();
    //找到最大的尺寸,存储在L中
	int cnt=0;
	int siz=L>>1;
	for(int i=siz+1;i<=(n-siz);++i){
		for(int j=siz+1;j<=(m-siz);++j){
			if(check(i,j,L)){
                //一个合法的中心点
				++cnt;
			}
		}
	}
	printf("%d\n%d",L*L,cnt);
	return 0;
}
