# Ubuntu instaii instructions

su
apt-get install aptitude
aptitude install mpich2
apt-get install liblapacke-dev
apt-get install libblas-dev
apt-get install gnuplot
apt-get install git
apt-get install cmake
download armadillo, yaml-cpp, boost latest versions

boost:
./bootstrap.sh
add "using mpi ;" to the end of project-config.jam
./b2 --target=shared,static
./b2 install

yaml-cpp:
git clone https://github.com/jbeder/yaml-cpp
cd yaml-cpp
mkdir build
cd build
cmake ..
make
make install

lapack:
install OPENBLAS-base OPENBLAS-dev packages



armadillo:
./configure
make
make install

elastic_network:
git clone https://github.com/mr-junior/elastic_network
edit mkfiles/default_defs.mk for boost include and lib dirs

./check_libs.sh

if ok

make all

