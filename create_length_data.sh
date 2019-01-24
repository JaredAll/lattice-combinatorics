#!/bin/bash

NUM_BONDS=10
NUM_BALLS=10
NUM_DOUBLE=5
LENGTH_LATTICE=15
for ((length = 1; length<=LENGTH_LATTICE; length++)); do
    echo "b n d l seq" > sequence_data/length_data/length_${length}.txt
    echo "Moving to the file:" length_${length}.txt
    for ((doubles = 0; doubles<=NUM_DOUBLE; doubles++)); do 
        for ((bonds = 0; bonds <= NUM_BONDS; bonds++)); do
            for ((balls = 1; balls<=NUM_BALLS; balls++)); do
                echo $bonds > two_ball_bounds_N_D.txt
                echo $balls >> two_ball_bounds_N_D.txt
                echo $doubles >> two_ball_bounds_N_D.txt
                echo $length >> two_ball_bounds_N_D.txt
                ./two_balls_N_D.sh < two_ball_bounds_N_D.txt >> \
                sequence_data/length_data/length_${length}.txt
            done
        done
    done
done
