#!/bin/bash

mkdir -v -p /boot/home/config/settings/Boggle
mkdir -v /boot/home/config/settings/Boggle/dict
cp -v ../data/boggle.xml /boot/home/config/settings/Boggle
cp -v ../data/dict/*.dict /boot/home/config/settings/Boggle/dict
