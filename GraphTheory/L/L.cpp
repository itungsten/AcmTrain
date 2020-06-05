#include<bits/stdc++.h>
using namespace std;
#define INF 0xfffffff
const int N=2e5+5;
const int M=2e5+5;

struct Node
{
    int idx;double dis;
    friend bool operator< (const Node& A,const  Node& B)
    {
        return A.dis > B.dis;
        //reverse
    }
};
bool vis[N];
double dis[N];
int m, n;
vector< vector<Node> > G;

int Dijkstra(int Beg)
{
    memset(vis,0,sizeof vis);
    memset(dis,0x3f,sizeof dis);
    dis[Beg]=0;
    Node temp;temp.idx=Beg;temp.dis=0;
    priority_queue<Node> Q;Q.push(temp);
    while( !Q.empty() )
    {
        temp=Q.top();
        Q.pop();
        int idx=temp.idx;
        if(vis[idx])continue;
        vis[idx]=1;
        dis[idx]=temp.dis;
        int siz = G[idx].size();
        for(int i=0; i< siz; i++)
        {
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
    G.resize(n+1);
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
    }
    for(int i=1;i<=n;++i){
        P.idx=i;
        scanf("%lf",&P.dis);
        P.dis=P.dis/2;
        G[0].push_back(P);
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
