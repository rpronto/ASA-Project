# Project2 - al014 , ist1106819 , ist1105672
from pulp import *

t, p, max = input().split()

t = int(t)
p = int(p)
max = int(max)

toys = []

for n in range(t):
    l, c = input().split()
    toys += [[int(l),int(c)]]

packages = []
for n in range(p):
    i, j, k, l = input().split()
    packages += [[int(i),int(j),int(k),int(l)]]

prob = LpProblem("ToysProblem", LpMaximize)

li = LpVariable("li", 0, None, LpInteger)
ci = LpVariable("ci", 0, None, LpInteger)
pi = LpVariable("pi", 0, None, LpInteger)

obj = 0

for i in range (t):
    obj += li * toys[i][0]

for i in range(p):
    obj += pi * packages[i][3]

prob += obj

rest = 0

for i in range (t):
    rest += ci * toys[i][1]

for i in range (p - 1):
    rest += (((ci * toys[packages[i][0] - 1][1]) + (ci * toys[packages[i][1] - 1][1]) + (ci * toys[packages[i][2] - 1][1])) * pi)

prob += rest <= max

prob.solve()

