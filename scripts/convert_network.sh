#!/bin/bash

script=`readlink -e $0`
scriptpath=`dirname $script`

input=
l0=
output=

function usage()
{
  cat << EOF
Usage: $0 [OPTIONS]

OPTIONS:
  -i [file]  Input file containing network nodes in CSV format.
  -o [file]  Output file which will contain converted network in YAML format.
  -l [num]   Cutoff distance.

EOF
}

while getopts "i:o:l:" opt
do
  case "$opt" in
    i) input=$OPTARG;;
    o) output=$OPTARG;;
    l) l0=$OPTARG;;
    \:) usage; exit;;
    \?) usage; exit;;
  esac
done

if [ -z "$output" ]; then
  output=$input.yaml
fi

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

$scriptpath/../applications/network_converter/obj/network_converter.exe $input $l0 $output
