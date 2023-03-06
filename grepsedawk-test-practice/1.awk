BEGIN{
s=0
a=0
total=0}

(FNR%2==1)
	total++
	
for(i=1;i<=NF;i++){
	if(FNR%2==0)s++
	if(FNR%2==1)a++
	}

END
print s, a/total
