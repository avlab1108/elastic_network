#!/bin/bash

script=`readlink -e $0`
scriptpath=`dirname $script`

function check_gcc {
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

function check_mpi {
  echo "#include <mpi.h>" > test_mpi_cpp.cpp
  echo "int main() {}" >> test_mpi_cpp.cpp
  mpic++ test_mpi_cpp.cpp -o test_mpi
  result=$?
  rm -f test_mpi_cpp.cpp
  if [ $result -ne 0 ]; then
    echo "Cannot find usable mpic++."
    rm -f test_mpi_cpp.cpp
    exit 1
  else
    echo "Found usable mpic++."
  fi
  mpirun -np 2 ./test_mpi
  result=$?
  if [ $result -ne 0 ]; then
    echo "Cannot find usable mpirun."
    rm -f test_mpi
    exit 1
  else
    echo "Found usable mpirun."
  fi
  rm -f test_mpi
}

function check_boost {
  include_dir_name="BOOST_INCLUDE_DIR"
  include_dir=`grep "$include_dir_name\s*=" $scriptpath/../mkfiles/default_defs.mk | sed -e "s/$include_dir_name\s*=\s*\-I\(.*\)/\1/"`
  if [ -z "$include_dir" ] || [ ! -d "$include_dir" ]; then
    echo "Cannot find boost include directory. Please check $include_dir_name variable's value in mkfiles/default_defs.mk"
    exit 1
  else
    echo "Found boost include directory."
  fi
  necessary_includes=("boost/numeric/odeint.hpp"
                      "boost/numeric/odeint/external/openmp/openmp.hpp"
                      "boost/mpi.hpp"
                      "boost/filesystem.hpp"
                      "boost/program_options.hpp"
                      "boost/mpi/nonblocking.hpp");
  echo > test_boost.cpp
  for i in ${necessary_includes[@]}; do
    if [ ! -f $include_dir/$i ]; then
      echo "Cannot find necessary include file $include_dir/$i."
      exit 1
    fi
    echo "#include \"$i\"" >> test_boost.cpp
  done
  echo "Found necessary includes in boost include directory."
  lib_dir_name="BOOST_LIB_DIR"
  lib_dir=`grep "$lib_dir_name\s*=" $scriptpath/../mkfiles/default_defs.mk | sed -e "s/$lib_dir_name\s*=\s*\-L\(.*\)/\1/"`
  if [ -z "$lib_dir" ] || [ ! -d "$lib_dir" ]; then
    echo "Cannot find boost lib directory. Please check $lib_dir_name variable's value in mkfiles/default_defs.mk"
    exit 1
  else
    echo "Found boost lib directory."
  fi
  compile_command="mpic++ test_boost.cpp -o test_boost -I"$include_dir" -L"$lib_dir
  necessary_libs=("libboost_mpi.so"
                  "libboost_serialization.so"
                  "libboost_program_options.so"
                  "libboost_system.so"
                  "libboost_filesystem.so")
  for i in ${necessary_libs[@]}; do
    if [ ! -f $lib_dir/$i ]; then
      echo "Cannot find necessary so file $lib_dir/$i."
      exit 1
    fi
    compile_command+=" -l"`echo $i | sed -e "s/lib//" -e "s/\.so//"`
  done
  echo "Found necessary so's in boost lib directory."
  echo "int main() {}" >> test_boost.cpp
  eval $compile_command
  result=$?
  rm -f test_boost.cpp test_boost
  if [ $result -ne 0 ]; then
    echo "Cannot find usable boost library."
  else
    echo "Found usable boost library."
  fi
}

function check_armadillo {
  echo "#include \"armadillo\"" > test_armadillo.cpp
  echo "int main() {}" >> test_armadillo.cpp
  g++ -larmadillo test_armadillo.cpp -o test_armadillo &> /dev/null
  result=$?
  rm -f test_armadillo.cpp test_armadillo
  if [ $result -ne 0 ]; then
    echo "Cannot find usable Armadillo library."
  else
    echo "Found usable Armadillo library."
  fi
}

function check_yaml {
  echo "#include \"yaml-cpp/yaml.h\"" > test_yaml_cpp.cpp
  echo "int main() {}" >> test_yaml_cpp.cpp
  g++ -lyaml-cpp test_yaml_cpp.cpp -o test_yaml_cpp &> /dev/null
  result=$?
  rm -f test_yaml_cpp.cpp test_yaml_cpp
  if [ $result -ne 0 ]; then
    echo "Cannot find usable yaml-cpp library."
  else
    echo "Found usable yaml-cpp library."
  fi
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
