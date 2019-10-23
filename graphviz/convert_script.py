import networkx as nx
from networkx.drawing.nx_agraph import write_dot
import os
import sys

inf = sys.argv[1]
out = os.path.splitext(inf)[0] + '.dot'

g = nx.Graph()

for line in open(inf).readlines():
    adj = list(map(str, line.split()))

    vertex_from = adj[0]
    vertex_to = adj[1]

    g.add_edge(vertex_from, vertex_to)

write_dot(g, out)
