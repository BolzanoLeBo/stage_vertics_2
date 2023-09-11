#!/bin/bash

    for e in energy runtime
    do
        python create_tab.py NORMAL $e
        python create_tab.py CODE_CCM $e
        python create_tab.py CODE_CCM-CACHE_OFF $e
        python create_tab.py CACHE_OFF-PRE_OFF $e
        python create_tab.py CACHE_ON-PRE_ON $e
        python create_tab.py CACHE_OFF-PRE_ON $e
    done

for n in ro_RAM ro_CCM ro_FLASH
do
    for e in energy runtime
    do
        python create_tab.py $n-NORMAL $e
        python create_tab.py $n-CODE_CCM $e
        python create_tab.py $n-CODE_CCM-CACHE_OFF $e
        python create_tab.py $n-CACHE_OFF-PRE_OFF $e
        python create_tab.py $n-CACHE_ON-PRE_ON $e
        python create_tab.py $n-CACHE_OFF-PRE_ON $e
    done
done