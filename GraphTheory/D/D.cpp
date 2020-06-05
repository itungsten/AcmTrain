#include<bits/stdc++.h>
#define INF 1e30
//随手糊的最大值
using namespace std;
const int N=5e3+5;
const int M=5e3+5;
int n,m;
//约束系统变量的个数和约束的个数
struct Edge{
    int u,v;
    float w;
}edge[M<<1];
//开两倍空间是因为会添加超级源点保证连通性
int cnt; //内存池计数器
float dis[N]; //超级源点作为源点的最短路
inline int read(){
    char c=getchar();int x=0,f=1;
    while(!isdigit(c))c=='-'&&(f=-1),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+c-48,c=getchar();
    return x*f;
}
//quick read
bool bellman_ford(){
    for(int i=1;i<=n;++i)dis[i]=INF;
    dis[0]=0;
    //最短路基操 0是超级源点

    for(int i=1;i<=n;++i){
        //添加了超级源点后，本质有n+1个点，最多松弛n次
        for(int j=1;j<=cnt;++j){
            int u=edge[j].u,v=edge[j].v;
            float w=edge[j].w;
            dis[v]=min(dis[v],dis[u]+w);
            //真。暴力松弛
        }
    }
    for(int j=1;j<=cnt;++j){
        int u=edge[j].u,v=edge[j].v;
        float w=edge[j].w;
        if(dis[v]>dis[u]+w){
            //判负环，因为最多松弛n次
            return 0;
        }
    }
    return 1;
}
void addEdge(int u,int v,float w){
    edge[++cnt].u=u;
    edge[cnt].v=v;
    edge[cnt].w=w;
}
signed main(){
    n=read(),m=read();
    for(int i=1;i<=n;++i){
        addEdge(0,i,0);
    }
    //添加超级源点
    int o,u,v;
    float w;
    for(int i=1;i<=m;++i){
        o=read(),u=read(),v=read();
        scanf("%f",&w);
        switch(o){
            //考虑都为正数，可以求对数把乘法关系转化为差分系统
            case 1:
                addEdge(u,v,-1*log(w));
                break;
            case 2:
                addEdge(v,u,log(w));
                break;
            case 3:
                addEdge(v,u,log(w));
                addEdge(u,v,-1*log(w));
                break;
        }
    }
    if(!bellman_ford())printf("Delicious");
    else{
        printf("DEDEDEDEDEDEDEDEDEDEDEDE");
    }
    return 0;
}
