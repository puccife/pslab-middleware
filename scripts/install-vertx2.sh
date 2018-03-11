#!/bin/bash
VERTXFILE=vert.x-2.1.5
VERTXDISTDIR=~/Vert.x/dist
curl -O -J -L "https://bintray.com/vertx/downloads/download_file?file_path=$VERTXFILE.tar.gz"
mkdir -p $VERTXDISTDIR
tar xf $VERTXFILE.tar.gz -C $VERTXDISTDIR
rm vert.x-2.1.5.tar.gz
echo "alias vertx2=\"$VERTXDISTDIR/$VERTXFILE/bin/vertx\"" >> ~/.bash_profile
