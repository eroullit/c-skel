#!/usr/bin/env python
import sys
import math
import yaml

def fib(n):
	return int(((1+math.sqrt(5))**n-(1-math.sqrt(5))**n)/(2**n*math.sqrt(5)))

print yaml.dump(map(fib, range(int(sys.argv[1])+1)), default_flow_style=False, explicit_start=True)
