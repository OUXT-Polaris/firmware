docker run --rm -t -u $(id -u):$(id -g) \
  --mount=type=bind,source="$(pwd)",destination=/var/mbed \
  --mount=type=bind,source="$(pwd)/.ccache",destination=//.ccache \
  -w /var/mbed ghcr.io/armmbed/mbed-os-env \
  bash -c "mbed-tools deploy \
    && mbed-tools compile -t GCC_ARM -m NUCLEO_F767ZI"