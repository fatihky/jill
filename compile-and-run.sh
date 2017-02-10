#!/bin/bash

g++ src/table.cc src/server.cc -o src/server -I/usr/local/include && src/server
