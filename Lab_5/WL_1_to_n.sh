
#!/bin/bash

read -p "Enter the value of n: " n

i=1
while [ $i -le $n ]
do
    echo $i
    i=$((i + 1))
done
