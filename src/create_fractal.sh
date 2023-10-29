#!/bin/bash
FRACTALS=$1
PALETTES=`ls palettes/*.json | cut -d'/' -f2 | cut -d'.' -f1`

# create fractal universe
for j in ${FRACTALS}; do mkdir -p universe/fractals/$j; for i in ${PALETTES}; do ./Fractals.exe /params=parameters/$j.json /palette=palettes/$i.json /image=universe/fractals/$j/$j-$i.png; done; done;
for j in ${FRACTALS}; do mkdir -p universe/fractals/$j; for i in ${PALETTES}; do ./Fractals.exe /params=parameters/$j.json /palette=palettes/$i.json /image=universe/fractals/$j/$j-$i-inverted.png /invert; done; done;
