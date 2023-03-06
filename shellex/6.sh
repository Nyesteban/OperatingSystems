#!/bin/bash
if [ $# -lt 1 ]
then
	echo "Impossible"
	exit
fi
f1=$1
shift 1
while [ $# -gt 0 ]
do
	if cat /etc/passwd | awk -F: '{print $1}' | grep -q $1	       	
	then
		homedir=$(cat /etc/passwd | awk -F: '{print $1":"$6}' | grep -E "^$1" | awk -F: '{print $2}')
		if find $homedir > /dev/null 2> /dev/null
		then
			cat $f1 | while read -r line
			do
				for for_word in $line
				do
					find $homedir | grep -E "^($for_word)$"
				done	
			done
		else
			echo "Not enough permissions"
		fi	
		finger $1	
	fi
	shift 1
done
