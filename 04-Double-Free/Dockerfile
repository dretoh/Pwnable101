FROM ubuntu@sha256:0d779ea97881505f5ef0039336ee85edba27519bdba968c284c86ee066a973c8
#22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends socat ca-certificates coreutils && rm -rf /var/lib/apt/lists/*

RUN groupadd -g 1337 pwnable101 && useradd -m -u 1337 -g 1337 -s /usr/sbin/nologin pwnable101

WORKDIR /home/pwnable101

COPY ./prob /home/pwnable101/prob
COPY ./flag /home/pwnable101/flag

RUN chown root:pwnable101 /home/pwnable101/prob && chmod 0550 /home/pwnable101/prob

USER pwnable101
EXPOSE 13337

CMD ["sh", "-lc", "exec socat TCP-LISTEN:13337,reuseaddr,fork EXEC:'/home/pwnable101/prob',stderr"]
