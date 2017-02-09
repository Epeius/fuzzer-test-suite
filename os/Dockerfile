# This is an i386 image of debian wheezy
# Use it to compile the kernel

FROM ubuntu:16.04 

RUN \
    apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    apt-file texinfo flex bison patch python unzip git bc \
    subversion screen cmake ninja-build golang autoconf libtool \
    apache2 python-dev pkg-config zlib1g-dev libgcrypt11-dev \
    bzip2 wget less nano g++ gcc file libc6-dev  make \
    fakeroot build-essential devscripts kernel-package libncurses5-dev clang-3.8 && \
    apt-get clean && \
    apt-file update && \
    mkdir -p /etc/kernel/postinst.d 



ENTRYPOINT ["/bin/bash"]

