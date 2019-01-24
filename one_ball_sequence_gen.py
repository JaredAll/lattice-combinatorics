import operator as op
import functools
import time

def ncr(n, r):
    r = min(r, n-r)
    numer = functools.reduce(op.mul, range(n, n-r, -1), 1)
    denom = functools.reduce(op.mul, range(1, r+1), 1)
    return numer//denom

bonds = 0
balls = int( input( "Enter number of balls: " ) )

for length in range( 1, 30 ):
    prediction = ncr( balls - 1, bonds ) * ncr( length - balls + 1, balls - bonds )

    print( prediction, " " )
