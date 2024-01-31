#!/usr/bin/bash

ragel ../../src/http/Http_Parser.rl -o ../../src/http/Http_Parser.cpp
cmake -Bbuild
cmake --build build
build/http_test