#!/bin/bash

./clean.sh
cp config.fcc config.initial

cp input.solid input.dat
cp config.initial config.0
./Monte_Carlo_NVT.exe 0

cp output.gave.0  solid.Gave.dat
cp output.gofr.0  solid.Gofr.dat
cp output.pres.0  solid.Pres.dat
cp output.epot.0  solid.Epot.dat
cp Pres.dat  Solid_Pres.dat
cp Epot.dat  Solid_Epot.dat


rm output.*
rm Pres.dat
rm Epot.dat


cp input.liquid input.dat
cp config.initial config.0
./Monte_Carlo_NVT.exe 0

cp output.gave.0  liquid.Gave.dat
cp output.gofr.0  liquid.Gofr.dat
cp output.pres.0  liquid.Pres.dat
cp output.epot.0  liquid.Epot.dat
cp Pres.dat  Liquid_Pres.dat
cp Epot.dat  Liquid_Epot.dat

rm output.*
rm Pres.dat
rm Epot.dat

cp input.gas input.dat
cp config.initial config.0
./Monte_Carlo_NVT.exe 0

cp output.gave.0 gas.Gave.dat
cp output.gofr.0  gas.Gofr.dat
cp output.pres.0  gas.Pres.dat
cp output.epot.0  gas.Epot.dat
cp Pres.dat  Gas_Pres.dat
cp Epot.dat  Gas_Epot.dat

rm output.*
rm Pres.dat
rm Epot.dat
