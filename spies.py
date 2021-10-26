# a simple parser for python. use get_number() and get_word() to read
def parser():
    while 1:
        data = list(input().split(' '))
        for number in data:
            if len(number) > 0:
                yield(number)

input_parser = parser()

def get_word():
    global input_parser
    return next(input_parser)

def get_number():
    data = get_word()
    try:
        return int(data)
    except ValueError:
        return float(data)

# numpy and scipy are available for use
import numpy
import scipy
from collections import defaultdict



# class Graph():
#     def __init__(self,vertices):
#         self.graph = defaultdict(list)
#         self.V = vertices

#     def addEdge(self,u,v):
#         self.graph[u].append(v)

#     def isCyclicUtil(self, v, visited, recStack):

#         # Mark current node as visited and
#         # adds to recursion stack
#         visited[v] = True
#         recStack[v] = True

#         # Recur for all neighbours
#         # if any neighbour is visited and in
#         # recStack then graph is cyclic
#         for neighbour in self.graph[v]:
#             if visited[neighbour] == False:
#                 if self.isCyclicUtil(neighbour, visited, recStack) == True:
#                     return True
#             elif recStack[neighbour] == True:
#                 return True

#         # The node needs to be poped from
#         # recursion stack before function ends
#         recStack[v] = False
#         return False

#     # Returns true if graph is cyclic else false
#     def isCyclic(self):
#         visited = [False] * (self.V + 1)
#         recStack = [False] * (self.V + 1)
#         for node in range(self.V):
#             if visited[node] == False:
#                 if self.isCyclicUtil(node,visited,recStack) == True:
#                     return True
#         return False


class Graph:

    def __init__(self,vertices):
        self.V= vertices #No. of vertices
        self.graph = defaultdict(list) # default dictionary to store graph

    # function to add an edge to graph
    def addEdge(self,u,v):
        self.graph[u].append(v)

    def replaceEdge(self, u, old, new):
        self.graph[u].remove(old)
        self.graph[u].append(new)

     # Use BFS to check path between s and d
    def isReachable(self, s, d):
        # Mark all the vertices as not visited
        visited =[False]*(self.V)

        # Create a queue for BFS
        queue=[]

        # Mark the source node as visited and enqueue it
        queue.append(s)
        visited[s] = True

        while queue:

            #Dequeue a vertex from queue
            n = queue.pop(0)

            # If this adjacent node is the destination node,
            # then return true
            if n == d:
                return True

            #  Else, continue to do BFS
            for i in self.graph[n]:
                if visited[i] == False:
                    queue.append(i)
                    visited[i] = True
        # If BFS is complete without visited d
        return False

def getDistance(v, goesTo):
    dist = 0
    while (goesTo[v] != -1):
        dist += 1
        v = goesTo[v]
    return dist


import numpy as np
T = get_number()
for _ in range(T):
    nr = get_number()
    nb = get_number()
    E = get_number()

    name2idx = {}
    idx2name = []
    id = 0
    for i in range(1, nr+1):
        key = "R" + str(i)
        name2idx[key] = id
        idx2name.append(key)
        id += 1

    for i in range(1, nb+1):
        key = "B" + str(i)
        name2idx[key] = id
        idx2name.append(key)
        id += 1


    g = Graph(nr+nb)

    goesTo = [-1 for _ in range(nr+nb)]

    for i in range(1, nr):
        inferior_name = "R" + str(i+1)
        senior_name = get_word()
        inferior_idx = name2idx[inferior_name]
        senior_idx = name2idx[senior_name]
        g.addEdge(inferior_idx, senior_idx)
        goesTo[inferior_idx] = senior_idx

    for i in range(1, nb):
        inferior_name = "B" + str(i+1)
        senior_name = get_word()
        inferior_idx = name2idx[inferior_name]
        senior_idx = name2idx[senior_name]
        g.addEdge(inferior_idx, senior_idx)
        goesTo[inferior_idx] = senior_idx




    for e in range(E):
        event = get_word()
        name_a = get_word()
        name_b = get_word()
        if event == "w":
            idx_start_R = name2idx[name_a]
            idx_start_B = name2idx[name_b]
            R1 = name2idx["R1"]
            B1 = name2idx["B1"]



            r2r_exists = g.isReachable(idx_start_R, R1)
            b2b_exists = g.isReachable(idx_start_B, B1)
            b2r_exists = g.isReachable(idx_start_B, R1)
            r2b_exists = g.isReachable(idx_start_R, B1)

            isNone = not (r2r_exists or b2b_exists or b2r_exists or r2b_exists)

            # if (aaa == 2):
            #     print(r2r_exists, b2b_exists, b2r_exists, r2b_exists)
            #     break
            # aaa += 1



            if (isNone):
                print("NONE")
            else:
                if r2r_exists:
                    r2r_dist = getDistance(idx_start_R, goesTo)
                    if b2b_exists:
                        b2b_dist = getDistance(idx_start_B, goesTo)
                        if r2r_dist < b2b_dist:
                            print("RED", r2r_dist)
                        elif r2r_dist > b2b_dist:
                            print("BLUE", b2b_dist)
                        else:
                            print("TIE", r2r_dist)
                    elif b2r_exists:
                        b2r_dist = getDistance(idx_start_B, goesTo)
                        print("RED", min(r2r_dist, b2r_dist))
                    else:
                        print("RED", r2r_dist)
                elif b2b_exists:
                    b2b_dist = getDistance(idx_start_B, goesTo)
                    if r2b_exists:
                        r2b_dist = getDistance(idx_start_R, goesTo)
                        print("BLUE", min(b2b_dist, r2b_dist))
                    else:
                        print("BLUE", b2b_dist)
                else:
                    if b2r_exists and r2b_exists:
                        b2r_dist = getDistance(idx_start_B, goesTo)
                        r2b_dist = getDistance(idx_Start_R, goesTo)
                        if b2r_dist < r2b_dist:
                            print("RED", b2r_dist)
                        elif b2r_dist > r2b_dist:
                            print("BLUE", b2r_dist)
                        else:
                            print("TIE", b2r_dist)
                    elif b2r_exists and (not r2b_exists):
                        b2r_dist = getDistance(idx_start_B, goesTo)
                        print("RED", b2r_dist)
                    elif (not b2r_exists) and r2b_exists:
                        r2b_dist = getDistance(idx_start_R, goesTo)
                        print("BLUE", r2b_dist)


        elif event == "c":
            idx_a = name2idx[name_a]
            idx_b = name2idx[name_b]
            u = idx_a
            old = goesTo[idx_a]
            new = idx_b
            goesTo[idx_a] = idx_b
            g.replaceEdge(u, old, new)
