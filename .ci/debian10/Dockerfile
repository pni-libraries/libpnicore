FROM debian:buster

MAINTAINER DESY, Jan Kotanski <jankotan@gmail.com>

RUN /bin/bash -c 'echo "deb http://ftp.de.debian.org/debian buster main" > /etc/apt/sources.list.d/debian9de.list'
RUN apt-get -qq update && apt-get -qq -y install libterm-readline-gnu-perl software-properties-common coreutils gnupg2 procps apt-utils curl apt-transport-https gnupg2 ca-certificates
RUN curl http://repos.pni-hdri.de/debian_repo.pub.gpg | apt-key add -
RUN add-apt-repository "deb http://repos.pni-hdri.de/apt/debian buster main" -y
RUN apt-get -qq update && apt-get -qq -y dist-upgrade

RUN apt-get -qq update && apt-get -qq -y install cmake ninja-build python-pip g++ doxygen python-sphinx git libboost-all-dev gfortran graphviz libcppunit-dev texlive doxygen pkg-config texlive-latex-extra texlive-latex-recommended texlive-pictures python3-pygments libhdf5-dev libgtest-dev lsb-release python3-breathe texlive-pictures python3-sphinx-rtd-theme libjs-mathjax fonts-mathjax fonts-mathjax-extras

RUN apt-get clean
RUN pip install conan
RUN pip install gitpython

RUN conan remote remove conan-center
RUN conan remote add conan-community https://api.bintray.com/conan/conan-community/conan
RUN conan remote add conan-center https://conan.bintray.com
RUN conan remote add conan-transit https://conan-transit.bintray.com

RUN conan user
RUN mkdir /src
WORKDIR /src
