#include<bits/stdc++.h>
#define int long long
//懒人写法
const int inf=0x3f3f3f3f3f3f3f3f;
//按照题中所述范围，推断可能爆int，使用类似int的INF初始方法，这样在相加时不会溢出
const int N=20;
const int M=1e8+5;
using namespace std;
int n,m;
int a[N+5],b[N+5];
//a，b如题目中所述，分别是左右括号在不同位置的代价
struct Mat
{
    int arr[2*N+5][2*N+5];
    //消除等价情况后，平衡因子不会超过2n个
};
Mat operator*(const Mat& x,const Mat& y)
{
    Mat c;
    for(int i=0;i<2*n;++i){
        for(int j=0;j<2*n;++j){
        	c.arr[i][j]=inf;
        	//类似普通乘法的置零
            for(int k=0;k<2*n;++k){
            	c.arr[i][j]=min(c.arr[i][j],x.arr[i][k]+y.arr[k][j]);
            }
        }
    }
    return c;
}
Mat pow(Mat x,int y)
{
    Mat ans=x;
    y-=1;
    //懒得考虑单位元是什么了，变成乘以自己的(n-1)次方
    while(y){
        if(y&1)ans=ans*x;
        x=x*x;
        y>>=1;
    }
    return ans;
}
Mat getN(){
	Mat beg;
	for(int i=0;i<2*n;++i){
		for(int j=0;j<2*n;++j){
			beg.arr[i][j]=inf;
			if(j==i-1)beg.arr[i][j]=a[0];
			if(j==i+1)beg.arr[i][j]=b[0];
			//如题解所述技巧
			//k=j-1时为a[i]
			//k=j+1时为b[i]
			//否则为正无穷
		}
	}
	//同样，不想思考单位元
	Mat tmp;
	for(int k=1;k<n;++k){
		for(int i=0;i<2*n;++i){
			for(int j=0;j<2*n;++j){
				tmp.arr[i][j]=inf;
				if(j==i-1)tmp.arr[i][j]=a[k];
				if(j==i+1)tmp.arr[i][j]=b[k];
			}
		}
		beg=tmp*beg;
		//这里巨坑，由于矩阵乘法不满足交换律，所以要注意顺序
	}
	return beg;
}
signed main(){
	//懒人写法
	cin>>n>>m;
	for(int i=0;i<n;++i)cin>>a[i];
	for(int i=0;i<n;++i)cin>>b[i];
	Mat ans=pow(getN(),m);
	//getN()返回转移n步的结果（因为n步中每步的转移是不同的，所以n步才是一个基本单元，看作一个组）
	//然后利用这个组转移m次，最终转移n*m次
	cout<<ans.arr[0][0];
	//由初态和终态可知，只有这元素参与贡献
	return 0;
}