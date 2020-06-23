#!/bin/bash

./clean.sh
cp config.fcc config.initial

cp input.gas input.dat
cp config.initial config.0
./MolDyn_NVE.exe 0

for i in {1..14}
do
cp config.final config.0
cp old.final old.0
./MolDyn_NVE.exe 1
done

