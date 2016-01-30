#!/bin/bash

input=

function usage()
{
  cat << EOF
Usage: $0 [OPTIONS]

OPTIONS:
  -i [dir]  Input file containing results.

EOF
}

while getopts "i:" opt
do
  case "$opt" in
    i) input=$OPTARG;;
    \:) usage; exit;;
    \?) usage; exit;;
  esac
done

function row_to_label()
{
  case $1 in
    "1") return 12;;
    "2") return 13;;
    "3") return 23;;
    *) return 0;;
  esac
}

function setup_plotter_impl()
{
  output_file=$1
  row_to_label $2
  x_label=$?
  row_to_label $3
  y_label=$?
  > plotter.gnu
  echo "set terminal png enhanced size 1280, 1024" >> plotter.gnu
  echo "set output \"$output_file\"" >> plotter.gnu
  echo "set style data lines" >> plotter.gnu
  echo "set style line 5 lt rgb \"blue\" lw 1 pt 6" >> plotter.gnu
  echo "set grid x" >> plotter.gnu
  echo "set grid y" >> plotter.gnu
  echo "set xlabel \"{/Symbol D}u_{$x_label}/u_{$x_label}^{(0)}\"" >> plotter.gnu
  echo "set ylabel \"{/Symbol D}u_{$y_label}/u_{$y_label}^{(0)}\"" >> plotter.gnu
  echo "set label at 0,0,0 \"\" point pointtype 7 pointsize 1 lc rgb \"red\" front" >> plotter.gnu
}

function setup_2d_plotter()
{
  trajectories=$1
  setup_plotter_impl $2 $3 $4
  echo "plot for [file in \"$trajectories\"] file using $3:$4 with lines notitle ls 5" >> plotter.gnu
  gnuplot plotter.gnu
}

function setup_3d_plotter()
{
  trajectories=$1
  setup_plotter_impl $2 1 2
  row_to_label 3
  z_label=$?
  echo "set grid z" >> plotter.gnu
  echo "set zlabel \"{/Symbol D}u_{$z_label}/u_{$z_label}^{(0)}\"" >> plotter.gnu
  echo "splot for [file in \"$trajectories\"] file using 1:2:3 with lines notitle ls 5" >> plotter.gnu
  gnuplot plotter.gnu
}

trajectory_files=`find $input -name "trajectory.txt" | tr '\n' ' '`

if [ -z "$trajectory_files" ]; then
  echo "No trajectory files found."
  exit
fi

touch plotter.gnu
setup_3d_plotter "$trajectory_files" "$input/trajectory.png"
setup_2d_plotter "$trajectory_files" "$input/u12_u13.png" 1 2
setup_2d_plotter "$trajectory_files" "$input/u12_u23.png" 1 3
setup_2d_plotter "$trajectory_files" "$input/u13_u23.png" 2 3
rm -f plotter.gnu
