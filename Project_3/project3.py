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
