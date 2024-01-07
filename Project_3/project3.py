# Project3 - al014 , ist1106819 , ist1105672
from pulp import *

t, p, max = map(int, sys.stdin.readline().split())

lucro_t = {}
capacidade_t = {}
toys_p = {}
vars_t = {}

prob = LpProblem("MaxProfitToys", LpMaximize)

for n in range(t):
    l, c = map(int, sys.stdin.readline().split())
    lucro_t[n] = l
    capacidade_t[n] = c
    toys_p[n] = []
    vars_t[n]= LpVariable("toys_{}".format(n), 0, max, LpInteger)

lucro_p = {}
vars_p = {}

for n in range(p):
    i, j, k, l = map(int, sys.stdin.readline().split())
    lucro_p[n] = l
    toys_p[i-1] += [n]
    toys_p[j-1] += [n]
    toys_p[k-1] += [n]
    vars_p[n] = LpVariable("packages_{}".format(n), 0, max, LpInteger)


prob += (
    lpSum([vars_t[i] * lucro_t[i] for i in range(t)])
    + lpSum([vars_p[i] * lucro_p[i] for i in range(p)])
)


prob += (  
    (lpSum([vars_t[i] for i in range(t)]) 
    + 3*lpSum([vars_p[n] for n in range(p)])) <= max
)

for i in range(t):
    prob += vars_t[i] + lpSum(vars_p[p] for p in toys_p[i]) <= capacidade_t[i]


prob.solve(PULP_CBC_CMD(msg=0, mip=True, timeLimit=0.01, gapRel=0.01))

print(int(value(prob.objective)))