#include<bits/stdc++.h>
#define int long 
//懒人写法
using namespace std;
const int N = 3e5+5;
const int M = 3e5+5;

int n, m;
//地区数，边数
struct Edge {
    int u, v, w;
    bool operator< (const Edge& o)const {
        return w < o.w;
    }
    //for sort
} edge[M]; //for MST
struct Node{int u, to, w, nxt;} graph[M << 1]; int cnt,head[N];  //真正存图，链式前向星
bool inq[M];    //该边是否是树边
int fa[N][20], Max[N][20], SecMax[N][20], dep[N];
//fa是倍增的祖先
//Max是该点到祖先的最大边
//Sec是该点到祖先的严格次大边
//dep是转化为有根树后的深度
int sum; int delta = LONG_MAX/2;
//sum是最小生成树边权和
//delta是用非树边替换后的最小边权和增量

inline int Pow(int x){
    return 1<<x;
}
inline int read() {
    char c = getchar();int x=0;
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)) x = (x<<1)+(x<<3)+c-48, c = getchar();
    return x;
}
//quick read
void addEdge(int u, int v, int w){
    graph[++cnt].to = v;
    graph[cnt].w = w;
    graph[cnt].nxt = head[u];
    head[u] = cnt;
    //链式前向星
}

int par[N];
int find(int x){
    if(par[x] == x)return x;
    return par[x] = find(par[x]);
}
void uni(int x,int y){
    par[find(x)]=find(y);
    //路径压缩
}
//并查集 for MST
void MST() {
    sort(edge + 1, edge + m + 1); //greedy
    int tot=0,i=1;
    while(tot!=n-1){
        int u = edge[i].u, v = edge[i].v;
        if(find(u) != find(v)) {
            ++tot ;
            uni(u,v);
            inq[i] = 1;
            sum+=edge[i].w;
            addEdge(edge[i].u, edge[i].v, edge[i].w);
            addEdge(edge[i].v, edge[i].u, edge[i].w);
        }
        ++i;
    }
}

void DFS(int pos, int last, int depth){
    dep[pos] = depth;
    fa[pos][0] = last; SecMax[pos][0] = -1; //默认没有严格次大边
    for(int i = 1;dep[pos]>Pow(i);++i) {

        fa[pos][i] = fa[fa[pos][i - 1]][i - 1];
        Max[pos][i] = max(Max[pos][i - 1], Max[fa[pos][i - 1]][i - 1]);

        //维护严格次大边
        if(Max[pos][i - 1] == Max[fa[pos][i - 1]][i - 1])
            SecMax[pos][i] = max(SecMax[pos][i - 1], SecMax[fa[pos][i - 1]][i - 1]);
        else
            SecMax[pos][i] = max(
                    min(Max[pos][i - 1], Max[fa[pos][i - 1]][i - 1]),
                    max(SecMax[pos][i - 1], SecMax[fa[pos][i - 1]][i - 1])
                    );
        //倍增的精髓
    }
    for(int i = head[pos]; i; i = graph[i].nxt) {
        int v = graph[i].to;
        if(v==last)continue;
        Max[v][0] = graph[i].w;
        DFS(v, pos, depth + 1);
    }//DFS基操
}
//倍增预处理

int LCA(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);
    //不妨假设 x 大于等于 y （在dep的意义上）
    int k = dep[x] - dep[y];
    for(int i = 0; i <=  19; ++i)
        if(k >> i & 1)x=fa[x][i];
    //对深度差二进制拆分，调到同一高度
    if(x==y)return x;
    //必须特判
    for(int i = 19; i >= 0; i --)
        if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

void solve(int pos, int a, int w) {
    //a是pos的祖先
    int Max1 = 0, Max2 = 0;
    while(dep[pos]!=dep[a]){
        //二进制拆分向上移动
        int lg=(int)log(dep[pos]-dep[a]);
        Max2 = max (Max2, SecMax[pos][lg]);
        if (Max[pos][lg] > Max1) {
            Max2 = max(Max2, Max1);
            Max1 = Max[pos][lg];
        }
        //查询M1和M2
        pos=fa[pos][lg];
    }
    if(Max1 == w) delta = min(delta, w - Max2); //如果最大边等于非树边
    else delta = min(delta, w - Max1);
}

signed main() {
    n = read(); m = read();

    for(int i = 1; i <= n; ++i)par[i] = i;
    //init union-find set

    for(int i = 1; i <= m; ++i)edge[i].u = read(), edge[i].v = read(), edge[i].w = read();
    MST();

    DFS(1, 0, 1);
    //倍增预处理

    for(int i = 1; i <= m; i ++) {
        if(!inq[i]) {
            //枚举非树边
            int u = edge[i].u, v = edge[i].v;
            int a = LCA(u, v);
            //利用LCA拆环成链
            solve(u, a, edge[i].w);
            solve(v, a, edge[i].w);
            //更新delta
        }
    }
    printf("%ld", sum + delta);
    return 0;
}
