#!/bin/bash

max=1000;
for ((i=1;i<=$max;i++))
do
  in_filepath="in$i.txt";
  out_filepath="out$i.txt";
  rm -f "${in_filepath}";
  rm -f "${out_filepath}";
done