#!/bin/bash
#NOTE: it has to be bash, sh won't do

ORIGHDR="easings_original.h"  #Original header file
MODFHDR="easings_new.h"  #Modified header file
T1OUT="test_orig.txt"  #Output file for the results of the test using the original header
T2OUT="test_newh.txt"  #Output file for the results of the test using the modified header
NDPARAMS=""  #Test program numerical options
TESTITR=8  #Number of consecutive times the performance testing program is run

cp -v $ORIGHDR easings.h
make
iter=0
while [ $iter -lt $TESTITR ]
do
	./easings_perftest --out=$T1OUT $NDPARAMS
	((iter++))
done
cp -v $MODFHDR easings.h

make
iter=0
while [ $iter -lt $TESTITR ]
do
	./easings_perftest --out=$T2OUT $NDPARAMS
	((iter++))
done