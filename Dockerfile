FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    python3 \
    python3-pip \
    git \
    wget \
    curl

RUN pip3 install conan
RUN conan profile detect

WORKDIR /app
COPY source/ source/
COPY static/ static/
COPY Makefile Makefile
COPY conanfile.txt conanfile.txt
COPY CMakeLists.txt CMakeLists.txt
COPY .env .env

RUN make all
EXPOSE 11050

CMD ["./build/build/Release/cpp_victory"]
