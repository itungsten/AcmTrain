# B. Was yant gagis chs hymmnos mea

### 结论：

$$\sum\limits_{i=1}^{n}{\mu(gcd(i,n))gcd(i,n)}=\mu(n)$$

### 证明：

显然，虽然原来式子中的求和上下界是1和n，但是实际上， 被求和的每一项 $\mu(gcd(i,n))gcd(i,n)$ 都只与$gcd(i,n)$相关，即n与i的最大公因数。由于最大公因数必然是n的因子，我们可以改变求和方式，枚举n的因子，从而变换形式。

问题是，对于不同的 i ，可能有相同的 gcd(i,n)，也就是说同一个 d 很有可能被计算多次，那么这里如何计数呢？如官方题解所示，这里需要使用Eular函数。

我们知道Eular函数的定义是 $\sum\limits_{i=1}^{n}[gcd(i,n)=1]$，其中[]部分是艾弗森括号，在括号内的命题成立时为1，否则为0。而我们需要的结果为$\sum\limits_{i=1}^{n}[gcd(i,n)=d]$。此时向 d=1 转化，注意到在命题成立时，必然有 i和n 都被 d 整除，那么在**假定i被d整除的条件下**，可以转化为$\sum\limits_{i=1}^{n}[gcd(\frac{i}{d},\frac{n}{d})=1]$，但是显然这个条件存在一定问题，并不是所有i都被d整除，所以应该通过做下标的乘法变换转换为$\sum\limits_{i=1}^{\lfloor \frac{n}{d} \rfloor}[gcd(i,\frac{n}{d})=1]=\varphi(\frac{n}{d})$，此时的 i 相当于 前式中的 i/d，并且按照枚举方式，此时的i必然为整数，即前式中的i被d整除。

故题目所求转化为 $$\sum\limits_{d|n}d\mu(d)\varphi(\frac{n}{d})$$

vy说要令$g(d)=dμ(d)$，然后我就得到了一个g与φ的狄利克雷卷积，原问题化为$g*\varphi$。

然后因为狄利克雷卷积有一个很重要的结论$\varphi=\mu*id$，代入得$g*(\mu*id)$。

然后又因为狄利克雷卷积有交换律和结合律，得$(g*id)*\mu$

然后根据狄利克雷卷积，g和id 的定义 $g*id = \sum\limits_{d|n}{d\mu(d)\times\frac{n}{d}}=n\sum\limits_{d|n}{\mu(d)}=n\sum\limits_{d|n}{\mu(d)\times1}=n\times(\mu*I)$

然后又根据性质$g*id=n\times(\mu*I)=n\varepsilon(n) $

根据$\varepsilon$定义，$g*id*\mu=\sum\limits_{d|n}d\times\varepsilon(d)\mu(\frac{n}{d})=\mu(n)$（显然只有d=1时非0）

Q.E.D.

### 时间复杂度：

好像计算莫比乌斯函数网上有两种方法，一是单点计算，一个是线性筛，但是线性筛显然过不了，就套了单点计算的模板，其单次复杂度是$O(\sqrt{N}))$，故总体是$O(T\sqrt{N})$，然后就过了。

为什么这个板子的时间复杂度如此呢？因为我们有，对于任意合数，其较小的因子不超过其sqrt的结论，所以是根号算法。但是由于这个结论只对合数成立，所以质数需要特殊处理。具体请看代码。

### 空间复杂度：

$O(1)$