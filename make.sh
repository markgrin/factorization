#!/bin/sh
[ -f /bin/g++ ] &&  g++ src/main.cpp src/full.cpp src/fermat.cpp src/polflo.cpp src/polflomt.cpp src/pollard.cpp src/common.cpp -lgmp -lgmpxx -lpthread -o factorization

