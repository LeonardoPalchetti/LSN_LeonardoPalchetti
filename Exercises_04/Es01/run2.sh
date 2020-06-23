#!/bin/bash

./clean.sh
cp config.fcc config.initial

cp input.solid input.dat
cp config.initial config.0
./MolDyn_NVE.exe 0

cp output_epot.dat  solid2_epot.dat
cp output_ekin.dat  solid2_ekin.dat
cp output_etot.dat  solid2_etot.dat
cp output_temp.dat  solid2_temp.dat

./clean.sh

cp input.liquid input.dat
cp config.initial config.0
./MolDyn_NVE.exe 0

cp output_epot.dat  liquid2_epot.dat
cp output_ekin.dat  liquid2_ekin.dat
cp output_etot.dat  liquid2_etot.dat
cp output_temp.dat  liquid2_temp.dat

./clean.sh

cp input.gas input.dat
cp config.initial config.0
./MolDyn_NVE.exe 0

cp output_epot.dat  gas2_epot.dat
cp output_ekin.dat  gas2_ekin.dat
cp output_etot.dat  gas2_etot.dat
cp output_temp.dat  gas2_temp.dat

./clean.sh
