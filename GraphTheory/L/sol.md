# L. PAFF 的演唱会

### 思路和解法：

我们要求每个节点，到达所有节点（包括自己）的最小花费，实际上，图中边是双向的，很容易想到转化多个源头到该点的最小花费。那么这个问题其实是一个多源多终止点的问题。



所以，这是一个有点技巧的最短路。



第一个技巧，这是一个多源最短路，添加一个超级源点使之变为单源最短路，这样就可以Dijkstra了hh。

第二个技巧，门票不同于路径，路径要算两次，门票只算一次，解决方案是门票除以2，这样新的价格可以计算两次。（注意要使用浮点数）



具体看代码，有注释

### 时间复杂度：

对于Dijsktra，采用邻接表和二叉堆，故时间复杂度 $O((V+E)logV)$，有些大哥喜欢写 $O(ElogV)$

### 空间复杂度：

由于有一个堆，其实我是不会分析的，55555

此外的复杂度是$O(V+E)$，V来自dis数组等，E来自存图。