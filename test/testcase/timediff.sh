#!/bin/bash

#g++ new_way.cpp -pthread -o new_way_cpp
#./new_way_cpp

#new_cpp_time=$(<time.txt)

gcc new_way.c -pthread -o new_way_c
./new_way_c

new_c_time=$(<time.txt)

gcc old_way.c -pthread -o old_way_c
./old_way_c

old_c_time=$(<time.txt)

echo "This is new c time"
echo $new_c_time
echo "This is old c time"
echo $old_c_time


#g++ old_way.cpp -pthread -o old_way
#./old_way

#old_time=$(<time.txt)

#echo "This is new time\n"
#echo $new_time
#echo "This is old time\n"
#echo $old_time