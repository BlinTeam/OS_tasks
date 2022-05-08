#! /usr/bin/bash

gcd() {
	m = $1
	n = $2
	
	while ((m-n))
	do
		if [[ m -gt n ]]; then
			((m=m-n))
		else 
			((n=n-m))
		fi
	done
	echo "GCD is $m"
}

#main
read m n
while ((m+n))
do
	gcd m n
	read m n
done 
echo "bye"
