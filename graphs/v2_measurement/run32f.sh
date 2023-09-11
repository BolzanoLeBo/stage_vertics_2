#!/bin/bash
proc=32f

python get_current_autom_dir.py $proc/bubble_sort/ param_$proc 20
python get_current_autom_dir.py $proc/dijkstra/ param_$proc 100
python get_current_autom_dir.py $proc/fft/ param_$proc 100
python get_current_autom_dir.py $proc/kalman/ param_$proc 100
python get_current_autom_dir.py $proc/mat_mul/ param_$proc 100
python get_current_autom_dir.py $proc/pointer_chase/ param_$proc 30
python get_current_autom_dir.py $proc/recursion/ param_$proc 50
python get_current_autom_dir.py $proc/RSA_dec/ param_$proc 100
python get_current_autom_dir.py $proc/RSA_enc/ param_$proc 100
python get_current_autom_dir.py $proc/sine/ param_$proc 50




