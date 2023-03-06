#!/bin/bash
if [ $# -lt 1 ]
then
	echo "Impossible"
	exit
fi
n=$1
shift 1
while [ $# -gt 0 ]
do
	cat $1 | while read -r line
	do
		for for_word in $line
		do
			echo $for_word
		done 
	done | sort | uniq -c | awk -v n=$n '($1>n){print}'
	shift 1
done
