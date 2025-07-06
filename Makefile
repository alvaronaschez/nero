#SHELL := /usr/bin/bash

CXX=g++
CC=cc
#CXX=clang++
#CC=clang

MAKEFLAGS += --no-print-directory

.PHONY: build start init run test clean destroy reset targets nix valgrind
.PHONY: docker-build docker-run docker-start docker-exec

build:
	cmake --build build

start init:
	cmake -B build -S . -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	if [ ! -f compile_commands.json ]; then \
		ln -s build/compile_commands.json; \
	fi
	mkdir -p build

ARGS ?= src/main.cc
run:
	@build/nero $(ARGS)

test:
	ctest --test-dir build --output-on-failure

clean:
	cmake --build build --target clean

destroy reset:
	rm -rf build
	if [ -f compile_commands.json ]; then \
		rm compile_commands.json; \
	fi

targets:
	cmake --build build --target help

#nix:
#	nix-shell


valgrind:
	@valgrind --leak-check=yes build/nero src/main.cc


docker-build:
	podman build --file Dockerfile.alpine --tag nero-alpine .
docker-run:
	podman run -it -v .:/root/nero -w /root/nero --name nero-alpine nero-alpine:latest sh
docker-start:
	podman start nero-alpine
docker-exec:
	podman exec -it nero-alpine sh

# podman cp ~/df/home/dot-config/ nero-alpine:/root/
# mv /root/dot-config /root/.config
# podman cp ~/.ssh nero-alpine:/root/.ssh

