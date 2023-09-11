#!/bin/bash

python create_tab.py data_CCM-code_CCM energy
python create_tab.py data_CCM-code_CCM runtime
python create_tab.py data_CCM-code_CCM intensity

python create_tab.py data_CCM-code_FLASH energy
python create_tab.py data_CCM-code_FLASH runtime
python create_tab.py data_CCM-code_CCM intensity

python create_tab.py data_RAM-code_CCM energy
python create_tab.py data_RAM-code_CCM runtime
python create_tab.py data_CCM-code_CCM intensity

python create_tab.py data_RAM-code_FLASH energy
python create_tab.py data_RAM-code_FLASH runtime
python create_tab.py data_RAM-code_FLASH intensity

python create_tab.py ro_CCM-code_CCM energy
python create_tab.py ro_CCM-code_CCM runtime


python create_tab.py ro_CCM-code_FLASH energy
python create_tab.py ro_CCM-code_FLASH runtime


python create_tab.py ro_CCM-code_CCM energy
python create_tab.py ro_CCM-code_CCM runtime


python create_tab.py ro_RAM-code_FLASH energy
python create_tab.py ro_RAM-code_FLASH runtime


python create_tab.py ro_RAM-code_CCM energy
python create_tab.py ro_RAM-code_CCM runtime


python create_tab.py ro_FLASH-code_FLASH energy
python create_tab.py ro_FLASH-code_FLASH runtime


python create_tab.py ro_FLASH-code_CCM energy
python create_tab.py ro_FLASH-code_CCM runtime
