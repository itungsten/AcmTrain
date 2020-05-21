#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
const int K=1e6+5;
const int M=1e6+5;
int par[N],val[N];
//par是parent，val是带权的value
int n,k,m,ans[M];
bool del[K];
//记录一个观测数据是否已被删除
struct Opt{
    char opt;
    int x;
    int y;
    //操作 option x y
} opts[M];
struct Term{
    int rel;
    int x;
    int y;
    //观测记录 relationship x y
} term[K];
inline int Mod(int x){
    //用来处理元素克制关系
    return (x%3+3)%3;
}
void init(){
    cin>>n>>k>>m;
    for(int i=1;i<=n;++i){
        par[i]=i;
    }
}
int find(int x){
    if(x==par[x])return x;
    int t=par[x];
    //记录以前的父亲
    par[x]=find(t);
    val[x]=Mod(val[x]+val[t]);
    //保持当前节点的权值相对以前的父亲不变
    return par[x];
}
void uni(int x,int y,int s){
    int px=find(x),py=find(y);
    if(px==py)return;
	par[px]=py;
    val[px]=Mod(-val[x]+val[y]+s);
    //可以画矢量图看出这个关系
    //这是为了保证相对关系的相容
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

    init();
    for(int i=1;i<=k;++i){
        cin>>term[i].rel>>term[i].x>>term[i].y;
        --term[i].rel;
        //一个小的表示细节，和逻辑关系不大
    }
    string opt;
    int tot=0,x,y;
    //因为有一些操作会被忽略，那么需要一个tot记录总的有效操作数
    for(int i=1;i<=m;++i){
        cin>>opt;
        if(opt[0]=='d'){
            cin>>x;
            if(del[x]==1)continue;
            //忽略
            del[x]=1;
        }
        if(opt[0]=='q'){
            cin>>x>>y; 
        }
        opts[++tot].opt=opt[0];
        opts[tot].x=x;
        opts[tot].y=y;
    }
    for(int i=1;i<=k;++i){
        if(del[i]==0){
            uni(term[i].x,term[i].y,term[i].rel);
            //从未被删除的，执行并操作
        }
    }
    int cnt=0;
    for(int i=tot;i>=1;--i){
        //倒序
        if(opts[i].opt=='d'){
            int idx=opts[i].x;
            uni(term[idx].x,term[idx].y,term[idx].rel);
        }
        else{
            //ask
            int x=opts[i].x,y=opts[i].y,px=find(x),py=find(y);
            if(px!=py){
                ans[++cnt]=3;
                //关系未知
            }
            else{
                ans[++cnt]=Mod(val[x]-val[y]);
            }
        }
    }
    for(int i=cnt;i>=1;--i){
        //注意倒着来
        cout<<ans[i]<<endl;
    }
}
