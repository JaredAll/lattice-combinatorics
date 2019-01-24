import operator as op
import functools
import time

def ncr(n, r):
    r = min(r, n-r)
    numer = functools.reduce(op.mul, range(n, n-r, -1), 1)
    denom = functools.reduce(op.mul, range(1, r+1), 1)
    return numer//denom

def factorial(n):
    if n < 0:
        return
    if n == 0:
        return 1
    else:
        return n * factorial(n-1)

redBalls = int( input( "Enter number of red balls: " ) )
greenBalls = int( input( "Enter number of green balls: " ) )
doubleOcc = int( input( "Enter number of doubly occupied positions: " ) )
length = int( input( "Enter length of lattice: ") )
#bonds = int( input( "Enter number of bonds: " ) )

file = open("two_ball_bounds.txt", "w")
file.write(str(redBalls) + "\n" + str(greenBalls) + "\n" + str(doubleOcc) +
           "\n" + str(length) + "\n" + "\n")
file.close()

emptySites = length + doubleOcc - ( redBalls + greenBalls )

lengthFact = factorial( length )
redDoubleFact = factorial(redBalls - doubleOcc)
doubleFact = factorial(doubleOcc)
greenDoubleFact = factorial(greenBalls - doubleOcc)
emptySitesFact = factorial( emptySites )

if( ( (redBalls - doubleOcc) >= 0 ) and ( (greenBalls - doubleOcc) >= 0 ) and
    (emptySites >= 0) ):
    totalConfig = int( lengthFact / ( doubleFact * redDoubleFact * greenDoubleFact * emptySitesFact ) )
    file = open("two_ball_bounds.txt", "a")
    file.write(str(totalConfig) + "\n")
    file.close()
else:
    totalConfig = 0

print( "\n" + "The total number of configurations disregarding bond number is " +
       str( totalConfig ) )

#prediction = ncr( balls - 1, bonds ) * ncr( length - balls + 1, balls - bonds )

#if( balls > length or bonds > balls):
#    prediction = 0

#print("The predicted number of sequences is " + str(prediction))

time.sleep(0.5)
