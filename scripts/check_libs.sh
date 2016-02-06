#!/bin/bash

script=`readlink -e $0`
scriptpath=`dirname $script`

compiler=

# temporary till yaml-cpp will get rid of boost includes
boost_include_dir=

function check_gcc
{
  gcc_version_num=`gcc -dumpversion`
  gcc_version=`echo $gcc_version_num | sed -e 's/\.\([0-9][0-9]\)/\1/g' -e 's/\.\([0-9]\)/0\1/g' -e 's/^[0-9]\{3,4\}$$/&00/'`
  if [ $gcc_version -gt 40600 ]; then
    if [ $gcc_version -gt 40900 ]; then
      echo "GCC version ($gcc_version_num) is OK."
    else
      echo "GCC version ($gcc_version_num) is sufficient for compilation, but it is recommended to upgrade to version 4.9."
    fi
  else
    echo "GCC version is incorrect. Please check GCC installation."
    exit 1;
  fi
}

function check_mpi
{
  compiler_dir_var="COMPILER_LOCATION"
  compiler_dir=`grep "$compiler_dir_var\s*=" $scriptpath/../mkfiles/default_defs.mk | sed -e "s/$compiler_dir_var\s*=\s*\(.*\)/\1/"`

  compiler_name_var="CXX_NAME"
  compiler_name=`grep "$compiler_name_var\s*=" $scriptpath/../mkfiles/default_defs.mk | sed -e "s/$compiler_name_var\s*=\s*\(.*\)/\1/"`

  if [ -z "$compiler_dir" ] || [ ! -f "$compiler_dir/bin/$compiler_name" ]; then
    echo "Cannot find mpic++ executable."
    exit 1
  fi
  compiler="$compiler_dir/bin/$compiler_name"

  echo "#include <mpi.h>" > test_mpi_cpp.cpp
  echo "int main() {}" >> test_mpi_cpp.cpp
  $compiler test_mpi_cpp.cpp -o test_mpi
  result=$?
  rm -f test_mpi_cpp.cpp
  if [ $result -ne 0 ]; then
    echo "Cannot find usable mpic++."
    exit 1
  fi
  echo "Found usable mpic++."

  mpi_exec="$compiler_dir/bin/mpirun"
  $mpi_exec -np 2 ./test_mpi
  result=$?
  rm -f test_mpi
  if [ $result -ne 0 ]; then
    echo "Cannot find usable mpirun."
    exit 1
  fi
  echo "Found usable mpirun."

  echo "Found usable MPI environment."
}

