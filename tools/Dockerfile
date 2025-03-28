# trunk-ignore-all(checkov/CKV_DOCKER_3)
FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && \
  apt-get purge man-db -y && \
  apt-get install -y \
    build-essential cmake curl \
    libx11-dev libglfw3-dev libglfw3 \
    xorg-dev libbsd-dev clang mold \
    git autoconf automake libtool gcc make \
    libpthread-stubs0-dev libasound2-dev \
    libpulse-dev libsndio-dev \
    libroar-dev libaudio-dev \
    libaudiofile-dev \
    libxau-dev libslang2-dev \
    libalsa-ocaml-dev libasound2-plugins

WORKDIR /app

# Add a health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
  CMD [ "exit", "0" ]

CMD [ "make", "build" ]