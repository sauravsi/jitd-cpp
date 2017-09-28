#!/bin/bash
echo "Running test1"
./jitd_noread testscripts/costModel/test1 > output/costModel/result1
echo "Running test2"
./jitd_noread testscripts/costModel/test2 > output/costModel/result2
echo "Running test3"
./jitd_noread testscripts/costModel/test3 > output/costModel/result3
echo "Running test4"
./jitd_noread testscripts/costModel/test4 > output/costModel/result4
echo "Running test5"
./jitd_noread testscripts/costModel/test5 > output/costModel/result5