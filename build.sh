docker run -t --mount=type=bind,source="$(pwd)",destination=/var/mbed -w /var/mbed ghcr.io/armmbed/mbed-os-env \
  bash -c "mbed-tools deploy && mbed-tools compile -t GCC_ARM -m NUCLEO_F767ZI"