#!/bin/bash

scons PREFIX=/usr debian
dpkg-buildpackage -uc -us
