#!/bin/bash

#Script to build User Interface
qmake -project
qmake UI.pro
make
