import operator as op
import functools
import time

def ncr(n, r):
    r = min(r, n-r)
    numer = functools.reduce(op.mul, range(n, n-r, -1), 1)
    denom = functools.reduce(op.mul, range(1, r+1), 1)
    return numer//denom

balls = int( input( "Enter number of balls: " ) )
length = int( input( "Enter length of lattice: ") )
bonds = int( input( "Enter number of bonds: " ) )

file = open("bounds.txt", "w")
file.write(str(balls) + "\n" + str(length) + "\n" + str(bonds) + "\n")

prediction = ncr( balls - 1, bonds ) * ncr( length - balls + 1, balls - bonds )

if( balls > length or bonds > balls):
    prediction = 0

if( (balls - 1 < bonds) or (length - balls + 1 < balls - bonds) ):
    prediction = 0

print("The predicted number of sequences is " + str(prediction))

time.sleep(0.5)
