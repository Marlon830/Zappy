#!/bin/bash

ROOT="$(dirname "$(readlink -f "$0")")"
PROJECT_ROOT="$(realpath "$ROOT/..")"
TAG_NAME="$(cat "$ROOT/tag_name")"

echo "Running ZOAT development image"

if ! podman volume exists zoat-home; then
    podman volume create zoat-home
fi

podman run \
    --name "zoat-instance" \
    --rm \
    --tty --interactive \
    \
    --volume "zoat-home:/home" \
    --volume "$PROJECT_ROOT:/epi/zoat:ro" \
    \
    --cap-add=NET_ADMIN \
    --cap-add=NET_RAW \
    --cap-add=SYS_ADMIN \
    --cap-add=SYS_NICE \
    --cap-add=SYS_PTRACE \
    --cap-add=SYS_RESOURCE \
    \
    --pids-limit=-1 \
    \
    --publish 1984-1987:1984-1987 \
    --publish 10000-14000:10000-14000 \
    \
    --device=nvidia.com/gpu=all \
    --device /dev/fuse \
    \
    "$TAG_NAME" 
