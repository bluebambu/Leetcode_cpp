#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

/*

问题描述：n个人（编号0~(n-1))，从0开始报数，报到(m-1)的退出，剩下的人继续从0开始报数。求胜利者的编号。

我们知道第一个人(编号一定是m%n-1) 出列之后，剩下的n-1个人组成了一个新的约瑟夫环（以编号为k=m%n的人开始）:
  k  k+1  k+2  ... n-2, n-1, 0, 1, 2, ... k-2
并且从k开始报0。


现在我们把他们的编号做一下转换：
k     --> 0
k+1   --> 1
k+2   --> 2
...
...
k-2   --> n-2
k-1   --> n-1

变换后就完完全全成为了(n-1)个人报数的子问题，假如我们知道这个子问题的解：例如x是最终的胜利者，那么根据上面这个表把这个x变回去不刚好就是n个人情况的解吗？！！
变回去的公式很简单，相信大家都可以推出来：x'=(x+k)%n

如何知道(n-1)个人报数的问题的解？对，只要知道(n-2)个人的解就行了。(n-2)个人的解呢？当然是先求(n-3)的情况 ---- 这显然就是一个倒推问题！好了，思路出来了，下面写递推公式：

令f[i]表示i个人玩游戏报m退出最后胜利者的编号，最后的结果自然是f[n]

递推公式
f[1]=0;
f[i]=(f[i-1]+m)%i;  (i>1)

有了这个公式，我们要做的就是从1-n顺序算出f[i]的数值，最后结果是f[n]。因为实际生活中编号总是从1开始，我们输出f[n]+1

由于是逐级递推，不需要保存每个f[i]，程序也是异常简单：

#include <stdio.h>
int main()
{
  int n, m, i, s=0;
  printf ("N M = "); scanf("%d%d", &n, &m);
  for (i=2; i<=n; i++) s=(s+m)%i;
  printf ("The winner is %d\n", s+1);
}

这个算法的时间复杂度为O(n)，相对于模拟算法已经有了很大的提高。算n，m等于一百万，一千万的情况不是问题了。可见，适当地运用数学策略，不仅可以让编程变得简单，而且往往会成倍地提高算法执行效率。

*/


int f(int n, int k){
    if(n==1) return 1;
    return (f(n-1,k)+k-1)%n +1 ;
}


int main()
{
	cout<<f(7,3);
}
