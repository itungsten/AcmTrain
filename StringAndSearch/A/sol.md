# A. 第一章：小试牛刀

### 思路和解法：

(~~思路在题目里写了，解法在出题人题解里写了)~~

正如题目所说，这是一个标准的单串匹配问题，使用kmp算法即可。

这里大致写一下kmp算法吧。



kmp算法最大的特点在于，对于文本的指针不会回移（这为kmp自动机埋下了伏笔~），我们需要的只是移动模式串上的指针（对于自动机就是转移状态~）。

kmp有一个重要的数据结构支持，就是前缀函数，kmp算法是线性算法，那么就需要线性地求解前缀函数。

前缀函数定义为从字符串首到该位置的子串中，最长的真相同前缀和后缀长度。

为什么要用前后缀呢？这是为了可以通过把模式串的前缀部分移动到后缀部分以加速。

那么怎么求前缀函数呢？不太好用文字描述。上图吧！

![1](C:\Users\tungsten\Documents\AcmTrain\StringAndSearch\A\1.png)

![2](C:\Users\tungsten\Documents\AcmTrain\StringAndSearch\A\2.png)

![3](C:\Users\tungsten\Documents\AcmTrain\StringAndSearch\A\3.png)

![4](C:\Users\tungsten\Documents\AcmTrain\StringAndSearch\A\4.png)

就这样在不相等时逐渐往前跳，直到相等，或者到头。daze

具体看代码，有注释

### 时间复杂度：

$O(M+N)$

### 空间复杂度：

$O(M + N)$

要拼接嘛