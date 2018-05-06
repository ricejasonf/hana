FROM ubuntu:bionic

RUN apt-get update && apt-get install -yq \
    gcc-7 build-essential cmake doxygen valgrind npm nodejs

RUN npm install -g http-server

WORKDIR /opt/build
CMD cmake /opt/src && /bin/bash
