#include<bits/stdc++.h>
using namespace std;
inline int read(){
	char c=getchar();int x=0;
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+c-48,c=getchar();
	return x;
}
//slow read
int main(){
	int n=read();
	for(int i=0;i<n;++i)
		if(read()&1){
			//题目保证序列中全为正整数，故可以使用&运算对2取模
			//如果存在奇数
			printf("Alice");
			return 0;
		}
	printf("Bob");
}