#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int in[N],out[N];
//入度，出度
int fa[N];
//并查集
int n;
//矩阵个数
bool vis[N];
//表示元素是否在集合（1-100）内
inline int read(){
    char c=getchar();int x=0;
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+c-48,c=getchar();
    return x;
}
int find(int x){
    if(x==fa[x])return x;
    return fa[x]=find(fa[x]);
}
void uni(int x,int y){
    fa[find(x)]=find(y);
}
//并查集
bool isConnect(){
	//即要求共一个父亲
    int beg=-1;
    for(int i=1;i<=100;++i){
        if(vis[i]){
            if(beg==-1){
                beg=find(i);
                continue;
            }
            if(beg!=find(i))return false;
        }
    }
    return true;
}
inline void Exit(){
	//用得太频繁了
    printf("%d",-1);
    exit(0);
}
signed main(){
    n=read();
    //读入规模
    if(n==1){
    	//特判，随手写的
        printf("%d",read()*read());
        return 0;
    }
    for(int i=1;i<=100;++i)fa[i]=i;
    //初始化并查集
    int l,r;
    for(int i=1;i<=n;++i){
        l=read();r=read();
        //读入矩阵
        ++out[l];
        ++in[r];
        uni(l,r);
       	//把一个矩阵拆分为两个点
        vis[l]=vis[r]=1;
    }
    if(!isConnect())Exit();
    //Eular定理的前提条件
    int best=-1;
    bool flag=1;
    for(int i=1;i<=100;++i){
        if(vis[i]){
            if(in[i]==out[i]){
                best=max(best,i);
            }
            else{
                flag=0;
                break;
            }
        }
    }
    if(flag){
        printf("%d",best*best);
        return 0;
    }
    //处理Eular回路，此时可以选择最大的规模

    int ltemp=-1,rtemp=-1;
    for(int i=1;i<=100;++i){
        if(vis[i]){
            if(in[i]==out[i])continue;
            if(in[i]-out[i]==1){
                if(ltemp==-1)ltemp=i;
                else Exit();
                continue;
            }
            if(out[i]-in[i]==1){
                if(rtemp==-1)rtemp=i;
                else Exit();
                continue;
            }
            Exit();
        }
    }
    if(ltemp!=-1&&rtemp!=-1){
        printf("%d",ltemp*rtemp);
        return 0;
    }
    //处理Eular通路，此时规模给定
    Exit();
}
