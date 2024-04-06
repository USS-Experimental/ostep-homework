**These program is use to measure TLB size.**

# Usage

## Bulid
`$ make`

## Run
`$ python3 run_tlb.py <pagelimit> <times>`  

The `pagelimit` should not be set bigger than 4096.  
The bigger `times` is set, the longer the measurement will take. Recommand smaller than 10000000.  
Program will generate result plot `result.png`.

## Clean
`make clean`  

Delete the execute file and result plot generated.