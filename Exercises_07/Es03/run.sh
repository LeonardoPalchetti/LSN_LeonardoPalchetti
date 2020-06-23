#!/bin/bash

./clean.sh
cp input.gas input.dat

cp config.final config.0
cp old.final old.0
./MolDyn_NVE.exe 1

cp ave.gofr.0  gas.gofr.dat
cp ave.etot.0  gas.etot.dat
cp ave.epot.0  gas.epot.dat
cp ave.ekin.0  gas.ekin.dat
cp ave.temp.0  gas.temp.dat



