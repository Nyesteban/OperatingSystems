#!/bin/bash
i=0
for a in $@
do
	for b in $(find $a -name "*.c" -type f)
		    do
			echo $b
			i=$(($i+1))
		    done
done	
echo $i
