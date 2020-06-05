#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int in[N],out[N];
int fa[N];
int n;
bool vis[N];
inline int read(){
    char c=getchar();int x=0;
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+c-48,c=getchar();
    return x;
}
int find(int x){
    if(x==fa[x])return x;
    return fa[x]=find(fa[x]);
}
void uni(int x,int y){
    fa[find(x)]=find(y);
}
bool isConnect(){
    int beg=-1;
    for(int i=1;i<=100;++i){
        if(vis[i]){
            if(beg==-1){
                beg=find(i);
                continue;
            }
            if(beg!=find(i))return false;
        }
    }
    return true;
}
inline void Exit(){
    printf("%d",-1);
    exit(0);
}
signed main(){
    n=read();
    //读入规模
    if(n==1){
        printf("%d",read()*read());
        return 0;
    }
    int l,r;
    for(int i=1;i<=100;++i)fa[i]=i;
    for(int i=1;i<=n;++i){
        //初始化并查集
        l=read();r=read();
        //读入矩阵
        ++out[l];
        ++in[r];
        uni(l,r);
        vis[l]=vis[r]=1;
    }
    if(!isConnect())Exit();
    int best=-1;
    bool flag=1;
    for(int i=1;i<=100;++i){
        if(vis[i]){
            if(in[i]==out[i]){
                best=max(best,i);
            }
            else{
                flag=0;
                break;
            }
        }
    }
    if(flag){
        printf("%d",best*best);
        return 0;
    }

    int ltemp=-1,rtemp=-1;
    for(int i=1;i<=100;++i){
        if(vis[i]){
            if(in[i]==out[i])continue;
            if(in[i]-out[i]==1){
                if(ltemp==-1)ltemp=i;
                else Exit();
                continue;
            }
            if(out[i]-in[i]==1){
                if(rtemp==-1)rtemp=i;
                else Exit();
                continue;
            }
            Exit();
        }
    }
    if(ltemp!=-1&&rtemp!=-1){
        printf("%d",ltemp*rtemp);
        return 0;
    }
    Exit();
}
