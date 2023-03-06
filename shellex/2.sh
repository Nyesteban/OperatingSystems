#!/bin/bash
if [ $# -lt 3 ]
then
	echo "Impossible"
	exit
fi

word=$1
m=$2
n=$3

shift 3

while [ $# -gt 0 ]
do
	count=0
	current=0
	cat $1 | while read -r line
	do
		current=$(($current + 1)) 
		if [ $current -eq $n ]
		then
			for for_word in $line
			do
				if [ "$for_word" == "$word" ]
				then
					count=$(( $count + 1 ))
				fi
			done
			if [ $count -ge $m ]
			then
				echo $1
			fi	
		continue
		fi	
	done	
	shift 1
done

