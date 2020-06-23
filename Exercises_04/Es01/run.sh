#!/bin/bash

./clean.sh
cp config.fcc config.initial

cp input.solid input.dat
cp config.initial config.0
./MolDyn_NVE.exe 0

for i in {1..9}
do
cp config.final config.0
cp old.final old.0
./MolDyn_NVE.exe 1
done

cp output_epot.dat  solid_epot.dat
cp output_ekin.dat  solid_ekin.dat
cp output_etot.dat  solid_etot.dat
cp output_temp.dat  solid_temp.dat

./clean.sh

cp input.liquid input.dat
cp config.initial config.0
./MolDyn_NVE.exe 0

for i in {1..9}
do
cp old.final old.0
cp config.final config.0
./MolDyn_NVE.exe 1
done

cp output_epot.dat  liquid_epot.dat
cp output_ekin.dat  liquid_ekin.dat
cp output_etot.dat  liquid_etot.dat
cp output_temp.dat  liquid_temp.dat

./clean.sh

cp input.gas input.dat
cp config.initial config.0
./MolDyn_NVE.exe 0

for i in {1..9}
do
cp old.final old.0
cp config.final config.0
./MolDyn_NVE.exe 1

done

cp output_epot.dat  gas_epot.dat
cp output_ekin.dat  gas_ekin.dat
cp output_etot.dat  gas_etot.dat
cp output_temp.dat  gas_temp.dat

./clean.sh
