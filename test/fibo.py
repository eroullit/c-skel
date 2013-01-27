#!/usr/bin/env python

def fib(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fib(n-1) + fib(n-2)

def fib_yaml(n=10):
    print "---"
    for i in range(n):
    	    print "  -", fib(i)
