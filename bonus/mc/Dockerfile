FROM archlinux

ARG mc_version=1.20.6
ARG mc_build_minram=1G
ARG mc_build_maxram=4G
ARG mc_run_minram=1G
ARG mc_run_maxram=4G

# System initialization
RUN pacman-key --init
RUN pacman-key --populate archlinux
RUN pacman -Syu --noconfirm

# Base packages installation
RUN pacman -S --noconfirm \
    \
    base \
    \
    jdk-openjdk git

RUN mkdir -p /tmp/minecraft
WORKDIR /tmp/minecraft

# Build Spigot
RUN curl -o BuildTools.jar https://hub.spigotmc.org/jenkins/job/BuildTools/lastSuccessfulBuild/artifact/target/BuildTools.jar
RUN java -jar -Xms$mc_build_minram -Xmx$mc_build_maxram BuildTools.jar --rev $mc_version

# Install the newly built Spigot server
RUN mkdir -p /app
RUN cp spigot-$mc_version.jar /app/spigot.jar
RUN rm -rf /tmp/minecraft

# Populate the server directory
WORKDIR /app
RUN java -Xms$mc_run_minram -Xmx$mc_run_maxram -jar spigot.jar

# Copy the template server directory
COPY template /app

# Setup the launch script
RUN echo '#!/bin/bash' > /app/run.sh
RUN echo "java -Xms$mc_run_minram -Xmx$mc_run_maxram -agentlib:jdwp=transport=dt_socket,server=y,suspend=n,address=21987 -jar spigot.jar" >> /app/run.sh
RUN chmod +x /app/run.sh

# Expose the server
EXPOSE 25565
EXPOSE 25575
EXPOSE 25587
EXPOSE 21987

VOLUME /app

# Setup the generated script as the main entrypoint
ENTRYPOINT /app/run.sh
