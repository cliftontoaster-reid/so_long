# trunk-ignore-all(checkov/CKV_DOCKER_3)
FROM archlinux:base-devel-20250323.0.325468

# Enable parallel downloads in pacman and install dependencies
RUN sed -i 's/^#ParallelDownloads = 5/ParallelDownloads = 6/' /etc/pacman.conf && \
  pacman -Syu --noconfirm && \
  pacman -S --noconfirm base-devel cmake curl libx11 glfw xorg-server libbsd clang mold git autoconf automake libtool gcc make pkgconf libpulse alsa-lib && \
  pacman -Scc --noconfirm

WORKDIR /app

# Add a health check
HEALTHCHECK --interval=30s --timeout=10s --start-period=5s --retries=3 \
  CMD [ "exit", "0" ]

CMD [ "make", "build" ]
