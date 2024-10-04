#!/bin/bash
# @date 2024-10-04 (last modification)
#echo $1 | sed "s#exit#exit_common#" > new_name.tmp
#TARGET=`cat new_name.tmp`
TARGET=../../lib/common.pde/exit.pde
echo -e ln -s $TARGET $1 $COLERR
ln -s $TARGET $1 -f
echo -e $NOCOLO $NORMCO
#/usr/bin/git mv $1 $TARGET

