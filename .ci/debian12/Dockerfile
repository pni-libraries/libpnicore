FROM debian:bookworm

MAINTAINER DESY, Jan Kotanski <jankotan@gmail.com>
# RUN /bin/bash -c 'echo "deb http://ftp.de.debian.org/debian bookworm main" > /etc/apt/sources.list.d/debian9de.list'
RUN apt-get update
RUN apt-get install -y base-passwd apt-utils dialog -y
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
RUN apt-get -qq update && apt-get -qq install -y libterm-readline-gnu-perl software-properties-common coreutils gnupg2 procps curl apt-transport-https gnupg2 ca-certificates wget
RUN curl -s http://repos.pni-hdri.de/debian_repo.pub.gpg  | gpg --no-default-keyring --keyring gnupg-ring:/etc/apt/trusted.gpg.d/debian-hdri-repo.gpg --import
RUN chmod 644 /etc/apt/trusted.gpg.d/debian-hdri-repo.gpg
# RUN add-apt-repository "deb http://repos.pni-hdri.de/apt/debian bookworm main" -y
RUN cd /etc/apt/sources.list.d && wget http://repos.pni-hdri.de/bookworm-pni-hdri.list

RUN apt-get -qq update && apt-get -qq -y dist-upgrade

RUN apt-get -qq update && apt-get -y install cmake ninja-build python3-pip g++ doxygen python3-sphinx git libboost-all-dev gfortran graphviz libcppunit-dev texlive doxygen pkg-config texlive-latex-extra texlive-latex-recommended texlive-pictures python3-pygments libhdf5-dev libgtest-dev lsb-release python3-breathe texlive-pictures python3-sphinx-rtd-theme libjs-mathjax fonts-mathjax fonts-mathjax-extras

RUN apt-get clean
RUN pip3 install conan
RUN pip3 install gitpython

# RUN conan remote remove conan-center
RUN conan remote add conan-community https://api.bintray.com/conan/conan-community/conan
RUN conan remote add conan-center https://conan.bintray.com
RUN conan remote add conan-transit https://conan-transit.bintray.com

RUN conan user
RUN mkdir /src
WORKDIR /src