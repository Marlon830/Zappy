#!/bin/bash

PROJECT_ROOT="$(dirname "$(readlink -f "$0")")"
BUILD_ROOT="$PROJECT_ROOT/build"

mkdir -p "$BUILD_ROOT"
cmake -B "$BUILD_ROOT" -S "$PROJECT_ROOT" $@
cmake --build "$BUILD_ROOT" -j $(nproc)
