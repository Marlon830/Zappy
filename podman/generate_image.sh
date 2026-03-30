#!/bin/bash

ROOT="$(dirname "$(readlink -f "$0")")"
TAG_NAME="$(cat "$ROOT/tag_name")"

echo "Generating ZOAT development image"
echo "This will require at least 20 GB of disk space"

podman build "--tag=$TAG_NAME" -f Containerfile
