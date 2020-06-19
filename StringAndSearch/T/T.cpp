#include<bits/stdc++.h>
const int N = 5+5;
//棋盘最大规模
using namespace std;
int n,k;
//n是规模
//k是局数
int chess[N][N];
//棋盘
int getSum(int i,int j){
	return chess[i][j]+chess[i+1][j]+chess[i][j+1]+chess[i+1][j+1];
}
//以左上方的点为标志，2x2的和
void rotate(int i,int j){
	int tmp=chess[i][j];
	chess[i][j]=chess[i][j+1];
	chess[i][j+1]=chess[i+1][j+1];
	chess[i+1][j+1]=chess[i+1][j];
	chess[i+1][j]=tmp;
}
//以左上方的点为标志，2x2逆时针旋转
void rotateReverse(int i,int j){
	int tmp=chess[i][j];
	chess[i][j]=chess[i+1][j];
	chess[i+1][j]=chess[i+1][j+1];
	chess[i+1][j+1]=chess[i][j+1];
	chess[i][j+1]=tmp;
}
//以左上方的点为标志，2x2顺时针旋转
int max_min_search(int level,int alpha,int beta,int score){
	if(level>2*k)return score;
	//游戏结束，score不变
	int res=level&1?INT_MIN:INT_MAX;
	//当前层的最值
	if(alpha>=beta)return res;
	//cut
	for(int i=1;i<n;++i){
		for(int j=1;j<n;++j){
			//enumerate
			rotate(i,j);
			int ans=max_min_search(level+1,alpha,beta,score+getSum(i,j));
			//总得分
			if(level&1){
				res=max(res,ans);
				alpha=max(alpha,res);
				//奇数层要求最大值，并且只能维护alpha
			}
			else{
				res=min(res,ans);
				beta=min(beta,res);
			}
			rotateReverse(i,j);
			//traceback
			if(alpha>=beta)return res;
			//cut
		}
	}
	return res;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	//慢读
	cin>>n>>k;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			cin>>chess[i][j];
		}
	}
	cout<<max_min_search(1,INT_MIN,INT_MAX,0);
	//alpha，beta要初始化为期望的相反面
	return 0;
}