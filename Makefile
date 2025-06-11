SHELL := /usr/bin/bash

CXX=g++
CC=cc
#CXX=clang++
#CC=clang

MAKEFLAGS += --no-print-directory

.PHONY: build start init run test clean destroy reset targets nix valgrind

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
	rm -rfd build
	if [ -f compile_commands.json ]; then \
		rm compile_commands.json; \
	fi

targets:
	cmake --build build --target help

nix:
	nix-shell

valgrind:
	@valgrind --leak-check=yes build/nero src/main.cc
