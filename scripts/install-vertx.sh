#!/bin/bash
CURRENTDIR=`pwd`
DOWNLOADDIR=/tmp/`date +'%Y-%m-%d_%s'`
sudo mkdir -p $DOWNLOADDIR
cd $DOWNLOADDIR
echo "Downloading files..."
sudo curl -O -J -L "https://bintray.com/artifact/download/vertx/downloads/vert.x-3.4.1-full.tar.gz"
echo "Extracting files..."
sudo tar xf vert.x-3.4.1-full.tar.gz
VERTXDISTDIR=/usr/local/share/vertx
sudo mkdir -p $VERTXDISTDIR
sudo mv vertx $VERTXDISTDIR/3.4.1
sudo ln -s $VERTXDISTDIR/3.4.1/bin/vertx /usr/local/bin
cd $CURRENTDIR
echo "Removing download folder..."
sudo rm -rf $DOWNLOADDIR
