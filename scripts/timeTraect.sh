#!/bin/bash

if [[ $# != 1 ]] ; then
    echo 'Argument should be: path'
    exit 1
fi

F='tmp'
mkdir $F

{ echo -ne "\n"; cat $1; } > $F/file.new

awk '/^$/{getline; print}' $F/file.new > $F/first.txt
awk '/^$/{print x;print};{x=$0}' $F/file.new > $F/last.txt
sed -i '/^$/d' $F/last.txt 

paste -d ' ' $F/first.txt $F/last.txt > $F/combined.txt
# sed -i '${/^$/d;}' $F/combined.txt
sed -i '$ d' $F/combined.txt


awk '{ print NR, sqrt(($1-$4)*($1-$4) + ($2-$5)*($2-$5) + ($3-$6)*($3-$6)) }' $F/combined.txt > $F/traect.txt

cp plotTimeTraect.gnu $F
cd $F
gnuplot plotTimeTraect.gnu
cd ..
cp $F/*.png .

# rm -rf $F


