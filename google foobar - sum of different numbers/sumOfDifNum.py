一个数， 分成互不相同的几个数的合， 有多少种分法？ 

import math

def p(array):
    for i in array:
        print i


def answer(n):
    res=0
    l = int(math.sqrt(2*n))

    dp = [[0 for i in xrange(l+1)] for j in xrange(n+1)]

    i=1
    while i <n+1:
        dp[i][1]=1
        i+=1

    for j in range(2,l+1):
        for i in range(1, n+1):
            # dp[i][j]
            if j>i/2+1:
                continue
            tmp=0
            for k in range(1, i/j+1):
                # (i,j) = sum(k: 1~i/j)(i-k*j, j-1)
                if i-k*j <0:
                    continue
                if j-1<0:
                    continue
                tmp += dp[i-k*j][j-1]
            dp[i][j]=tmp

    for i in range(2, l+1):
        res += dp[n][i]
    return res

print answer(10)