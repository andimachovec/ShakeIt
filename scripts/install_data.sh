#!/bin/bash
DATA_DIRECTORY=`finddir B_SYSTEM_NONPACKAGED_DATA_DIRECTORY`

mkdir -p $DATA_DIRECTORY/ShakeIt
cp -rv ../data/* $DATA_DIRECTORY/ShakeIt


