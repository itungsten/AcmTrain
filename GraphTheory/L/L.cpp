#include<bits/stdc++.h>
using namespace std;
#define INF 0xfffffff
const int N=2e5+5;
const int M=2e5+5;

struct Node
{
    int idx;double dis;
    //虽然题中都是整数，但是这里有一些处理
    friend bool operator< (const Node& A,const  Node& B)
    {
        return A.dis > B.dis;
        //reverse
        //从大到小
    }
};
bool vis[N];
//是否已经求出最短路
double dis[N];
//最短路长度
int n, m;
//原节点数与边数
vector< vector<Node> > G;  //存图

void Dijkstra(int Beg)
{
    memset(vis,0,sizeof vis);
    //全部没有被确定最短路
    memset(dis,0x3f,sizeof dis);
    dis[Beg]=0;
    //最短路基操
    Node temp;temp.idx=Beg;temp.dis=0;
    priority_queue<Node> Q;Q.push(temp);
    //星星之火，可以燎原（
    while( !Q.empty() )
    {
        temp=Q.top();
        Q.pop();
        int idx=temp.idx;
        if(vis[idx])continue;
        //总会有一些垃圾节点慢慢到堆顶来
        vis[idx]=1;
        //被确定最短路
        dis[idx]=temp.dis;
        int siz = G[idx].size();
        for(int i=0; i< siz; i++)
        {
        	//松弛与之相连的节点
            Node slack;
            slack.idx = G[idx][i].idx;
            slack.dis = temp.dis+G[idx][i].dis;
            if(!vis[slack.idx])Q.push(slack);
        }
    }
}
inline int read(){
    char c=getchar();int x=0;
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+c-48,c=getchar();
    return x;
}
int main()
{
    G.clear();
    n=read();m=read();
    //点，边
    G.resize(n+1);
    //不resize预留空间，下标访问就会段错误
    Node P;
    int u,v;
    double w;
    for(int i=0; i<m; ++i) {
        u = read(), v = read();
        scanf("%lf",&w);
        P.idx = v;
        P.dis = w;
        G[u].push_back(P);
        P.idx = u;
        G[v].push_back(P);
        //双向边
    }
    for(int i=1;i<=n;++i){
        P.idx=i;
        scanf("%lf",&P.dis);
        P.dis=P.dis/2;
        G[0].push_back(P);
        //超级源点
        //注意这里边权不是0，而是门票的1/2，这是为了让门票和路费可以同时乘2
    }
    Dijkstra(0);
    for(int i=1;i<=n;++i){
        cout<<(long long)round(dis[i]*2)<<" ";
    }
    return 0;
}
/*
   2 1
   1 2 1
   10 5
   */
