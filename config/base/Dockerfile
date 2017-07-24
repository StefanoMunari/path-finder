FROM debian:latest

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && apt-get upgrade -y \
&& apt-get install -y \
	build-essential \
    g++ \
    libboost-all-dev \
    libjsoncpp-dev