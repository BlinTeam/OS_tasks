#! /usr/bin/bash
case $1 in
	0)
		echo "No students"
		;;
	1)
		echo "1 student"
		;;
	2 | 3 | 4) 
		echo "$1 students"
		;;
	*)
		echo "A lot of students"
		;;
esac
