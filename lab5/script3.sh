while true
do
	if [[ $(ps -o stat= -p $$) =~ "+" ]] 
	then 
		echo "I'm foreground :( Enter smiley face to make me happy..."
		read a
		if [[ $a = ':)' ]]
		then 
			echo "Yay! I'm Happy :)"
			break
		else 
			echo "You don't want me to be happy? :("
		fi
	else
		echo "I'm background :)"
		sleep 10
	fi
done

while true
do
	echo "Foreground again :("
	sleep 3
done

