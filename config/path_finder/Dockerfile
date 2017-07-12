FROM debian:latest
MAINTAINER <stefanomunari.sm@gmail.com>

ENV DEBIAN_FRONTEND noninteractive
ENV TERM xterm
ENV DATA_PATH /home/cds

ADD loop.sh /tmp/

RUN apt-get update && apt-get upgrade -y \
&& apt-get install -y \
	build-essential \
    libboost-all-dev \
    g++ \
    libpython2.7

RUN chmod +x /tmp/loop.sh
RUN useradd -m -p cds cds
USER cds
WORKDIR $DATA_PATH

ENTRYPOINT ["sh","/tmp/loop.sh","&"]