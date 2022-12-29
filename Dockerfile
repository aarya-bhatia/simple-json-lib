FROM ubuntu:latest
RUN apt update && apt-get install -y build-essential valgrind g++ make
COPY . /usr/src/json
WORKDIR /usr/src/json
RUN make clean
ENTRYPOINT [ "/usr/bin/bash" ]