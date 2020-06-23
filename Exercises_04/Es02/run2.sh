#!/bin/bash

./clean.sh

cp input.gas input.dat

cp config.final config.0
cp old.final old.0
./MolDyn_NVE.exe 1


cp misure_epot.dat gas_epot.dat
cp misure_ekin.dat gas_ekin.dat
cp misure_etot.dat gas_etot.dat
cp misure_temp.dat gas_temp.dat

rm misure_*.dat
