#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
bool vis[N<<1];
//一个变量要拆分为两个点，以下同样
int LOW[N<<1],DFN[N<<1],head[N << 1],top,dfs_num,sta[N << 1],color[N << 1],CN;
int n,m;
//变量数目，约束数目
struct Edge{
    int to,nxt;
}E[N*6];
//一个约束会拆分出6条边
int cntEdge; //内存池计数器
void tarjan(int pos){
    if(DFN[pos])return;
    //考虑有多个连通分量的情况，如果已经访问，直接返回
    vis[sta[++top]=pos]=1;//入栈并标记已经入栈
    LOW[pos]=DFN[pos]=++dfs_num;	//更新DFN，初始化LOW
    for(int i=head[pos]; i; i=E[i].nxt){
        if(!DFN[E[i].to]){
        	//生成树边
            tarjan(E[i].to);
            LOW[pos]=min(LOW[pos],LOW[E[i].to]);
            //维护子树的LOW
        }
        else if(vis[E[i].to]) LOW[pos]=min(LOW[pos],DFN[E[i].to]);
        //在栈中，是返祖边或者前向边
    }
    if(LOW[pos]==DFN[pos]){
    	//连通分量中那个特殊的点，连通分量中的点一定在它的子树中
        vis[pos]=0;
        //出栈
        color[pos]=++CN;
        //染色
        while(pos != sta[top]){
            vis[sta[top]]=0;
            color[sta[top--]]=CN;//弹栈并染色
        }
        top--;
    }
}
void insertEdge(int u,int v){
    E[++cntEdge].to=v;
    E[cntEdge].nxt=head[u];
    head[u]=cntEdge;
}
void addEdge(int a,bool u,int b,bool v,int c,bool w){
    //对原本的i号变量，拆分为两个点
    //真 2i-1 假2i
    insertEdge(2*a-1+u,2*b-v);
    insertEdge(2*a-1+u,2*c-w);
    //(a,u)为假，则(b,v)和(c,w)为真

    insertEdge(2*b-1+v,2*a-u);
    insertEdge(2*b-1+v,2*c-w);
    //同理

    insertEdge(2*c-1+w,2*b-v);
    insertEdge(2*c-1+w,2*a-u);
    //同理
}
signed main(){
    scanf("%d%d",&n,&m);
    int a,u,b,v,c,w;
    for(int i=1;i<=m;++i){
        scanf("%d%d%d%d%d%d",&a,&u,&b,&v,&c,&w);
        addEdge(a,u,b,v,c,w);
    }
    for(int i=1;i<=2*n;++i){
    	//计算强连通分量
        tarjan(i);
    }
    for(int i=1;i<=n;++i){
    	//枚举每一个变量
        if(color[2*i]==color[2*i-1]){
            //变量的两个点不能在同一个强连通分量内，因为同一个分量中的点同真假
            cout<<"NO";
            return 0;
        }
    }
    cout<<"YES";
    return 0;
}
