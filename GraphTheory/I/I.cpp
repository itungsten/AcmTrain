#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,idx,tot;
int DFN[N],LOW[N];
bool cut[N];
vector<int> edge[N];
void add (int x,int y)
{
    edge[x].push_back(y);
    edge[y].push_back(x);
}
void tarjan (int u,int root)
{
    DFN[u]=LOW[u]=++idx;
    int ch=0;
    for (int i=0;i<edge[u].size();++i)
    {
        int v=edge[u][i];
        if (!DFN[v])
        {
            tarjan(v,root);
            LOW[u]=min(LOW[u],LOW[v]);
            if (LOW[v]>=DFN[u]&&u!=root)
                cut[u]=1;
            if(u==root)++ch;
        }
        LOW[u]=min (LOW[u],DFN[v]);
    }
    if (ch>=2&&u==root)
        cut[u]=1;
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
    for (int i=1;i<=n;i++)cut[i]&&++tot;
    printf("%d",tot);
    return 0;
}