#!/bin/bash
if [ $# -lt 1 ]
then
	echo "Impossible"
	exit
fi
if (cat /etc/passwd | awk -F: '{print $1}' | grep -E -q "^($1)$")
then
	a=$1
else
	echo "Invalid username"
	exit
fi
shift 1
while [ $# -gt 0 ]
do
	if [ -d "$1" ]
	then
		for word in $(find "$1" -type f)
		do
			if [ "$(stat --format="%U" "$word")" == "$a" ]
			then
				echo $word
			fi
		done
	else
		echo "Invalid directory"
	fi
	shift 1
done
