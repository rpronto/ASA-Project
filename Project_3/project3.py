# Project3 - al014 , ist1106819 , ist1105672
from pulp import *

t, p, max = input().split()

t = int(t)
p = int(p)
max = int(max)

toys = []
lucro_t = {}
capacidade_t = {}
toys_p = {}

for n in range(t):
    l, c = input().split()
    toys += [n]
    lucro_t[n] = int(l)
    capacidade_t[n] = int(c)
    toys_p[n] = []
    

packages = []
lucro_p = {}

for n in range(p):
    i, j, k, l = input().split()
    packages += [n]
    lucro_p[n] = int(l)
    toys_p[int(i)-1] += [n]
    toys_p[int(j)-1] += [n]
    toys_p[int(k)-1] += [n]

prob = LpProblem("toys", LpMaximize)

vars_t = LpVariable.dict("toys", toys, 0, max, LpInteger)
vars_p = LpVariable.dict("packages", packages, 0, max, LpInteger)

prob += (
    lpSum([vars_t[i] * lucro_t[i] for i in toys])
    + lpSum([vars_p[i] * lucro_p[i] for i in packages]),
    "objectivo"
)


prob += (  
    (lpSum([vars_t[i] for i in toys]) 
    + (lpSum(vars_p[n] for n in toys_p[i]) for i in toys)) <= max,
    "capacidade"
)

for i in range (t):
    prob += vars_t[i] <= capacidade_t[i]

for i in range (t):
    for p in toys_p[i]:
        prob += vars_t[i] + vars_p[p] <= capacidade_t[i]


prob.solve()

print(int(value(prob.objective)))
