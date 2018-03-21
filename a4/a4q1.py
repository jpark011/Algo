import sys
from Queue import *

class Graph():
    def __init__(self, n, m):
        self.m = m
        self.n = n
        self.nodes = [[] for i in range(n)]

    def addEdge(self, u, v):
        # init edges
        self.nodes[u].append(v)

    # return reversed itself
    # no mutation
    # O(m+n)
    def getReverse(self):
        ret = Graph(self.n, self.m)

        for v, neighbors in enumerate(self.nodes):
            for u in neighbors:
                # add reversed arrow
                ret.addEdge(u, v)

        return ret

    # given a pointer to stack
    # return stack with filled values
    def DFS(self, v, stack, visited):
        visited[v] = True

        for u in self.nodes[v]:
            if visited[u] == False:
                self.DFS(u, stack, visited)
        stack.append(v)

    # returns a stack of node number
    # where the top node is the first visited
    # O(m+n)
    def runDFS(self):
        visited = [False] * self.n
        ret = []

        for v, neighbors in enumerate(self.nodes):
            if visited[v] == False:
                self.DFS(v, ret, visited)
        return ret

    # mutate visited with source visiting in BFS method
    # returns # of nodes visited
    def BFS(self, source, visited):
        ret = 1
        frontier = Queue()

        frontier.put(source)
        visited[source] = True

        while not frontier.empty():
            cur = frontier.get()
            for nxt in self.nodes[cur]:
                if visited[nxt] == False:
                    frontier.put(nxt)
                    visited[nxt] = True
                    ret += 1
        return ret

    # return a list integer values
    # where each value = size of SCC
    # O(m+n)
    def runBFS(self, stack):
        ret = []
        visited = [False] * self.n

        while stack:
            source = stack.pop()
            if visited[source] == False:
                size = self.BFS(source, visited)
                ret.append(size)

        return ret



def kosaraju(graph):
    # O(m+n)
    reversed = graph.getReverse()

    # O(m+n)
    stack = reversed.runDFS()

    # O(m+n)
    return graph.runBFS(stack)


HOW_MANY = 5

#__main__
# get std inputs
# and call Kosaraju
def main(argv):
    # file = open(argv[1])

    n = int(raw_input())
    m = int(raw_input())
    g = Graph(n, m)

    for i in range(m):
        # just for convinience
        # need to +1 when print out
        v, u = [int(i)-1 for i in raw_input().split()]
        g.addEdge(v, u)

    # file.close()

    # python recursion limit
    sys.setrecursionlimit(max(1000, n+5))
    res = kosaraju(g)

    top_five = []
    for i in range(HOW_MANY):
        max_sofar = 0 #S-inf
        for ele in res:
            if max_sofar < ele:
                max_sofar = ele
        top_five.append(max_sofar)
        if max_sofar != 0:
            res.remove(max_sofar)

    for i in range(HOW_MANY):
        if i < len(top_five):
            print(top_five[i]),
        else:
            print(0),
        print("\t"),
    print('')   # newline... wierd

if __name__ == '__main__':
  main(sys.argv)
