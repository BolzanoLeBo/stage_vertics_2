#!/bin/bash

python get_current_autom_dir.py bubble_sort param_12 2000 0.00185
python get_current_autom_dir.py bubble_sort_no_opt param_12 2000 0.00195
python get_current_autom_dir.py RSA_dec param_12
python get_current_autom_dir.py RSA_enc param_12 2000 0.0004
python get_current_autom_dir.py kalman param_12
python get_current_autom_dir.py dijkstra param_12
python get_current_autom_dir.py FFT param_12
python get_current_autom_dir.py mat_mul param_12 2000 0.0005
python get_current_autom_dir.py pointer_chase param_12 2000 0.0005
python get_current_autom_dir.py recursif param_12 2000 0.0005
python get_current_autom_dir.py sine param_12



