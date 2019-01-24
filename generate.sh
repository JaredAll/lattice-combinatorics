#!/bin/bash

for r in 'jot 10'
do
    for g in 'jot 10'
    do
        for d in 'jot 10'
        do
            for l in 'jot 10'
            do
                red = r
                red >> two_ball_data.txt
                green = g
                green >> two_ball_data.txt
                double = d
                double >> two_ball_data.txt
                length = l
                length >> two_ball_data.txt

            done
        done
    done
done
