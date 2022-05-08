#! /usr/bin/bash
calc()
{
	let " result = $1 $2 $3 "
	echo "$result"
}
#main
while true
do
	read n1 op n2
	if [[ $n1 == "exit" ]]; then
	       echo "bye"
       	       exit 0
	fi
	
	if [[ "${n1}" =~ ^[+-]?[0-9]+$ ]] && [[ "${n2}" =~ ^[+-]?[0-9]+$ ]]; then
		calc $n1 "$op" $n2
	else 
		echo "error" 	
		exit 0
	fi
done

