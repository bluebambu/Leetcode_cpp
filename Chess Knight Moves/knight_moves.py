# To help yourself get to and from your bunk every day, write a function called answer(src, dest) which takes
# in two parameters: the source square, on which you start, and the destination square, which is where you need
# to land to solve the puzzle. The function should return an integer representing the smallest number of moves it
# will take for you to travel from the source square to the destination square using a chess knight's moves (that
# is, two squares in any direction immediately followed by one square perpendicular to that direction, or vice versa,
#  in an "L" shape). Both the source and destination squares will be an integer between 0 and 63, inclusive, and are
#  numbered like the example chessboard below:

#  ------------------------- | 0| 1| 2| 3| 4| 5| 6| 7|
# ------------------------- | 8| 9|10|11|12|13|14|15|
#  ------------------------- |16|17|18|19|20|21|22|23|
#  ------------------------- |24|25|26|27|28|29|30|31|
#  ------------------------- |32|33|34|35|36|37|38|39|
#  ------------------------- |40|41|42|43|44|45|46|47|
# ------------------------- |48|49|50|51|52|53|54|55|
#  ------------------------- |56|57|58|59|60|61|62|63|

# Test cases == == == == ==
# Inputs:
# (int)# src = 19
# (int)# dest = 36
# Output:
# (int) 1
#
# Inputs:
# (int)# src = 0
# (int)# dest = 1
# Output:
# (int) 3
import copy
dir = [(2,1),(2,-1),(-2,1),(-2,-1),(1,2),(1,-2),(-1,2),(-1,-2)]

def isout(n, d):
    x=n%8 + d[0]
    y=n/8 + d[1]
    if x<0 or x>7 or y<0 or y>7:
        return True
    else:
        return False

def answer(src, dest):
    # your code here
    if src==dest:
        return 0

    f = set()
    b = set()
    map = set(range(64))
    f.add(src)
    b.add(dest)
    map.remove(src)
    map.remove(dest)
    step=0

    while len(map)!=0 :
        if len(f) > len(b):
            f,b=b,f

        step+=1

        next = set()
        for n in f:
            for d in dir:
                if isout(n,d):
                    continue
                new = n+8*d[1]+d[0]
                if new in b:
                    return step
                if new not in map:
                    continue
                map.remove(new)
                next.add(new)
        f=copy.deepcopy(next)
    return 0

print(answer(0, 1))


