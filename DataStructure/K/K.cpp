#include<bits/stdc++.h>
#define rep(i,n) for(register int i=1;i<=n;++i)
using namespace std;
const int N=1e6+5;
int sta[N];
//伪单调栈
bool inStack[N];
//记录是否在栈中
int arr[N];
//离线数组
int lastTime[N];
//元素最后一次出现位置
int cnt,n,k;
//n是规模，k是目标长度,cnt是stack的顶部指针
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
int main(){
	n=read(),k=read();
	rep(i,n){
		arr[i]=read();
		lastTime[arr[i]]=i;
	}
	int temp;
	sta[0]=INT_MIN;
	rep(i,n){
		temp=arr[i];
		if(inStack[temp])continue;
        //在栈中，忽略
		while(sta[cnt]>temp){
			if(lastTime[sta[cnt]]>i){
                //被弹出
				inStack[sta[cnt]]=0;
				--cnt;
			}
			else break;
            //受正确性限制而终止
		}
		sta[++cnt]=temp;
		inStack[temp]=1;
	}
	if(cnt==k){
		rep(i,k)printf("%d ",sta[i]);
	}
	else printf("Kanade");
	return 0;
}
