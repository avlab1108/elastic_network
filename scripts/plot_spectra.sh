#!/bin/bash

input=
output=

function usage()
{
  cat << EOF
Usage: $0 [OPTIONS]

OPTIONS:
  -i [file]  Input file containing eigenvalues.
  -o [file]  Output image file.

EOF
}

while getopts "i:o:" opt
do
  case "$opt" in
    i) input=$OPTARG;;
    o) output=$OPTARG;;
    \:) usage; exit;;
    \?) usage; exit;;
  esac
done

if [ -z "$output" ]; then
  output=$input.png
fi

> spectra_plotter.gnu
echo "set terminal png enhanced size 1280, 200" >> spectra_plotter.gnu
echo "set output \"$output\"" >> spectra_plotter.gnu
echo "filter(x)=(x>=0.00001)?(x):(1/0)" >> spectra_plotter.gnu
echo "stats \"$input\" using (filter(\$1))" >> spectra_plotter.gnu
echo "unset ytics" >> spectra_plotter.gnu
echo "set xrange [-0.1:log10(STATS_max/STATS_min)+0.1]" >> spectra_plotter.gnu
echo "set yrange [-1:1]" >> spectra_plotter.gnu
echo "plot \"$input\" using (log10(filter(\$1)/STATS_min)):(0) notitle" >> spectra_plotter.gnu

gnuplot spectra_plotter.gnu

rm -f spectra_plotter.gnu
