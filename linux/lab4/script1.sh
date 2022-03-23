#!/bin/bash

echo $LAB1 $LAB2

STR=$LAB1$LAB2
SUBSTR=${STR/$LAB2/}


echo $STR
echo $SUBSTR

echo 'Bye-bye, '${STR/$SUBSTR/}

