#!/bin/bash

docker run \
    --name "zoat-mc-instance" \
    --rm \
    --tty --interactive \
    \
    --volume "./plugins:/app/plugins" \
    --volume "zoat-mc-app:/app" \
    \
    --network host \
    \
    $@ \
    \
    zoat-mc \
