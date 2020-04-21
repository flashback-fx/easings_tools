#!/bin/sh

ORIGHDR="easings_original.h"  #Original header file
MODFHDR="easings_new.h" #Modified header file
T1OUT="result_orig.txt"  #Output file for the results of the test using the original header
T2OUT="result_newh.txt"  #Output file for the results of the test using the modified header
DIFFF="diff_out.txt"  #Output file for the diff operation
NDPARAMS=""  #Test program numerical options

cp -v $ORIGHDR easings.h
make
./easings_results --out=$T1OUT $NDPARAMS

cp -v $MODFHDR easings.h
make
./easings_results --out=$T2OUT $NDPARAMS
diff -s -y -t $T1OUT $T2OUT > $DIFFF
