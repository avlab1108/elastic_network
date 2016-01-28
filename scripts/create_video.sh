#!/bin/bash

script=`readlink -e $0`
scriptpath=`dirname $script`

path_to_generation=

user_config=$scriptpath/config.yaml
global_config=$scriptpath/global_config.yaml

function usage()
{
  cat << EOF
Usage: $0 [OPTIONS]

OPTIONS:
  -p       Path to the generation directory. Required option.

EOF
}

while getopts "p:tep" opt
do
  case "$opt" in
    p) path_to_generation=$OPTARG;;
   \:) usage; exit;;
   \?) usage; exit;;
  esac
done

function setup_plotter()
{
  > $results_dir/plotter.gnu
  echo "set term pngcairo size 1024,768 enhanced" >> $results_dir/plotter.gnu
  echo "set output \"$2\"" >> $results_dir/plotter.gnu
  echo "unset border" >> $results_dir/plotter.gnu
  echo "unset xtics" >> $results_dir/plotter.gnu
  echo "unset ytics" >> $results_dir/plotter.gnu
  echo "unset ztics" >> $results_dir/plotter.gnu
  echo "set key off" >> $results_dir/plotter.gnu
  echo "set view 60,45,1.5" >> $results_dir/plotter.gnu
  echo "stat \"$1\" index 0 using 1 prefix \"x\" noout" >> $results_dir/plotter.gnu
  echo "stat \"$1\" index 0 using 2 prefix \"y\" noout" >> $results_dir/plotter.gnu
  echo "stat \"$1\" index 0 using 3 prefix \"z\" noout" >> $results_dir/plotter.gnu
  echo "stat \"$1\" using 1 prefix \"all\" noout" >> $results_dir/plotter.gnu
  echo "set xrange [x_min-3:x_max+3]" >> $results_dir/plotter.gnu
  echo "set yrange [y_min-3:y_max+3]" >> $results_dir/plotter.gnu
  echo "set zrange [z_max-3:z_max+3]" >> $results_dir/plotter.gnu
  echo "set title \"$3\"" >> $results_dir/plotter.gnu
  echo "set margin 2" >> $results_dir/plotter.gnu
  echo "plot \"$1\" index 0 using 1:2:3 pt 7 ps 2 lc rgb \"red\", \\" >> $results_dir/plotter.gnu
  echo "\"$1\" index 1:all_blocks-2 using 1:2:3 with lines lc rgb \"red\", \\" >> $results_dir/plotter.gnu
  echo "\"$1\" index all_blocks-1 using 1:2:3 pt 7 ps 2 lc rgb \"blue\"" >> $results_dir/plotter.gnu
  gnuplot $results_dir/plotter.gnu
  rm $results_dir/plotter.gnu
}

ls_command="find . -maxdepth 1 -type d"

#TODO: need to extract from mkfiles/default_defs.mk
export LD_LIBRARY_PATH=/usr/local/lib:$scriptpath/../core/last/obj:$LD_LIBRARY_PATH

echo "Preparing data for video ..."
dirs_before=`eval $ls_command`
$scriptpath/../applications/video_data_preparer/obj/video_data_preparer.exe -u $user_config -g $global_config -p $path_to_generation &> /tmp/log.txt
dirs_after=`eval $ls_command`
results_dir=`diff <(echo "$dirs_before") <(echo "$dirs_after") | grep "^>" | sed -e "s/^>\s*//" | grep "results_*"`

mv /tmp/log.txt ${results_dir}/log.txt

echo "Finished data preparation."

echo "Creating images for excitation ..."
mkdir ${results_dir}/excitation/pictures
for i in `find ${results_dir}/excitation -type f -name "*.txt"`;
do
  name=$(basename "$i" .txt)
  if (( $name % 100 != 0 )); then
    continue
  fi
  output="${results_dir}/excitation/pictures/$(($name/100)).png"
  setup_plotter $i $output "Возбуждение (T=$name)" &>> ${results_dir}/log.txt
done
echo "Created images for excitation."

echo "Creating excitation video ..."
avconv -i "${results_dir}/excitation/pictures/%d.png" "${results_dir}/excitation/video.mp4" &>> ${results_dir}/log.txt
echo "Created excitation video ${results_dir}/excitation/video.mp4."

mkdir ${results_dir}/relaxation/pictures
echo "Creating images for relaxation ..."
for i in `find ${results_dir}/relaxation -type f -name "*.txt"`;
do
  name=$(basename "$i" .txt)
  if (( $name % 100 != 0 )); then
    continue
  fi
  output="${results_dir}/relaxation/pictures/$(($name/100)).png"
  setup_plotter $i $output "Релаксация (T=$name)" &>> ${results_dir}/log.txt
done
echo "Created images for relaxation."

echo "Creating relaxation video ..."
cat `ls -v ${results_dir}/relaxation/pictures/*.png` | avconv -f image2pipe -i - "${results_dir}/relaxation/video.mp4" &>> ${results_dir}/log.txt
echo "Created relaxation video ${results_dir}/relaxation/video.mp4."

echo "Creating full video ..."
avconv -i ${results_dir}/excitation/video.mp4 -qscale 1 ${results_dir}/video_1.mpeg &>> ${results_dir}/log.txt 
avconv -i ${results_dir}/relaxation/video.mp4 -qscale 1 ${results_dir}/video_2.mpeg &>> ${results_dir}/log.txt
cat ${results_dir}/video_1.mpeg ${results_dir}/video_2.mpeg | avconv -f mpeg -i - -vcodec mpeg4 -qscale 1 -strict experimental ${results_dir}/video.mp4 &>> ${results_dir}/log.txt
rm ${results_dir}/video_1.mpeg
rm ${results_dir}/video_2.mpeg
echo "Created full video ${results_dir}/video.mp4."
