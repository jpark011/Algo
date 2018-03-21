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

        for neighbors in (self.nodes):
            for u, v in enumerate(neighbors):
                # add reversed arrow
                ret.addEdge(v, u)

        return ret

    # given a pointer to stack
    # return stack with filled values
    def runDFS_Helper(self, v, stack, visited):
        visited[v] = True

        for u in self.nodes[v]:
            if visited[u] == False:
                runDFS_Helper(u, stack, visited)
        stack.append(v)

    # returns a stack of node number
    # where the top node is the first visited
    # O(m+n)
    def runDFS(self):
        visited = [False] * self.n
        ret = []

        for v, neighbors in enumerate(self.nodes):
            if visited[v] == False:
                self.runDFS_Helper(v, ret, visited)

        return ret

    # mutate visited with source visiting in BFS method
    # returns # of nodes visited
    def runBFS_Helper(self, source, visited):
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
                size = self.runBFS_Helper(source, visited)
                ret.append(size)

        return ret



def kosaraju(graph):
    # O(m+n)
    reversed = graph.getReverse()

    # O(m+n)
    stack = reversed.runDFS()

    # O(m+n)
    return graph.runBFS(stack)



test_edges = [
    (1, 2),
    (1, 3),
    (2, 3),
    (2, 5),
    (3, 1),
    (3, 4),
    (4, 5),
    (4, 6),
    (5, 4)
]

HOW_MANY = 5

#__main__
# get std inputs
# and call Kosaraju
def main(argv):
    # n = int(input("Number of nodes: "))
    # m = int(input("Number of edges: "))
    # g = Graph(n, m)
    #
    # for i in range(m):
    #     # just for convinience
    #     # need to +1 when print out
    #     v, u = [int(i)-1 for i in raw_input("Enter edge {}: ".format(i+1)).split()]
    #     g.addEdge(v, u)

    ###### TESTING ######
    n = 6
    m = 9
    g = Graph(n, m)

    for edge in test_edges:
        g.addEdge(edge[0]-1, edge[1]-1)

    res = kosaraju(g)

    # biggest first
    res.sort(reverse=True)

    for i in range(HOW_MANY):
        if i < len(res):
            print(res[i]),
        else:
            print(0),

        if i < HOW_MANY-1:
             print("\t"),

if __name__ == '__main__':
  main(sys.argv)
