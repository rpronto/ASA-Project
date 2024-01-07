# Project3 - al014 , ist1106819 , ist1105672
from pulp import *

t, p, max = map(int, sys.stdin.readline().split())

profit_t = {}
capacity_t = {}
toys_p = {}

for n in range(t):
    l, c = map(int, sys.stdin.readline().split())
    profit_t[n] = l
    capacity_t[n] = c
    toys_p[n] = []
    
profit_p = {}

for n in range(p):
    i, j, k, l = map(int, sys.stdin.readline().split())
    profit_p[n] = l
    toys_p[i-1] += [n]
    toys_p[j-1] += [n]
    toys_p[k-1] += [n]


prob = LpProblem("MaxProfitToys", LpMaximize)

vars_t = LpVariable.dict("toys", list(range(t)), 0, max, LpInteger)
vars_p = LpVariable.dict("packages", list(range(p)), 0, max, LpInteger)

prob += (
    lpSum([vars_t[i] * profit_t[i] for i in range(t)])
    + lpSum([vars_p[i] * profit_p[i] for i in range(p)])
)

prob += (  
    (lpSum([vars_t[i] for i in range(t)]) 
    + 3*lpSum([vars_p[n] for n in range(p)])) <= max
)

for i in range(t):
    prob += vars_t[i] + lpSum(vars_p[p] for p in toys_p[i]) <= capacity_t[i]

prob.solve(PULP_CBC_CMD(msg=0, timeLimit=0.01))

print(int(value(prob.objective)))