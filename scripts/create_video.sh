#!/bin/bash

script=`readlink -e $0`
scriptpath=`dirname $script`

path_to_generation=

user_config=$scriptpath/config.yaml
global_config=$scriptpath/global_config.yaml

period_of_pictures=100
width=1024
height=768

create_excitation_video=false
create_relaxation_video=false

path_to_generation_defined=false
user_config_defined=false
global_config_defined=false

function usage()
{
  cat << EOF
Usage: $0 [OPTIONS]

OPTIONS:
  -p [path] Path to the generation directory. Required option.
  -n [num]  Take every num-th picture and skip others. Default is 100.
  -h [num]  Height of video. Default is 768.
  -w [num]  Width of video. Default is 1024.
  -e        Prepare video for excitation. If neither this nor -r is defined, both are considered defined.
  -r        Prepare video for relaxation. If neither this nor -e is defined, both are considered defined.

  -u [path] User config path.
  -g [path] Global config path.
EOF
}

while getopts ":p:u:g:n:h:w:er" opt
do
  case "$opt" in
    p) path_to_generation=$OPTARG; path_to_generation_defined=true;;
    n) period_of_pictures=$OPTARG;;
    h) height=$OPTARG;;
    w) width=$OPTARG;;
    e) create_excitation_video=true;;
    r) create_relaxation_video=true;;
    u) user_config=$OPTARG; user_config_defined=true;;
    g) global_config=$OPTARG; global_config_defined=true;;
   \:) usage; exit;;
   \?) usage; exit;;
  esac
done

if ! $path_to_generation_defined; then
  usage
  exit
fi

if ! $user_config_defined; then
  if [ -f `pwd`/config.yaml ]; then
    user_config="`pwd`/config.yaml";
  fi
fi

if ! $global_config_defined; then
  if [ -f `pwd`/global_config.yaml ]; then
    global_config="`pwd`/global_config.yaml";
  fi
fi

if [ ! -d "$path_to_generation" ]; then
  echo "Generation directory not found."
  exit
fi

if [ ! -f "$user_config" ]; then
  echo "User config file not found."
  exit
fi

if [ ! -f "$global_config" ]; then
  echo "Global config file not found."
  exit
fi

echo "User config: $user_config"
echo "Global config: $global_config"

# If neither -r nor -e is defined, consider both of them defined
if ! $create_excitation_video && ! $create_relaxation_video; then
  create_excitation_video=true
  create_relaxation_video=true
fi

function setup_plotter()
{
  > $results_dir/plotter.gnu
  echo "set term pngcairo size $width,$height enhanced" >> $results_dir/plotter.gnu
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
}

ls_command="find . -maxdepth 1 -type d"

export LD_LIBRARY_PATH=/usr/local/lib:$scriptpath/../core/last/obj:$LD_LIBRARY_PATH
#TODO: need to extract from mkfiles/default_defs.mk
# Get lib dir for boost from mkfiles/default_defs.mk
boost_lib_dir_name="BOOST_LIB_DIR"
boost_lib_str=`grep "$boost_lib_dir_name\s*=" $scriptpath/../mkfiles/default_defs.mk | sed -e "s/$boost_lib_dir_name\s*=\s*\(.*\)/\1/"`
if [ ! -z $boost_lib_str ]; then
  # remove -L from lib dir
  boost_lib_str=`echo $boost_lib_str | sed -r 's/^.{2}//'`
  export LD_LIBRARY_PATH=${boost_lib_str}:$LD_LIBRARY_PATH
fi

# TODO Need to optimize data preparer for some cases
echo "Preparing data for video ..."
dirs_before=`eval $ls_command`
# TODO There must be a better way to do this
mode='a'
if $create_excitation_video; then
  mode='e'
fi
if $create_relaxation_video; then
  mode='r'
fi
if $create_excitation_video && $create_relaxation_video; then
  mode='a'
fi
$scriptpath/../applications/video_data_preparer/obj/video_data_preparer.exe -u $user_config -g $global_config -p $path_to_generation -m $mode &> /tmp/log.txt
dirs_after=`eval $ls_command`
results_dir=`diff <(echo "$dirs_before") <(echo "$dirs_after") | grep "^>" | sed -e "s/^>\s*//" | grep "results_*"`

if [ -z $results_dir ] ; then
    echo "Cannot find results directory."
    echo "Please check program arguments and try again."
  exit
fi

mv /tmp/log.txt ${results_dir}/log.txt

echo "Finished data preparation."

if $create_excitation_video; then
  echo "Creating images for excitation ..."
  mkdir ${results_dir}/excitation/pictures
  input_files=(`find ${results_dir}/excitation -type f -name "*.txt"`)
  for i in ${input_files[@]};
  do
    name=$(basename "$i" .txt)
    if (( $name % $period_of_pictures != 0 )); then
      continue
    fi
    output="${results_dir}/excitation/pictures/$(($name/$period_of_pictures)).png"
    setup_plotter $i $output "Возбуждение (T=$name)" &>> ${results_dir}/log.txt
  done
  for i in "${input_files[@]}"; do
    rm -f ${i}
  done
  echo "Created images for excitation."

  echo "Creating excitation video ..."
  cat `ls -v ${results_dir}/excitation/pictures/*.png` | ffmpeg -f image2pipe -i - -vcodec mpeg4 "${results_dir}/excitation/video.mp4" &>> ${results_dir}/log.txt
  rm -rf ${results_dir}/excitation/pictures
  echo "Created excitation video ${results_dir}/excitation/video.mp4."
fi

if $create_relaxation_video; then
  mkdir ${results_dir}/relaxation/pictures
  echo "Creating images for relaxation ..."
  input_files=(`find ${results_dir}/relaxation -type f -name "*.txt"`)
  for i in ${input_files[@]};
  do
    name=$(basename "$i" .txt)
    if (( $name % $period_of_pictures != 0 )); then
      continue
    fi
    output="${results_dir}/relaxation/pictures/$(($name/$period_of_pictures)).png"
    setup_plotter $i $output "Релаксация (T=$name)" &>> ${results_dir}/log.txt
  done
  for i in "${input_files[@]}"; do
    rm -f ${i}
  done
  echo "Created images for relaxation."

  echo "Creating relaxation video ..."
  cat `ls -v ${results_dir}/relaxation/pictures/*.png` | ffmpeg -f image2pipe -i - -vcodec mpeg4 "${results_dir}/relaxation/video.mp4" &>> ${results_dir}/log.txt
  rm -rf ${results_dir}/relaxation/pictures
  echo "Created relaxation video ${results_dir}/relaxation/video.mp4."
fi

if $create_excitation_video && $create_relaxation_video; then
  echo "Creating full video ..."
  ffmpeg -i ${results_dir}/excitation/video.mp4 -qscale 1 ${results_dir}/video_1.mpeg &>> ${results_dir}/log.txt
  ffmpeg -i ${results_dir}/relaxation/video.mp4 -qscale 1 ${results_dir}/video_2.mpeg &>> ${results_dir}/log.txt
  cat ${results_dir}/video_1.mpeg ${results_dir}/video_2.mpeg | ffmpeg -f mpeg -i - -vcodec mpeg4 -qscale 1 -strict experimental ${results_dir}/video.mp4 &>> ${results_dir}/log.txt
  rm ${results_dir}/video_1.mpeg
  rm ${results_dir}/video_2.mpeg
  echo "Created full video ${results_dir}/video.mp4."
fi
