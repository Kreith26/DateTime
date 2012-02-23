#!/bin/bash

BUILDPATH=Build/

cd $BUILDPATH

case $1 in
  update)
    make
    ;;
  clean)
    make clean
    ;;
  build|*)
      cmake .
      make
    ;;
esac
