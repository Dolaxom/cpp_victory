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
RUN conan profile new default --detect && \
    conan profile update settings.compiler.libcxx=libstdc++11 default

WORKDIR /app
COPY . .
RUN make all
EXPOSE 11050

CMD ["./build/build/Release/cpp_victory"]
