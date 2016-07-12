#!/bin/bash

script=`readlink -e $0`
scriptpath=`dirname $script`

num_proc=1
trajectory=0
eigens=0
points=0
relaxation=0
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
	-r				Custom relaxation.

  -u [path] User config path.
  -g [path] Global config path.

EOF
}

while getopts "n:u:g:tepr" opt
do
  case "$opt" in
    n) num_proc=$OPTARG;;
    u) user_config=$OPTARG;;
    g) global_config=$OPTARG;;
    t) trajectory=1;;
    e) eigens=1;;
    p) points=1;;
    r) relaxation=1;;
    \:) usage; exit;;
    \?) usage; exit;;
  esac
done

if [ ! -f "$user_config" ]; then
  echo "User config file not found."
  exit
fi

if [ ! -f "$global_config" ]; then
  echo "Global config file not found."
  exit
fi

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

if (( $eigens == 1 )); then
  dirs_before=`eval $ls_command`
  $scriptpath/../applications/eigen_spectra/obj/eigens.exe -u $user_config -g $global_config
  dirs_after=`eval $ls_command`
  results_dir=`diff <(echo "$dirs_before") <(echo "$dirs_after") | grep "^>" | sed -e "s/^>\s*//" | grep "results_*"`

  if [ -z $results_dir ] ; then
    echo "Cannot find results directory."
    echo "Please check program arguments and try again."
    exit
  fi

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

    if [ -z $results_dir ] ; then
      echo "Cannot find results directory."
      echo "Please check program arguments and try again."
      exit
    fi

    $scriptpath/plot_trajectory.sh -i $results_dir
  fi
fi

if (( $relaxation == 1 )); then

  dirs_before=`eval $ls_command`

  comm="$scriptpath/../applications/relaxer/obj/relaxer.exe -u $user_config -g $global_config"

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

    if [ -z $results_dir ] ; then
      echo "Cannot find results directory."
      echo "Please check program arguments and try again."
      exit
    fi

    $scriptpath/plot_trajectory.sh -i $results_dir
  fi
fi
