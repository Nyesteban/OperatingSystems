#!/bin/bash
if [ $# -lt 2 ]
then
	echo "Impossible"
	exit
fi
f1=$1
f2=$2
shift 2
echo "" > $f2
while [ $# -gt 0 ]
do
	if cat /etc/passwd | awk -F: '{print $1}' | grep -q $1
	then
		ans=$(du -bs $(cat /etc/passwd | awk -F: '{print $1":"$6}' | grep -E '^$1' | awk -F: '{print $2}') | awk '{print $1}')" "$1
		echo $ans
	else
		echo $1 >> $f2
	fi
	shift 1
done | sort -n > $f1
