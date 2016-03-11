#!/bin/bash

if [ "$1" == "" ]; then
  echo "Usage examples:"
  echo " - ${0} file.svg"
  echo " - find . -type f -name '*.svg' | xargs -i{} ${0} {}"
  exit 0;
fi

FILE=`basename $1 .svg`

if [ ! -e $FILE.svg ]; then
  echo $FILE.png does not exist
  exit 1;
fi

rm -f $FILE.png
convert -verbose $FILE.svg -scale 160x160 $FILE.png

