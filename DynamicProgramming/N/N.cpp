#include<bits/stdc++.h>
using namespace std;
const int N=205;
const int P=205;
int siz[N],fa[N],f[N][P],n,p,son[N];
//siz 子树大小
//fa 父亲节点
//f DP数组
//son 儿子节点数目
vector<int> edge[N];
inline int read(){
    int x=0;char c=getchar();
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+c-48,c=getchar();
    return x;
}
void dfs(int now,int par){
    fa[now]=par;
    siz[now]=1;
    int to;
    for(int i=0;i<edge[now].size();++i){
        to=edge[now][i];
        if(to==par)continue;
        dfs(to,now);
        siz[now]+=siz[to];
        for(int j=siz[now];j>0;--j){
        	//枚举当前可能的子树大小，注意顺序，这样才能保证是新子树的影响
            for(int k=1;k<j&&k<=siz[to];++k){
                f[now][j]=min(f[now][j],f[now][j-k]+f[to][k]-1);
                //少减去一条边
            }
        }
    }
}
signed main(){
    n=read(),p=read();
    for(int i=1;i<=n;++i){
        memset(f[i],0x3f,sizeof(f[i]));
        //初始化
    }
    for(int i=1;i<n;++i){
        int u=read(),v=read();
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    for(int i=1;i<=n;++i){
        if(i==1)son[i]=edge[i].size();
        //根节点没有父亲节点
        else son[i]=edge[i].size()-1; 
        f[i][1]=son[i];
        //初始化dp数组
    }
    dfs(1,-1);
    int ans=f[1][p];
    for(int i=2;i<=n;++i){
        ans=min(ans,f[i][p]+1);
        //非根节点要断开与父节点的边
    }
    printf("%d",ans);
    return 0; 
}