#!/bin/bash

for i in `seq 1 5`
do
    ./temp/build-release/demo_coarse_grained 5 50 500000
    ./temp/build-release/demo_striped 5 50 500000
    ./temp/build-release/demo_refinable 5 50 500000
done