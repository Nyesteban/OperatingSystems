#!/bin/bash
if [ $# -lt 2 ]
then
	echo "Impossible"
	exit
fi
n=$1
w=$2
shift 2
while [ $# -gt 0 ]
do
	count=0
	cat $1 | while read -r line
	do
		for for_word in $line
		do			
		if [ "$for_word" == "$w" ]
		then
			count=$(($count+1))
			break
		fi
		done
		if [ $count -eq $n ]
		then
			echo $line
			break
		fi	
	done
	shift 1
done	
