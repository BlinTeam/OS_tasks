#!/bin/bash

DIR1=$PWD/$1
DIR2=$PWD/$2
cd $DIR1
arr1=($(ls *))
cd $DIR2
arr2=($(ls *))

for f in "${arr1[@]}"; do
    flag=false
    for g in "${arr2[@]}"; do    
        if [[ "$f" == "$g" ]] 
        then
            if [[ `date -r "$DIR1/$f" +%s` -lt `date -r "$DIR2/$g" +%s` ]]
            then    
                flag=true
            
            fi
        break
        fi

    done
    if [[ "$flag" == false ]]
    then 
        cp -f $DIR1/$f $DIR2/
    fi
done

for f in "${arr2[@]}"; do
    flag=false
    for g in "${arr1[@]}"; do
        if [[ "$f" == "$g" ]]
        then
            flag=true
            break
        fi
    done
    if [[ "$flag" == false ]]
    then
        rm $DIR2/$f
    fi
done
