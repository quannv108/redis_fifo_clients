FROM ubuntu:16.04 as redis-test-cpush

RUN apt update && apt upgrade -y
RUN apt install cmake wget gcc g++ cpp unzip -y

RUN apt install libssl-dev openssl -y

WORKDIR /cpush/src
COPY src .
WORKDIR /cpush/build
RUN cmake ../src
RUN make
CMD ["./main/CPush_Runner"]