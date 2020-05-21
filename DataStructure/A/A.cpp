#include<iostream>
inline bool isRight(char x){
	return x==')';
}
//判断是左括号还是右括号
using namespace std;
int t,n,S,cnt;
//t是数据组数(石头数目），n是每组数据的长度（石头上的划痕数）
//S用来模拟stack，cnt是答案计数器
char temp;
int main(){

	ios::sync_with_stdio(0);
	cin.tie(0);

	cin>>t;
	for(int i=1;i<=t;++i){
		//枚举石头
        
		cnt=0;
		S=0;
        //初始化答案，清空栈

		cin>>n;
		for(int j=1;j<=n;++j){
			//枚举划痕
			cin>>temp;
			if(isRight(temp)){
                //右括号出栈
				if(0==S){
                    //右括号多于左括号，补齐，答案加一
					++cnt;
				}
				else{
					--S;
				}
			}
			else{
                //左括号入栈
				++S;
			}
		}
        //左括号多于右括号
		cnt+=S;
		cout<<cnt<<endl;
	}
	return 0;
}
