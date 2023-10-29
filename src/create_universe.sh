#!/bin/bash
FRACTALS=`ls parameters/*.json | grep -v 'biomorph' | grep -v mandelbrot | cut -d'/' -f2 | cut -d'.' -f1`
BIOMORPHS=`ls parameters/biomorph-*.json | cut -d'/' -f2 | cut -d'-' -f2 | cut -d'.' -f1`
PALETTES=`ls palettes/*.json | cut -d'/' -f2 | cut -d'.' -f1`

# create biomorph universe
for j in ${BIOMORPHS}; do mkdir -p universe/biomorphs/$j; for i in ${PALETTES}; do ./Fractals.exe /params=parameters/biomorph-$j.json /palette=palettes/$i.json /image=universe/biomorphs/$j/$j-$i.png; done; done;
for j in ${BIOMORPHS}; do mkdir -p universe/biomorphs/$j; for i in ${PALETTES}; do ./Fractals.exe /params=parameters/biomorph-$j.json /palette=palettes/$i.json /image=universe/biomorphs/$j/$j-$i-inverted.png /invert; done; done;

# create mandelbrots
for j in mandelbrot mandelbrot4; do mkdir -p universe/fractals/$j-histogram; for i in ${PALETTES}; do ./Fractals.exe /params=parameters/$j.json /palette=palettes/$i.json /image=universe/fractals/$j-histogram/$j-histogram-$i.png /histogram; done; done;
for j in mandelbrot mandelbrot4; do mkdir -p universe/fractals/$j-histogram; for i in ${PALETTES}; do ./Fractals.exe /params=parameters/$j.json /palette=palettes/$i.json /image=universe/fractals/$j-histogram/$j-histogram-$i-inverted.png /histogram /invert; done; done;
for j in mandelbrot mandelbrot4; do mkdir -p universe/fractals/$j-log; for i in ${PALETTES}; do ./Fractals.exe /params=parameters/$j.json /palette=palettes/$i.json /image=universe/fractals/$j-log/$j-log-$i.png /log; done; done;
for j in mandelbrot mandelbrot4; do mkdir -p universe/fractals/$j-log; for i in ${PALETTES}; do ./Fractals.exe /params=parameters/$j.json /palette=palettes/$i.json /image=universe/fractals/$j-log/$j-log-$i-inverted.png /log /invert; done; done;
for j in mandelbrot-func mandelbrot-funcs mandelbrot-reciprocal; do mkdir -p universe/fractals/$j; for i in ${PALETTES}; do ./Fractals.exe /params=parameters/$j.json /palette=palettes/$i.json /image=universe/fractals/$j/$j-$i.png; done; done;
for j in mandelbrot-func mandelbrot-funcs mandelbrot-reciprocal; do mkdir -p universe/fractals/$j; for i in ${PALETTES}; do ./Fractals.exe /params=parameters/$j.json /palette=palettes/$i.json /image=universe/fractals/$j/$j-$i-inverted.png /invert; done; done;

# create fractal universe
for j in ${FRACTALS}; do mkdir -p universe/fractals/$j; for i in ${PALETTES}; do ./Fractals.exe /params=parameters/$j.json /palette=palettes/$i.json /image=universe/fractals/$j/$j-$i.png; done; done;
for j in ${FRACTALS}; do mkdir -p universe/fractals/$j; for i in ${PALETTES}; do ./Fractals.exe /params=parameters/$j.json /palette=palettes/$i.json /image=universe/fractals/$j/$j-$i-inverted.png /invert; done; done;
