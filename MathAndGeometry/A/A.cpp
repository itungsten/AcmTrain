#include<bits/stdc++.h>
using namespace std;
inline int read(){
	char c=getchar();int x=0;
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+c-48,c=getchar();
	return x;
}
int n;
bool exist;
int main(){
	n=read();
	for(int i=0,tmp;i<n;++i){
		tmp=read();
		if(tmp&1){
			exist=true;
			break;
		}
	}
	if(exist)printf("Alice");
	else printf("Bob");
	return 0;
}