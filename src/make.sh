#!/bin/sh
sh clean.sh
cython -a --cplus DBSCAN.pyx
gcc -std=c++17 -pthread -g -O3 -fPIC -I. -I/usr/include/python3.9 -c DBSCAN.cpp -o DBSCAN.cpython-39-x86_64-linux-gnu.o
g++ -std=c++17 -pthread -shared -O3 DBSCAN.cpython-39-x86_64-linux-gnu.o -o DBSCAN.cpython-39-x86_64-linux-gnu.so