function check_boost
{
  include_dir_name="BOOST_INCLUDE_DIR"
  include_dir=`grep "$include_dir_name\s*=" $scriptpath/../mkfiles/default_defs.mk | sed -e "s/$include_dir_name\s*=\s*\-I\(.*\)/\1/"`
  boost_include_dir=$include_dir
  if [ -z "$include_dir" ] || [ ! -d "$include_dir" ]; then
    echo "Cannot find boost include directory. Please check $include_dir_name variable's value in mkfiles/default_defs.mk"
    exit 1
  fi
  echo "Found boost include directory."
  necessary_includes=("boost/numeric/odeint.hpp"
                      "boost/numeric/odeint/external/openmp/openmp.hpp"
                      "boost/mpi.hpp"
                      "boost/filesystem.hpp"
                      "boost/program_options.hpp"
                      "boost/mpi/nonblocking.hpp");
  echo > test_boost.cpp
  for i in ${necessary_includes[@]}
  do
    if [ ! -f $include_dir/$i ]; then
      echo "Cannot find necessary include file $include_dir/$i."
      exit 1
    fi
    echo "#include \"$i\"" >> test_boost.cpp
  done
  echo "Found necessary includes in boost include directory."
  lib_dir_name="BOOST_LIB_DIR"
  lib_str=`grep "$lib_dir_name\s*=" $scriptpath/../mkfiles/default_defs.mk | sed -e "s/$lib_dir_name\s*=\s*\(.*\)/\1/"`
  read -r -a prefixed_lib_dirs <<< "$lib_str"
  lib_dirs=()
  compile_command="$compiler test_boost.cpp -o test_boost -I$include_dir"
  for prefixed_lib_dir in "${prefixed_lib_dirs[@]}"
  do
    lib_dir=`echo $prefixed_lib_dir | sed -e "s/\s*\-L\(.*\)/\1/"`
    if [ -z "$lib_dir" ] || [ ! -d "$lib_dir" ]; then
      echo "Cannot find boost lib directory. Please check $lib_dir_name variable's value in mkfiles/default_defs.mk"
      exit 1
    else
      compile_command+=" -L$lib_dir"
      lib_dirs+=("$lib_dir")
    fi
  done
  echo "Found boost lib directories."
  necessary_libs=("libboost_mpi.so"
                  "libboost_serialization.so"
                  "libboost_program_options.so"
                  "libboost_system.so"
                  "libboost_filesystem.so")
  for lib in ${necessary_libs[@]}
  do
    missed_count=0
    for dir in ${lib_dirs[@]}
    do
      if [ -f $dir/$lib ]; then
        compile_command+=" -l"`echo $lib | sed -e "s/lib//" -e "s/\.so//"`
        break
      else
        ((++missed_count))
      fi
    done
    if (( $missed_count == ${#lib_dirs[@]} )); then
      echo "Cannot find necessary so file $lib."
      exit 1
    fi
  done
  echo "Found necessary so's in boost lib directories."

  echo "int main() {boost::mpi::environment e;}" >> test_boost.cpp
  eval $compile_command
  result=$?
  rm -f test_boost.cpp test_boost
  if [ $result -ne 0 ]; then
    echo "Cannot find usable boost library."
    exit 1
  fi
  echo "Found usable boost library."
}

function check_armadillo
{
  lib_dir_var="ARMADILLO_LIB_DIR"
  lib_dir=`grep "$lib_dir_var\s*=" $scriptpath/../mkfiles/default_defs.mk | sed -e "s/$lib_dir_var\s*=\s*\(.*\)/\1/"`
  include_dir_var="ARMADILLO_INCLUDE_DIR"
  include_dir=`grep "$include_dir_var\s*=" $scriptpath/../mkfiles/default_defs.mk | sed -e "s/$include_dir_var\s*=\s*\(.*\)/\1/"`
  libs_var="ARMADILLO_LIB"
  libs=`grep "$libs_var\s*=" $scriptpath/../mkfiles/default_defs.mk | sed -e "s/$libs_var\s*=\s*\(.*\)/\1/"`
  echo "#include <armadillo>" > test_armadillo.cpp
  echo "int main() {arma::mat m; arma::vec v;}" >> test_armadillo.cpp
  $compiler $include_dir $lib_dir $libs test_armadillo.cpp -o test_armadillo &> /dev/null
  result=$?
  rm -f test_armadillo.cpp test_armadillo
  if [ $result -ne 0 ]; then
    echo "Cannot find usable Armadillo library."
    exit 1
  fi
  echo "Found usable Armadillo library."
}

function check_yaml
{
  lib_dir_var="YAML_LIB_DIR"
  lib_dir=`grep "$lib_dir_var\s*=" $scriptpath/../mkfiles/default_defs.mk | sed -e "s/$lib_dir_var\s*=\s*\(.*\)/\1/"`
  include_dir_var="YAML_INCLUDE_DIR"
  include_dir=`grep "$include_dir_var\s*=" $scriptpath/../mkfiles/default_defs.mk | sed -e "s/$include_dir_var\s*=\s*\(.*\)/\1/"`
  echo "#include <yaml-cpp/yaml.h>" > test_yaml_cpp.cpp
  echo "int main() {YAML::Node n;}" >> test_yaml_cpp.cpp
  $compiler -std=c++11 $include_dir $lib_dir -I$boost_include_dir -lyaml-cpp test_yaml_cpp.cpp -o test_yaml_cpp &> /dev/null
  result=$?
  rm -f test_yaml_cpp.cpp test_yaml_cpp
  if [ $result -ne 0 ]; then
    echo "Cannot find usable yaml-cpp library."
    exit 1
  fi
  echo "Found usable yaml-cpp library."
}

echo "Checking GCC..."
check_gcc

echo ""
echo "Checking MPI..."
check_mpi

echo ""
echo "Checking boost..."
check_boost

echo ""
echo "Checking Armadillo..."
check_armadillo

echo ""
echo "Checking yaml-cpp..."
check_yaml
