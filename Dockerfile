FROM ubuntu:latest

ARG SOURCE_DIR=/tmp/OrderBook/source
ARG BUILD_DIR=/tmp/OrderBook/build

ENV GTEST_DIR=/usr/include/googletest
ENV SOURCE_DIR=${SOURCE_DIR}
ENV BUILD_DIR=${BUILD_DIR}

RUN apt-get update
RUN apt-get install -y g++ build-essential
RUN apt-get install -y git && git clone https://github.com/google/googletest.git $GTEST_DIR
RUN apt-get install -y qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
RUN mkdir -p ${BUILD_DIR} ${SOURCE_DIR}

CMD ["bash"]