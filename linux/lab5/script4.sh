name=$1
path=$2
delay=$3
i=0

while true
do
	tar -czf "./${name}${i}".tar.gz ${path}/${name}
	let i++
	sleep ${delay}
done

