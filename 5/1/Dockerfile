FROM ubuntu:16.04
	LABEL maintainer starovoytovsergeya@gmail.com
	RUN apt-get update && apt-get install -y gcc
	WORKDIR /home/test/
	COPY hello_world.c .
	RUN gcc hello_world.c -o hello_world
	CMD ["./hello_world"]