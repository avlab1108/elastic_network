#!/bin/bash

num_proc=

function usage()
{
  cat << EOF
Usage: $0 [OPTIONS]

OPTIONS:
  -n  Number of processes.

EOF
}

while getopts ":n:": opt
do
  case "$opt" in
    n) num_proc=$OPTARG;;
    ?) usage; exit;;
  esac
done

script=`realpath $0`
scriptpath=`dirname $script`

export LD_LIBRARY_PATH=/home/minas/third_party/boost/install/lib:$scriptpath/../../core/last/obj

ls_command="ls -d */ | sed -e 's/\/$//'"

dirs_before=`eval $ls_command`

#mpirun -np $num_proc $scriptpath/obj/task_manager.exe \
$scriptpath/obj/task_manager.exe \
  -u $scriptpath/config.yaml \
  -g $scriptpath/global_config.yaml \

dirs_after=`eval $ls_command`

results_dir=`diff <(echo "$dirs_before") <(echo "$dirs_after") | grep "^>" | sed -e "s/^>\s*//" | grep "results_*"`

trajectory_files=`find $results_dir -name "trajectory" | tr '\n' ' '`

touch plotter.gnu
echo "set terminal png size 1024, 768" >> plotter.gnu
echo "set output \"$results_dir/trajectory.png\"" >> plotter.gnu
echo "set style data lines" >> plotter.gnu
echo "set grid x" >> plotter.gnu
echo "set grid y" >> plotter.gnu
echo "set grid z" >> plotter.gnu
echo 'set xlabel "{/Symbol D}u_{12}/u_{12}^{(0)}"' >> plotter.gnu
echo 'set ylabel "{/Symbol D}u_{13}/u_{13}^{(0)}"' >> plotter.gnu
echo 'set zlabel "{/Symbol D}u_{23}/u_{23}^{(0)}"' >> plotter.gnu
echo "set style line 5 lt rgb \"blue\" lw 1 pt 6" >> plotter.gnu
echo "splot for [file in \"$trajectory_files\"] file using 1:2:3 with lines notitle ls 5" >> plotter.gnu
echo "set label at 0,0,0 \"\" point pointtype 7 pointsize 1 lc rgb \"red\" front" >> plotter.gnu
gnuplot plotter.gnu

> plotter.gnu
echo "set terminal png size 1024, 768" >> plotter.gnu
echo "set output \"$results_dir/u12_u13.png\"" >> plotter.gnu
echo "set style data lines" >> plotter.gnu
echo "set grid x" >> plotter.gnu
echo "set grid y" >> plotter.gnu
echo 'set xlabel "{/Symbol D}u_{12}/u_{12}^{(0)}"' >> plotter.gnu
echo 'set ylabel "{/Symbol D}u_{13}/u_{13}^{(0)}"' >> plotter.gnu
echo "set style line 5 lt rgb \"blue\" lw 1 pt 6" >> plotter.gnu
echo "plot for [file in \"$trajectory_files\"] file using 1:2 with lines notitle ls 5" >> plotter.gnu
echo "set label at 0,0,0 \"\" point pointtype 7 pointsize 1 lc rgb \"red\" front" >> plotter.gnu
gnuplot plotter.gnu

> plotter.gnu
echo "set terminal png size 1024, 768" >> plotter.gnu
echo "set output \"$results_dir/u12_u23.png\"" >> plotter.gnu
echo "set style data lines" >> plotter.gnu
echo "set grid x" >> plotter.gnu
echo "set grid y" >> plotter.gnu
echo 'set xlabel "{/Symbol D}u_{12}/u_{12}^{(0)}"' >> plotter.gnu
echo 'set ylabel "{/Symbol D}u_{23}/u_{23}^{(0)}"' >> plotter.gnu
echo "set style line 5 lt rgb \"blue\" lw 1 pt 6" >> plotter.gnu
echo "plot for [file in \"$trajectory_files\"] file using 1:3 with lines notitle ls 5" >> plotter.gnu
echo "set label at 0,0,0 \"\" point pointtype 7 pointsize 1 lc rgb \"red\" front" >> plotter.gnu
gnuplot plotter.gnu

> plotter.gnu
echo "set terminal png size 1024, 768" >> plotter.gnu
echo "set output \"$results_dir/u13_u23.png\"" >> plotter.gnu
echo "set style data lines" >> plotter.gnu
echo "set grid x" >> plotter.gnu
echo "set grid y" >> plotter.gnu
echo 'set xlabel "{/Symbol D}u_{13}/u_{13}^{(0)}"' >> plotter.gnu
echo 'set ylabel "{/Symbol D}u_{23}/u_{23}^{(0)}"' >> plotter.gnu
echo "set style line 5 lt rgb \"blue\" lw 1 pt 6" >> plotter.gnu
echo "plot for [file in \"$trajectory_files\"] file using 2:3 with lines notitle ls 5" >> plotter.gnu
echo "set label at 0,0,0 \"\" point pointtype 7 pointsize 1 lc rgb \"red\" front" >> plotter.gnu
gnuplot plotter.gnu

rm -f plotter.gnu
