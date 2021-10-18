FROM ubuntu:20.04
RUN apt-get update && apt-get install -y \
    gcc \
    g++ \
    python3 \
    python3-distutils \
    python3-apt \
    python3-dev \
    python3-pip \
    wget \
    make \
    vim \
    && rm -rf /var/lib/apt/lists/*

ENV PATH=/usr/bin
ENV CC=/usr/bin/gcc
ENV CXX=/usr/bin/g++

RUN pip3 install conan
ENV PATH=/usr/local/bin:${PATH}

# from http://www.yolinux.com/TUTORIALS/CORBA.html
RUN wget https://downloads.sourceforge.net/project/omniorb/omniORB/omniORB-4.2.4/omniORB-4.2.4.tar.bz2 --show-progress \
    && tar -xvf omniORB-4.2.4.tar.bz2 \
    && cd omniORB-4.2.4 \
    && ./configure --prefix=/opt \
    && make -j8 \
    && make install \
    && cd .. \
    && rm -f omniORB-4.2.4.tar.bz2
    # && rm -rf omniORB-4.2.4

ENV OMNIORB_CONFIG=/etc/omniORB.cfg

RUN cp omniORB-4.2.4/sample.cfg ${OMNIORB_CONFIG} \
    && sed -i '/supportPerThreadTimeOut/ s/./#&/' ${OMNIORB_CONFIG} \
    && sed -i '/poaUniquePersistentSystemIds/ s/./#&/' ${OMNIORB_CONFIG}

ENV PATH=/opt/bin:${PATH}
ENV LD_LIBRARY_PATH=/opt/lib:${LD_LIBRARY_PATH}
