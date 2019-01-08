# Get the base Ubuntu image from Docker Hub
FROM ubuntu:latest

# Update apps on the base image
RUN apt-get -y update && apt-get install -y

RUN apt-get install wget -y
#RUN apt-add-repository "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-6.0 main"
#RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
RUN apt-get install -y clang-6.0 lld-6.0
RUN apt-get install git ninja-build cmake vim build-essential -y

#Checkout code
#RUN git clone https://TotteKarlsson@bitbucket.org/TotteKarlsson/dsl-tp.git libs/dsl-tp

## Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY ./dsl-tp /usr/src/dsl-tp
COPY ./dsl /usr/src/dsl

RUN mkdir /builds
RUN mkdir -p /build/lib
ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/build/lib
ENV PATH=$PATH:/build/bin

WORKDIR /builds
RUN  cmake -G"Ninja" /usr/src/dsl-tp -DHTTP_ONLY=ON -DCURL_DISABLE_HTTP=OFF -DBUILD_CURL_EXE=ON -DCMAKE_INSTALL_PREFIX="/build"
WORKDIR /builds
RUN ninja install

#CMD ["./Test"]
CMD /bin/bash