#!/bin/bash
CURRENTDIR=`pwd`
DOWNLOADDIR=/tmp/`date +'%Y-%m-%d_%s'`
mkdir -p $DOWNLOADDIR
cd $DOWNLOADDIR
echo "Downloading files..."
sudo wget https://pypi.python.org/packages/1c/f5/d925e65a1920a6f53c297f9e02a0affde5fb50c6cdeebf2a0f9342249db9/vertx-eventbus-1-2-0.zip#md5=956d4d871d785f72ebf0faf2d554dc63
echo "Extracting files..."
unzip vertx-eventbus-1-2-0.zip
echo "Installing Vert.x Tcp EventBus Bridge Python Clint..."
sudo easy_install -Z vertx-eventbus
echo "Removing temporary directory..."
cd $CURRENTDIR
sudo rm -rf $DOWNLOADDIR
