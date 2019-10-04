FROM ubuntu:16.04 as redis-test-cpull

RUN apt update && apt upgrade -y
RUN apt install cmake wget gcc g++ cpp unzip -y

RUN apt install libssl-dev openssl -y

WORKDIR /cpull/src
COPY src .
WORKDIR /cpull/build
RUN cmake ../src
RUN make
CMD ["./main/CPull_Runner"]