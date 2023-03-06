#!/bin/bash
if [ $# -lt 1 ]
then
	echo "Impossible"
	exit
fi
for file in $(find $1 -perm -o=w -type f)
do
	echo "$(ls -l $file | awk '{print $1}') $file"
	chmod o-w $file
	echo "$(ls -l $file | awk '{print $1}') $file"
done
