#!/bin/bash


for file in sequence_data/length_data/*.txt; do
    unix2dos ${file} ${file}
done


