#include<bits/stdc++.h>
const int N = 2e6+5;
//最长长度乘2，因为有连接操作
using namespace std;
string a,b;
int nxt[N];
//最长真前缀和后缀
void kmp(string &a,string &b){
	string tmp;
	tmp+=a;
	tmp+='@';
	tmp+=b;
	//连接ab，并且使用特殊字符防止越界
	int la=a.size();
	int lb=b.size();
	for(int i=1;i<tmp.size();++i){
		int u=nxt[i-1];
		//初始化为前面一个字符的结果，此时可能匹配，也可能不匹配，如果匹配，结束
		while(u>0&&tmp[u]!=tmp[i])u=nxt[u-1];
		if(tmp[u]==tmp[i])++u;
		//可能的确一个都找不到
		nxt[i]=u;
		if(tmp[u]=='@')printf("%d ",i+1-2*la);
	}
}
int main() {
	cin>>b>>a;
	kmp(a,b);
	return 0;
}