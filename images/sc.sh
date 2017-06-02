#!/bin/bash

for f in $(find . -type f -name "*.png")
do
echo "Processing $f ..."
convert $f -strip $f
done