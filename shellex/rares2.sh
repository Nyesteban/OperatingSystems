#!/bin/bash
if [ $# -lt 1 ]
then
	echo "Impossible"
	exit
fi
total=0
for file in $(find $1 -name "*.c" -type f)
do
	if [ $(wc $file | awk '{print $1}') -gt 500 ]
	then
		echo $file
		total=$(($total+1))
	fi
	if [ $total -gt 1 ]
	then
		exit
	fi
done
