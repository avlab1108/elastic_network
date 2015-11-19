#!/bin/bash

export LD_LIBRARY_PATH=/home/minas/third_party/boost/install/lib:/home/minas/elastic_network/core/last/obj

mpirun -np 5 /home/minas/elastic_network/utests/task_manager/obj/task_manager.exe \
  -u /home/minas/elastic_network/utests/task_manager/config.yaml \
  -g /home/minas/elastic_network/utests/task_manager/global_config.yaml \
