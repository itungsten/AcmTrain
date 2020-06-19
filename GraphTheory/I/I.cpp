#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,idx,tot;
//n是点数
//m是双向边数
//idx是访问计数
//tot是割点数
int DFN[N],LOW[N];
bool cut[N];
vector<int> edge[N];
//存图
void add (int x,int y)
{
    edge[x].push_back(y);
    edge[y].push_back(x);
//双向边
}
void tarjan (int u,int root)
{
    DFN[u]=LOW[u]=++idx;
    //初始化LOW
    int ch=0;
    //对于根节点，判定割点的方法特殊
    for (int i=0;i<edge[u].size();++i)
    {
        int v=edge[u][i];
        if (!DFN[v])
        {
        	//树边
            tarjan(v,root);
            LOW[u]=min(LOW[u],LOW[v]);
            if (LOW[v]>=DFN[u]&&u!=root)
                cut[u]=1;
            //即子树内的节点无法于u上方节点连接，故被割掉
            if(u==root)++ch;
            //根节点特殊
        }
        LOW[u]=min (LOW[u],DFN[v]);
    }
    if (ch>=2&&u==root)
        cut[u]=1;
    //根节点特殊
}
inline int read(){
	char c=getchar();int x=0;
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+c-48,c=getchar();
	return x;
}
int main()
{
	n=read(),m=read();
    while(m--)add(read(),read());
    for(int i=1;i<=n;i++)if(!DFN[i])tarjan(i,i);
    //考虑可能有多个连通分量
    for (int i=1;i<=n;i++)cut[i]&&++tot;
    //等价于if(cut[i]==true)tot++;
    printf("%d",tot);
    return 0;
}