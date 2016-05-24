#!/bin/sh
sudo sysctl -w kernel.randomize_va_space=0
make
make data
sudo chown root demo
sudo chmod 4755 demo
