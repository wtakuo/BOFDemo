#!/bin/sh
# BOFDemo : A simple buffer overflow vulnerability demo for IA-32
# Copyright (c) 2015-2017 Takuo Watanabe

sudo sysctl -w kernel.randomize_va_space=0
make
make data
sudo chown root demo
sudo chmod 4755 demo
