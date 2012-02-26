#!/bin/bash

BUILDPATH=Build/

cd $BUILDPATH

case $1 in
  update)
    make
    ;;
  clean)
    make clean
    echo "Cleaned up"
    ;;
  build|*)
      cmake .
      make
    ;;
esac
