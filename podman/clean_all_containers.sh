#!/bin/bash

ROOT="$(dirname "$(readlink -f "$0")")"
TAG_NAME="$(cat "$ROOT/tag_name")"

echo "Cleaning all containers, images and volumes"

podman container prune
podman volume prune
podman image prune

echo "Removing ZOAT development image"

podman image rm "$TAG_NAME"
