#!/bin/bash
for for_word in $(cat who.fake | echo $(awk '{print $1}'))
do
	echo "$for_word $(cat ps.fake | grep -E -c "^$for_word")"
done
