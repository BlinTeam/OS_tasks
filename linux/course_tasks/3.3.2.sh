#! /usr/bin/bash

while true
do
	echo "enter your name:"
	read name

	if [[ -z $name || $name == 0 ]]; then
		echo "bye"; break
	fi

	echo "enter your age:"
	read age

	if [[ $age == 0 ]]; then
		echo "bye"; break
	fi
	
	group=""

	if [[ $age -le 16 && $age -gt 0 ]]; then
		group='child';
		elif [[ $age -gt 16 && $age -le 25 ]]; then
			group='youth';
				else group='adult';
	fi

	echo "$name, your group is $group"

	done


