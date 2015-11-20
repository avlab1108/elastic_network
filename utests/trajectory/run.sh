#!/bin/bash

export LD_LIBRARY_PATH=/home/minas/third_party/boost/install/lib:/home/minas/elastic_network/core/last/obj

mkdir -p /home/minas/elastic_network/utests/trajectory/sample

for i in {1..20} ; do
  echo "running for i =" $i
  /home/minas/elastic_network/utests/trajectory/obj/trajectory.exe
  mv trajectory.txt /home/minas/elastic_network/utests/trajectory/sample/trajectory$i.txt
done
