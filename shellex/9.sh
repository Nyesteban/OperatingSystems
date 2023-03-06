#!/bin/bash
while [ $# -gt 0 ]
do
	for for_word in $(cat $1)		
	do
		echo $for_word | grep -E "^[0-9]*[02468]$"
	done | sort | uniq -c | sort -n
	shift 1
done
