#!/bin/bash
while [ $# -gt 0 ]
do
	if [ -d "$1" ]
	then
		echo $(stat --format="%U %n" $1)
		echo $(find $1 -type f -print0 | du --files0-from=- -h | sort -n | head -n1)
	else
		if [ -f "$1" ]
		then
			echo $(tac $1)
		else
			echo "Argument is neither a file or a directory"
		fi
	fi
	shift 1
done
