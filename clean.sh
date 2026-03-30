#!/bin/bash

PROJECT_ROOT="$(dirname "$(readlink -f "$0")")"
BUILD_ROOT="$PROJECT_ROOT/build"

rm -rf "$BUILD_ROOT"
rm -rf "$PROJECT_ROOT/zappy_server"
rm -rf "$PROJECT_ROOT/zappy_ai"
rm -rf "$PROJECT_ROOT/zappy_gui"
