#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+5;
const int INF=LONG_LONG_MAX/2;
//开long long就用long long的1/2咯
int n,m;
//节点数，边数
inline int read(){
    char c=getchar();int x=0;
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+c-48,c=getchar();
    return x;
}
int a[N], e[N], l[N],in[N], out[N];
//a 节点权值
//e early time
//l late time
//in in degree
//out out degree

vector<int> edgeFor[N];
vector <int> edgeBack[N];
//存放正向边和反向边
void addEdge(int u, int v)
{
    ++in[v], ++out[u];
    edgeFor[u].push_back(v);
    edgeBack[v].push_back(u);
}


int getEarly(int pos)
{
    if (e[pos])return e[pos];
    for (int i = 0; i < edgeBack[pos].size(); ++i)
    {
    	int to=edgeBack[pos][i];
        e[pos] = max(e[pos], getEarly(to)+a[pos]);
        //early要max，取前方最迟
    }
    return e[pos];
}

int getLate(int pos)
{
    if (l[pos] != INF)return l[pos];
    for (int i = 0; i < edgeFor[pos].size(); ++i)
    {
        int to=edgeFor[pos][i];
        l[pos] = min(l[pos], getLate(to) - a[to]);
        //取后方最早
    }
    return l[pos];
}
signed main() {
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)a[i] = read();
    for (int i = 1; i <= m; ++i)
    {
        int u = read(), v = read();
        addEdge(u, v);
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!in[i])addEdge(0, i);
        if (!out[i])addEdge(i, n + 1);
    }
    //添加0号超级源点，n+1号超级汇点
    int endTime = getEarly(n+1);
    fill(l, l+n+1, INF);
    l[n + 1] = endTime;
    getLate(0);
    int sum = 0;
    for (int i = 0; i <= n+1; ++i)
    {
        sum += l[i] - e[i];
    }
    //总摸鱼时间
    printf("%lld\n%lld",endTime,sum);
    return 0;
}