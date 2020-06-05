#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f
const int N = 105;
//矩阵规模

int weight[N][N];
//匹配的权重
int Lx[N], Ly[N];
//可行顶标（就是每个顶点分配的一个值
bool visX[N], visY[N];
//每轮中，X部分和Y部分的节点是否被访问过
int match[N];
//Y部分节点匹配的X
int slack[N];
//用来优化计算最小delta
int n;

bool dfs(int x) {
    visX[x] = true;
    for (int y = 1; y <= n; ++y) {
        if (visY[y]) continue;
        int dis = Lx[x] + Ly[y] - weight[x][y];
        if (!dis) {
            //一条相等边，有可能被加入相等子图
            visY[y] = true;
            if (!match[y]|| dfs(match[y])) {
                //如果没有被匹配，就进行匹配
                //否则如果匹配了，但是可以更改匹配，仍然可以进行
                match[y] = x;
                return true;
            }
        } else {
            slack[y] = min(slack[y], dis);
            //维护slack数组，优化delta计算
        }
    }
    return false;
}
//匈牙利算法

int km(){
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            Lx[i] = max(Lx[i], weight[i][j]);
        }
    }
    //初始化X的可行顶标为与之相连的最大边的权重
    for (int i = 1; i <= n; ++i) {
        //为每个X找匹配
        fill(slack + 1, slack + 1 + n, INF);
        while (1) {
            //通过改变顶标，逐步扩大相等子图，最终达到能够经行匹配的情况
            memset(visX, 0, sizeof visX);
            memset(visY, 0, sizeof visY);
            //每一次匈牙利算法前清零
            if (dfs(i)) break;
            //如果找到匹配，终止
            //否则计算delta
            int delta = INF;
            for (int j = 1; j <= n; ++j)
                if (!visY[j]) delta = min(delta, slack[j]);
            //delta为每一个未被匹配的Y部点所需最小变化的最小值
            for (int j = 1; j <= n; ++j) {
                if (visX[j]) Lx[j] -= delta;
                if (visY[j])
                    Ly[j] += delta;
                else
                    slack[j] -= delta;
            }
            //更新顶标和slack
        }
    }
    int res = 0;
    for (int i = 1; i <= n; ++i) res += weight[match[i]][i];
    return res;
}

signed main() {
    cin>>n;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j)cin>>weight[i][j];
    }
    cout<<km();
    return 0;
}