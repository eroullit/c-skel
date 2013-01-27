#!/usr/bin/env python
import sys
import yaml

def fib(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fib(n-1) + fib(n-2)

print yaml.dump(map(fib, range(int(sys.argv[1])+1)), default_flow_style=False, explicit_start=True)
