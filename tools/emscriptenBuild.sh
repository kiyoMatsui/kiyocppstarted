#!/bin/bash

mkdir -p build && cd build

emcmake cmake ..
# or cmake -DCMAKE_INSTALL_PREFIX:PATH=/home
emmake make

# apt-file can find package from file ... run ~$ apt-file update and then ~$ apt-file search kwallet.h

#to install go to build directory and run:
#~$ sudo make install ..
#to uninstall software (note will not remove directories)
#~$ xargs sudo rm < install_manifest.txt




