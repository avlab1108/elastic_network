#!/bin/bash

script=`readlink -e $0`
scriptpath=`dirname $script`

num_proc=1
trajectory=0
eigens=0
points=0
user_config=$scriptpath/config.yaml
global_config=$scriptpath/global_config.yaml

function usage()
{
  cat << EOF
Usage: $0 [OPTIONS]

OPTIONS:
  -n [num]  Number of processes.
  -t        Perform trajectory task.
  -e        Calculate eigenvalues and plot spectra.
  -p        Calculate 3 optimal points.

  -u        User config path.
  -g        Global config path.

EOF
}

while getopts "n:u:g:tep" opt
do
  case "$opt" in
    n) num_proc=$OPTARG;;
    u) user_config=$OPTARG;;
    g) global_config=$OPTARG;;
    t) trajectory=1;;
    e) eigens=1;;
    p) points=1;;
    \:) usage; exit;;
    \?) usage; exit;;
  esac
done

ls_command="find . -maxdepth 1 -type d"

#TODO: need to extract from mkfiles/default_defs.mk
export LD_LIBRARY_PATH=/usr/local/lib:$scriptpath/../core/last/obj:$LD_LIBRARY_PATH

if (( $eigens == 1 )); then
  dirs_before=`eval $ls_command`
  $scriptpath/../applications/eigen_spectra/obj/eigens.exe -u $user_config -g $global_config
  dirs_after=`eval $ls_command`
  results_dir=`diff <(echo "$dirs_before") <(echo "$dirs_after") | grep "^>" | sed -e "s/^>\s*//" | grep "results_*"`
  $scriptpath/plot_spectra.sh -i $results_dir/eigens.txt -o $results_dir/eigen_spectra.png
  exit
fi

if (( $points == 1 )); then
  $scriptpath/../applications/optimal_nodes/obj/optimal_nodes.exe -u $user_config -g $global_config
  exit
fi

if (( $trajectory == 1 )); then

  dirs_before=`eval $ls_command`

  comm="$scriptpath/../applications/trajectory/obj/trajectory.exe -u $user_config -g $global_config"

  result=0

  if (( $num_proc > 1 )); then
    mpirun -np $num_proc $comm
    result=$?
  else
    eval $comm
    result=$?
  fi

  if (( $result == 0 )); then
    dirs_after=`eval $ls_command`
    results_dir=`diff <(echo "$dirs_before") <(echo "$dirs_after") | grep "^>" | sed -e "s/^>\s*//" | grep "results_*"`
    $scriptpath/plot_trajectory.sh -i $results_dir
  fi
fi
