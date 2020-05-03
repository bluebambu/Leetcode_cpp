import collections

dir = [[0,1],[0,-1],[1,0],[-1,0]]

def p(m):
    for i in m:
        print(i)


def answer(maze):
    if len(maze)==0 or len(maze[0])==0:
        return 0

    w = len(maze[0])
    h = len(maze)

    dist = [[500 for i in range(w)] for j in range(h)]

    q = collections.deque()
    n = 1
    q.append((w - 1, h - 1))
    visited = set()
    visited.add((w - 1, h - 1))
    while q:
        sz = len(q)
        while sz > 0:
            tmp = q.popleft()
            for d in dir:
                x = tmp[0] + d[0]
                y = tmp[1] + d[1]
                if x < 0 or x >= w or y < 0 or y >= h or (x, y) in visited:
                    continue
                if maze[y][x] == 1:
                    dist[y][x] = min(dist[y][x], n + 1)
                else:
                    visited.add((x, y))
                    q.append((x, y))
            sz -= 1
        n += 1

    p(dist)

    res = 500
    n = 1
    q.append((0, 0))
    visited.clear()
    visited.add((0, 0))
    while q:
        sz = len(q)
        while sz > 0:
            tmp = q.popleft()
            for d in dir:
                x = tmp[0] + d[0]
                y = tmp[1] + d[1]
                if x < 0 or x >= w or y < 0 or y >= h or (x, y) in visited:
                    continue
                if maze[y][x] == 1:
                    res = min(res, n + dist[y][x])
                elif x == w - 1 and y == h - 1:
                    res = min(res, n + 1)
                else:
                    visited.add((x, y))
                    q.append((x, y))
            sz -= 1
        n += 1

    return -1 if res == 500 else res

maze = [
    [0,1,0,0,0],
    [0,0,0,0,0],
    [0,0,0,0,0],
    [0,0,0,0,0],
    [0,0,0,1,1],
    [0,0,0,1,0]
]

print(answer(maze))
