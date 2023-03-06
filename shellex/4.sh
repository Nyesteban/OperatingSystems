#!/bin/bash
if [ $# -lt 2 ]
then
	echo "Impossible"
	exit
fi
n=$1
buffer=""
shift 1
while [ $# -gt 0 ]
do
	echo "File $1 uses the libraries:"
	cat $1 | grep -E '^[#]include *[<](.*)[>]$' | sed -E 's/^[#]include *[<](.*)[>]$/\1/g'
	buffer="$buffer $(cat $1 | grep -E '^[#]include *[<](.*)[>]$' | sed -E 's/^[#]include *[<](.*)[>]$/\1/g')"
	shift 1
done

echo "***********"

echo $buffer | awk '{for(i=1;i<=NF;i++){print $i}}' | sort | uniq -c | sort -nr | head -n $n


