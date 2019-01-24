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

bonds = int( input( "" ) )
balls = int( input( "" ) )
doubleOcc = int( input( "" ) )
length = int( input( "") )

file = open("two_ball_bounds_N_D.txt", "w")
file.write(str(bonds) + "\n" + str(balls) + "\n" + str(doubleOcc) +
           "\n" + str(length) + "\n" + "\n")
file.close()

'''
emptySites = length + doubleOcc - ( balls )

lengthFact = factorial( length )
redDoubleFact = factorial(balls - doubleOcc)
doubleFact = factorial(doubleOcc)
greenDoubleFact = factorial(balls - doubleOcc)
emptySitesFact = factorial( emptySites )

#if( ( (balls - doubleOcc) >= 0 ) and  (emptySites >= 0) ):
#   totalConfig = 10
    #int( lengthFact / ( doubleFact * redDoubleFact * greenDoubleFact * emptySitesFact ) )
#    file = open("two_ball_bounds_N_D.txt", "a")
#    file.write(str(totalConfig) + "\n")
#    file.close()
#else:
#    totalConfig = 0

#print( "\n" + "The total number of configurations disregarding bond number is " +
#       str( totalConfig ) )

#prediction = ncr( balls - 1, bonds ) * ncr( length - balls + 1, balls - bonds )

#if( balls > length or bonds > balls):
#    prediction = 0

#print("The predicted number of sequences is " + str(prediction))

#time.sleep(0.5)
'''
