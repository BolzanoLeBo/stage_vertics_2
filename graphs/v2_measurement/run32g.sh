#!/bin/bash
proc=32g

python get_current_autom_dir.py $proc/bubble_sort/ param_$proc 10 1500 0.002
python get_current_autom_dir.py $proc/dijkstra/ param_$proc 100 1500 0.002
python get_current_autom_dir.py $proc/fft/ param_$proc 100 1000 0.002
python get_current_autom_dir.py $proc/kalman/ param_$proc 100 1000 0.002
python get_current_autom_dir.py $proc/mat_mul/ param_$proc 100 1000 0.002
python get_current_autom_dir.py $proc/pointer_chase/ param_$proc 30 1000 0.002
python get_current_autom_dir.py $proc/recursion/ param_$proc 30 1000 0.002
python get_current_autom_dir.py $proc/RSA_dec/ param_$proc 100 1000 0.002
python get_current_autom_dir.py $proc/RSA_enc/ param_$proc 100 1000 0.002
python get_current_autom_dir.py $proc/sine/ param_$proc 20 1000 0.002




